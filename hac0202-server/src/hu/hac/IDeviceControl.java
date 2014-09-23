/**
 * 
 */
package hu.hac;


/**
 * @author balazs.grill
 *
 */
public interface IDeviceControl {

	public int currentValue();
	
	public void requestValue(int value);
	
	public void step();
	
}
