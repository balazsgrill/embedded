/**
 * 
 */
package uart.dio.lib;

import jssc.SerialPortException;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.MqttSecurityException;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

/**
 * @author balazs.grill
 *
 */
public class Main {

	public final static String broker = "tcp://localhost:1883";
	
	private static void executeCommand(UARTDioInterface port, String cmd, String arg) throws NumberFormatException, SerialPortException{
		UARTDioCommand command = UARTDioCommand.valueOf(cmd);
		
		int a = 0;
		if (arg != null){
			if (arg.startsWith("0x")){
				a = Integer.parseInt(arg.substring(2), 16);
			}else{
				a = Integer.parseInt(arg);
			}
		}
		
		System.out.println("Sending "+command+"("+a+")");
		port.sendCommand(command, a);
	}
	
	/**
	 * @param args
	 * @throws SerialPortException 
	 * @throws MqttException 
	 * @throws MqttSecurityException 
	 */
	public static void main(String[] args) throws SerialPortException, MqttSecurityException, MqttException {

		String portID = args[0];
		String id = portID;
		int per = id.lastIndexOf('/');
		if (per != -1){
			id = id.substring(per+1);
		}
		
		MqttClient sampleClient = new MqttClient(broker, "uart-dio-"+id, new MemoryPersistence());
		
		try(UARTDioInterface port = new UARTDioInterface(portID)){
			
			 MqttConnectOptions connOpts = new MqttConnectOptions();
	         connOpts.setCleanSession(true);
	         sampleClient.connect(connOpts);
	         sampleClient.subscribe("uart-dio/"+id);
	         sampleClient.setCallback(new MqttCallback() {
					
					@Override
					public void messageArrived(String arg0, MqttMessage arg1) throws Exception {
						String cmd = new String(arg1.getPayload());
						
						String[] cmds = cmd.split(" ");
						if (cmds.length > 0){
							executeCommand(port, cmds[0], cmds.length >= 2 ? cmds[1] : null);
						}
					}
					
					@Override
					public void deliveryComplete(IMqttDeliveryToken arg0) {
					}
					
					@Override
					public void connectionLost(Throwable arg0) {
						System.exit(-1);
					}
				});
			
			while(true){
				
	           ReadData data = port.read();
	           if (data != null){
	        	   //TODO publish data in message
	           }else{
	        	   try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
	           }
			}
			
		}finally{
			sampleClient.disconnect();
		}
	}

}
