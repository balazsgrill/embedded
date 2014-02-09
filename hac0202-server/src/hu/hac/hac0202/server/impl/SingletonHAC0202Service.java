/**
 * 
 */
package hu.hac.hac0202.server.impl;

import hu.hac.hac0202.server.HAC0202Manager;
import hu.hac.hac0202.server.HACFrame;
import hu.hac.hac0202.server.IHAC0202Service;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

/**
 * @author balage
 *
 */
public class SingletonHAC0202Service extends Thread implements IHAC0202Service{

	private static IHAC0202Service instance = null;
	
	public static IHAC0202Service getInstance() {
		if (instance == null){
			instance = new SingletonHAC0202Service();
		}
		return instance;
	}
	
	private static long CONF_TIMEOUT = 1000;
	private static long CONF_RETRY = 3;
	
	private static int CMDID_RELAY = 0;
	private static int CMDID_PWM1 = 1;
	private static int CMDID_PWM2 = 2;
	
	private static int MSGID_ACK = 1;
	
	private static int RELAY1_ON = 1;
	private static int RELAY1_OFF = 2;
	private static int RELAY2_ON = 4;
	private static int RELAY2_OFF = 8;
	
	private final HAC0202Manager manager;
	
	private final BlockingQueue<HACFrame> frames = new LinkedBlockingQueue<>();
	
	private HACFrame current = null;
	private long sentTime;
	private int tries;
	
	private SingletonHAC0202Service() {
		setDaemon(true);
		manager = new HAC0202Manager();
		start();
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
			
			try {
				for(HACFrame f: manager.read()){
					if (f.getId() == MSGID_ACK){
						if (current != null && current.getId() == f.getData()){
							// ACK received, finished sending
							current = null;
						}
					}
				}
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			if (current != null){
				/* Still waiting for ACK */
				
				if (System.currentTimeMillis()-sentTime > CONF_TIMEOUT){
					/* retry */
					if(tries < CONF_RETRY){
						tries++;
						try {
							manager.send(current);
						} catch (Exception e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
						sentTime = System.currentTimeMillis();
					}else{
						/* Give up */
						current = null;
					}
				}
				
			}else{
				/* No pending communication */
				try {
					HACFrame current = frames.poll();
					if (current != null){
						manager.send(current);
						sentTime = System.currentTimeMillis();
						tries = 1;
					}
				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
	}

	@Override
	public void relay1(boolean on) {
		frames.add(new HACFrame(CMDID_RELAY, on ? RELAY1_ON : RELAY1_OFF));
	}

	@Override
	public void relay2(boolean on) {
		frames.add(new HACFrame(CMDID_RELAY, on ? RELAY2_ON : RELAY2_OFF));
	}

	@Override
	public void pwm1(float value, float rampSpeed) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void pwm2(float value, float rampSpeed) {
		// TODO Auto-generated method stub
		
	}
	
}
