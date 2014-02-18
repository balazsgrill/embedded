/**
 * 
 */
package hu.hac.hac0202.server.impl;

import hu.hac.IControlService;
import hu.hac.hac0202.server.HAC0202Manager;
import hu.hac.hac0202.server.IHAC0202ControlService;
import hu.hac.impl.AbstractControlServiceThread;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

/**
 * @author balage
 *
 */
public class SingletonHAC0202Service extends AbstractControlServiceThread implements IHAC0202ControlService{

	private static IControlService instance = null;
	
	public static IControlService getInstance() {
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
	private static int MSGID_UNKNOWN_MSG = 2;
	
	private static int RELAY1_ON = 1;
	private static int RELAY1_OFF = 2;
	private static int RELAY2_ON = 4;
	private static int RELAY2_OFF = 8;
	
	private HAC0202Manager manager;
	
	private final BlockingQueue<HAC0202Frame> frames = new LinkedBlockingQueue<>();
	
	private HAC0202Frame current = null;
	private long sentTime;
	private int tries;
	
	private boolean readFailure = false;
	
	@Override
	protected void initialize() {
		super.initialize();
		manager = new HAC0202Manager();
		
		RelayDeviceControl R1 = new RelayDeviceControl(this, CMDID_RELAY, RELAY1_ON, RELAY1_OFF);
		register("R1", R1);
		register("R2", new RelayDeviceControl(this, CMDID_RELAY, RELAY2_ON, RELAY2_OFF));
		PWMDeviceControl P1 = new PWMDeviceControl(this, CMDID_PWM1);
		register("P1", P1);
		register("P2", new PWMDeviceControl(this, CMDID_PWM2));
		
		register("L", new CompositeLamp(R1, P1));
	}
	
	@Override
	protected void step() {
		try {
			for(HAC0202Frame f: manager.read()){
				if (f.getId() == MSGID_UNKNOWN_MSG){
					if (current != null && current.getId() == f.getData()){
						// sent message ID is unknown by target, give up sending
						System.err.println("Message ID unknown by target: "+current.getId());
						current = null;
					}
				}
				if (f.getId() == MSGID_ACK){
					if (current != null && current.getId() == f.getData()){
						// ACK received, finished sending
						current = null;
					}
				}
			}
			if (readFailure){
				System.err.println("Reading recovered!");
			}
			readFailure = false;
		} catch (Exception e) {
			if (!readFailure){
				readFailure = true;
				System.err.println("Cannot read ("+e.getMessage()+")");
			}
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
						// Error may be permanent, give up sending
						current = null;
						System.out.println("Could not send message ("+e.getMessage()+")");
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
				current = frames.poll();
				if (current != null){
					manager.send(current);
					sentTime = System.currentTimeMillis();
					tries = 1;
				}
			} catch (Exception e) {
				// no device, or other permanent problem
				current = null;
				System.err.println("Sending failed ("+e.getMessage()+")");
			}
		}
		super.step();
	}

	@Override
	public void sendCommandSafely(int id, int data) {
		frames.add(new HAC0202Frame(id, data));
	}
	
}
