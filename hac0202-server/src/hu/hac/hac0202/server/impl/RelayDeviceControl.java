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
public class RelayDeviceControl implements IDeviceControl {

	private final int msgID;
	private final int onData;
	private final int offData;
	
	private final IHAC0202ControlService service;
	
	/**
	 * 
	 */
	public RelayDeviceControl(IHAC0202ControlService service, int msgID, int onData, int offData) {
		this.msgID = msgID;
		this.onData = onData;
		this.offData = offData;
		this.service = service;
	}

	/* (non-Javadoc)
	 * @see hu.hac.IDeviceControl#requestValue(int)
	 */
	@Override
	public void requestValue(int value) {
		service.sendCommandSafely(msgID, value > 0 ? onData : offData);
	}

	/* (non-Javadoc)
	 * @see hu.hac.IDeviceControl#step(hu.hac.IControlService)
	 */
	@Override
	public void step() {
	}

}
