/**
 * 
 */
package uart.dio.lib;

import jssc.SerialPort;
import jssc.SerialPortException;

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
		port.setParams(9600, 1, 0, 0);
		port.openPort();
	}
	
	@Override
	public void close() throws SerialPortException{
		port.closePort();
	}

	public void sendCommand(UARTDioCommand command, int argument) throws SerialPortException{
		port.writeByte(command.getByte(argument));
	}
	
	public ReadData read() throws SerialPortException{
		byte[] data = port.readBytes(1);
		if (data != null && data.length > 0){
			return UARTDioCommand.parse(data[0]);
		}
		return null;
	}
	
}
