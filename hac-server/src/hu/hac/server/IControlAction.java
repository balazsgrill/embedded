/**
 * 
 */
package hu.hac.server;

import java.util.Map;

/**
 * @author balazs.grill
 *
 */
public interface IControlAction {

	public void execute(Map<String, String> options) throws Exception;
	
}
