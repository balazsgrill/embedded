/**
 * 
 */
package hu.hac.hac0202.server;

/**
 * @author balazs.grill
 *
 */
public class MCP2200ControllerThread extends Thread {

	private volatile boolean stop = false;
	
	
	
	/**
	 * 
	 */
	public MCP2200ControllerThread() {
		super("MCP2200 controller");
	}

	public synchronized void requestStop(){
		this.stop = true;
	}
	
	@Override
	public void run() {
		boolean isStopped = false;
		while(!isStopped){
			
			
			synchronized (this) {
				isStopped = stop;
			}
		}
	}

}
