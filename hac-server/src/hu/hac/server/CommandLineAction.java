/**
 * 
 */
package hu.hac.server;

import java.util.Map;

/**
 * @author balazs.grill
 *
 */
public class CommandLineAction implements IControlAction {

	private final String commandLine;
	
	/**
	 * 
	 */
	public CommandLineAction(String commandLine) {
		this.commandLine = commandLine;
	}

	/* (non-Javadoc)
	 * @see hu.hac.server.IControlAction#execute(java.util.Map)
	 */
	@Override
	public void execute(Map<String, String> options) throws Exception {
		//ProcessBuilder pb = new ProcessBuilder(commandLine.split(" "));
		Process process = Runtime.getRuntime().exec(commandLine.split(" "), null, null); //pb.start();

		int returnCode = process.waitFor();
		
		if (returnCode != 0) {
			throw new IllegalArgumentException("Process returned with "+returnCode);
		}
	}

}
