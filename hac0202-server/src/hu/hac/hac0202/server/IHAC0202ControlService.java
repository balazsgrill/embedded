/**
 * 
 */
package hu.hac.hac0202.server;

import hu.hac.IControlService;

/**
 * @author balazs.grill
 *
 */
public interface IHAC0202ControlService extends IControlService{

	public void sendCommandSafely(int id, int data);
	
}
