/**
 * 
 */
package hu.hac.server;

import java.io.IOException;
import java.io.OutputStream;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * @author balazs.grill
 *
 */
public abstract class AbstractControlPageServlet extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = -4939978272239724093L;

	protected abstract IControlPage getPage();
	
	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {
		
		String actionID = req.getParameter("actionid");
		if (actionID != null){
			Map<String, String> args = new HashMap<>();
			for(Entry<String, String[]> entry : req.getParameterMap().entrySet()){
				String[] v = entry.getValue();
				args.put(entry.getKey(), v.length == 0 ? "" : v[0]);
			}
			IControlAction action = getPage().getAction(actionID, args);
			if (action != null){
				try {
					action.execute(args);
				} catch (Exception e) {
					resp.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, e.getMessage());
				}
			}
		}
		
		resp.setContentType("text/html;charset=UTF-8");
		OutputStream out = resp.getOutputStream();
		out.write(getPage().getPageContent());
		out.flush();
		out.close();
	}

}
