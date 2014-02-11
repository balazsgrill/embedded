/**
 * 
 */
package hu.hac;

import java.util.Collection;

/**
 * @author balazs.grill
 *
 */
public interface IControlService {

	public Collection<String> getDevices();
	
	public IDeviceControl getControl(String device);
	
}
