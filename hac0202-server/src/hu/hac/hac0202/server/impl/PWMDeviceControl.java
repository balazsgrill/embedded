/**
 * 
 */
package hu.hac.hac0202.server.impl;

import hu.hac.IDeviceControl;
import hu.hac.hac0202.server.IHAC0202ControlService;

/**
 * @author balazs.grill
 *
 */
public class PWMDeviceControl implements IDeviceControl {

	private final IHAC0202ControlService service;
	private final int msgID;
	
	private int lastValue = 0;
	
	/**
	 * 
	 */
	public PWMDeviceControl(IHAC0202ControlService service, int msgID) {
		this.service = service;
		this.msgID = msgID;
	}

	/* (non-Javadoc)
	 * @see hu.hac.IDeviceControl#requestValue(int)
	 */
	@Override
	public void requestValue(int value) {
		service.sendCommandSafely(msgID, value);
		lastValue = value;
	}

	/* (non-Javadoc)
	 * @see hu.hac.IDeviceControl#step()
	 */
	@Override
	public void step() {
	}

	@Override
	public int currentValue() {
		return lastValue;
	}

}
