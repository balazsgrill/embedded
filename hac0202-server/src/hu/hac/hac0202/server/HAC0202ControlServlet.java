/**
 * 
 */
package hu.hac.hac0202.server;

import hu.hac.hac0202.server.impl.SingletonHAC0202Service;

import java.io.IOException;
import java.util.logging.Logger;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * @author balazs.grill
 *
 */
public class HAC0202ControlServlet extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = 2710130948421584380L;
	
	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {
		
		String dev = req.getParameter("dev");
		String value = req.getParameter("value");
		
		Integer v = Integer.parseInt(value);
		
		if ("R1".equals(dev)){
			boolean on = v != 0;
			SingletonHAC0202Service.getInstance().relay1(on);	
		}else
		if ("R2".equals(dev)){
			boolean on = v != 0;
			SingletonHAC0202Service.getInstance().relay2(on);
		}else{
			throw new ServletException("Unknown device!");
		}
	}
	
}
