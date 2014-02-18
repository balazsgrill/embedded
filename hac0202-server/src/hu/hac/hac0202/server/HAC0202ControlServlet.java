/**
 * 
 */
package hu.hac.hac0202.server;

import hu.hac.IDeviceControl;
import hu.hac.hac0202.server.impl.SingletonHAC0202Service;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * @author balazs.grill
 *
 */
public class HAC0202ControlServlet extends HttpServlet {

	public static final String localhost = "127.0.0.1";
	public static final String lan = "192.168.0.";
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 2710130948421584380L;
	
	public static boolean allow(String addr){
		if (localhost.equals(addr)) return true;
		if (addr.startsWith(lan)){
			String last = addr.substring(lan.length());
			int l = Integer.parseInt(last);
			return l >=100 && l<=200;
		}
		return false;
	}
	
	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {

		String remote = req.getRemoteAddr().trim();
		
		String dev = req.getParameter("dev");
		String value = req.getParameter("value");
		
		if (dev == null){
			
			PrintWriter out = resp.getWriter();
			out.print(remote);
			out.close();
			
		}else{

			if (allow(remote)){
				
				IDeviceControl control = SingletonHAC0202Service.getInstance().getControl(dev);
				if (control == null){
					resp.sendError(HttpServletResponse.SC_NOT_FOUND, "Could not found device: "+dev);
				}else{
					if (value == null){
						int v = control.currentValue();
						PrintWriter out = resp.getWriter();
						out.print(v);
						out.flush();
						out.close();
					}else{
						Integer v = Integer.parseInt(value);
						control.requestValue(v.intValue());
					}
				}
			}else{
				resp.sendError(HttpServletResponse.SC_FORBIDDEN, "Forbidden access");
			}
		}
		
		
	}
	
}
