/**
 * 
 */
package uart.dio.lib;

import jssc.SerialPort;
import jssc.SerialPortException;
import jssc.SerialPortTimeoutException;

/**
 * @author balazs.grill
 *
 */
public class UARTDioInterface implements AutoCloseable {
	
	private final SerialPort port;
	
	/**
	 * @throws SerialPortException 
	 * 
	 */
	public UARTDioInterface(String portName) throws SerialPortException {
		port = new SerialPort(portName);
		port.openPort();
		port.setParams(9600, 1, 0, 0);
	}
	
	@Override
	public void close() throws SerialPortException{
		port.closePort();
	}

	public void sendCommand(UARTDioCommand command, int argument) throws SerialPortException{
		port.writeByte(command.getByte(argument));
	}
	
	public ReadData read() throws SerialPortException{
		byte[] data;
		try {
			data = port.readBytes(1, 1000);
			if (data != null && data.length > 0){
				return UARTDioCommand.parse(data[0]);
			}
			return null;
		} catch (SerialPortTimeoutException e) {
			return null;
		}
	}
	
}
