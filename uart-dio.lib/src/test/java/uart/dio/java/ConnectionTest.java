/**
 * 
 */
package uart.dio.java;

import static org.junit.Assert.*;
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
	public void test() throws SerialPortException {
		try(UARTDioInterface inf = new UARTDioInterface("")){
			assertNull(inf.read());
			inf.sendCommand(UARTDioCommand.READ, 0);
			assertNotNull(inf.read());
			assertNull(inf.read());
		}
	}

}
