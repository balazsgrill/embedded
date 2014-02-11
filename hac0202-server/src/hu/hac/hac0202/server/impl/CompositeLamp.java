/**
 * 
 */
package hu.hac.hac0202.server.impl;

import hu.hac.IDeviceControl;

/**
 * @author balazs.grill
 *
 */
public class CompositeLamp implements IDeviceControl {

	/* PWM change ramp speed n/sec (e.g. 100/sec => 0..255 = 2.55 seconds) */
	private static final float rampSpeed = 100; 
	
	private final IDeviceControl relay;
	private final IDeviceControl pwm;
	
	private boolean relayState;
	private int lastValue;
	private int requestedValue;
	private long lastTime = 0;
	
	private float cumulation = 0;
	
	/**
	 * 
	 */
	public CompositeLamp(IDeviceControl relay, IDeviceControl pwm) {
		this.relay = relay;
		this.pwm = pwm;
		relayState = false;
		lastValue = 0;
		requestedValue = 0;
	}

	/* (non-Javadoc)
	 * @see hu.hac.IDeviceControl#requestValue(int)
	 */
	@Override
	public void requestValue(int value) {
		requestedValue = Math.min(255, Math.max(0, value));
	}

	/* (non-Javadoc)
	 * @see hu.hac.IDeviceControl#step()
	 */
	@Override
	public void step() {
		if (lastTime == 0){
			lastTime = System.currentTimeMillis();
			return;
		}
		
		if (lastValue == 0 && relayState){
			//Reached 0, switch off relay
			relay.requestValue(0);
			relayState = false;
		}
		
		if (requestedValue != lastValue){
			
			if (requestedValue != 0 && !relayState){
				/* Start ramping by switching the relay on */
				relay.requestValue(1);
				relayState = true;
			}
			
			long time = lastTime-System.currentTimeMillis();
			float ramp = cumulation + (requestedValue>lastValue ? 1 : -1) * rampSpeed*time/1000;
			
			int r = Math.round(ramp);
			cumulation = ramp-r;
			
			if (r != 0){
				lastValue = lastValue+r;
				pwm.requestValue(lastValue);
			}
			
		}

		lastTime = System.currentTimeMillis();
		
	}

}
