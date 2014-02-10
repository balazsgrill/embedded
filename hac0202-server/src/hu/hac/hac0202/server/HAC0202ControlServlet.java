/**
 * 
 */
package hu.hac.hac0202.server;

import hu.hac.hac0202.server.impl.SingletonHAC0202Service;

import java.io.IOException;
import java.io.Writer;
import java.util.Stack;

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
	
	private class StructuredHTMLSerializer{
		private final Writer out;
		private final Stack<String> stack = new Stack<>();
		
		public StructuredHTMLSerializer(HttpServletResponse resp) throws IOException {
			out = resp.getWriter();
		}
		
		public void e(String element, String...args) throws IOException{
			out.write("<");
			out.write(element);
			for(int i=0;i<args.length/2;i++){
				out.write(" ");
				out.write(args[i*2]);
				out.write("=\"");
				out.write(args[i*2+1]);
				out.write("\"");
			}
			out.write(">");
			stack.push(element);
		}
		
		public void t(String text) throws IOException{
			out.write(text);
		}
		
		public void e() throws IOException{
			String element = stack.pop();
			out.write("</"+element+">");
		}
		
		public void done() throws IOException{
			while(!stack.isEmpty()){
				
			}
			out.close();
		}
	}
	
	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {
		
		/* TODO filter access by remote address */
		//req.getRemoteAddr();
		
		String dev = req.getParameter("dev");
		String value = req.getParameter("value");
		
		if (dev == null || value == null){
			
			StructuredHTMLSerializer out = new StructuredHTMLSerializer(resp);
			out.t("<!DOCTYPE html>");
			out.e("html");
				out.e("head");
					out.e("script");
					out.t("function control(dev, value){"
							+ "var xmlhttp=new XMLHttpRequest();"
							+ "xmlhttp.open(\"GET\",\""+getServletContext().getContextPath()+"?dev=\"+dev+\"&value=\"+value,true);"
							+ "xmlhttp.send();"
							+ "}");
					out.e();
				out.e();
				out.e("body");
				out.e("div");
					out.e("button", "type","button", "onclick","control('R1',1)");
					out.t("R1 ON");
					out.e();
					out.e("button", "type","button", "onclick","control('R1',0)");
					out.t("R1 OFF");
					out.e();
				out.e();out.e("div");
					out.e("button", "type","button", "onclick","control('R2',1)");
					out.t("R2 ON");
					out.e();
					out.e("button", "type","button", "onclick","control('R2',0)");
					out.t("R2 OFF");
					out.e();
				out.e();
				out.e();
			out.e();
			
			out.done();
			
		}else{
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
	
}
