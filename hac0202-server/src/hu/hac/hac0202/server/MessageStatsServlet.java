/**
 * 
 */
package hu.hac.hac0202.server;

import hu.hac.hac0202.server.impl.SingletonHAC0202Service;
import hu.hac.hac0202.server.impl.StatisticsServiceEventListener;

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
public class MessageStatsServlet extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = -8434428743500757705L;

	@Override
	protected void doGet(HttpServletRequest req, HttpServletResponse resp)
			throws ServletException, IOException {
		
		StatisticsServiceEventListener stats = SingletonHAC0202Service.getStats();
		if (stats == null){
			resp.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
		}
		
		PrintWriter out = resp.getWriter();
		
		synchronized (stats) {
			int[][] data = stats.getData();
			int current = stats.getCurrent();
			out.print("{ queue : ");out.print(SingletonHAC0202Service.getInstance().getQueueLength());
			out.print(", period : ");out.print(SingletonHAC0202Service.getInstance().getPeriod());
			out.print(", histogram :[");
			
			for(int i=0;i<data.length;i++){
				current++;
				current = current%data.length;
				if (i == 0){
					out.println();
				}else{
					out.println(",");
				}
				
				int[] row = data[current];
				if (row == null){
					out.print("null");
				}else{
					out.print("{");
						out.print("timeouts : ");out.print(row[0]);
						out.print(", fails : ");out.print(row[1]);
						out.print(", successes : ");out.print(row[2]);
					out.print("}");
				}
				
			}
			
			out.print("]}");
		} 
		out.close();
	}

}
