/**
 * 
 */
package hu.hac.server;

import java.util.Map;

/**
 * @author balazs.grill
 *
 */
public interface IControlPage {

	public byte[] getPage();
	
	public IControlAction getAction(String actionID, Map<String, String> options);
	
}
