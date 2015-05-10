/**
 * 
 */
package uart.dio.java;

import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;
import jssc.SerialPortException;

import org.junit.Test;

import uart.dio.lib.UARTDioCommand;
import uart.dio.lib.UARTDioInterface;

/**
 * @author inovo8
 *
 */
public class ConnectionTest {

	@Test
	public void NOPTest() throws SerialPortException{
		try(UARTDioInterface inf = new UARTDioInterface("COM3")){
			for(int i=0;i<1000;i++){
				inf.sendCommand(UARTDioCommand.NOP, 0);
			}
		}
	}
	
	@Test
	public void test() throws SerialPortException {
		try(UARTDioInterface inf = new UARTDioInterface("COM3")){
			assertNull(inf.read());
			inf.sendCommand(UARTDioCommand.READ255, 0);
			assertNotNull(inf.read());
			assertNull(inf.read());
		}
	}

}
