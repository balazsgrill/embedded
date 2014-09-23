/**
 * 
 */
package hu.hac.impl;

import hu.hac.IControlService;
import hu.hac.IDeviceControl;

import java.util.Collection;
import java.util.LinkedHashMap;
import java.util.Map;

/**
 * @author balazs.grill
 *
 */
public abstract class AbstractControlServiceThread extends Thread implements IControlService{

	public AbstractControlServiceThread() {
		initialize();
		
		setDaemon(true);
		start();
	}
	
	private final Map<String, IDeviceControl> devices = new LinkedHashMap<>();
	

	protected final void register(String device, IDeviceControl control){
		devices.put(device, control);
	}
	
	@Override
	public Collection<String> getDevices() {
		return devices.keySet();
	}
	
	@Override
	public IDeviceControl getControl(String device) {
		return devices.get(device);
	}
	
	protected void initialize(){
		
	}
	
	@Override
	public void run() {
		
		while(true){
			try {
				sleep(100);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			step();
		}
	}
	
	protected void step(){
		for(IDeviceControl control : devices.values()){
			control.step();
		}
	}
	
}
