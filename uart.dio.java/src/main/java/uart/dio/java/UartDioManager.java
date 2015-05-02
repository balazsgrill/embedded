package uart.dio.java;

import java.io.InputStream;
import java.io.OutputStream;

public class UartDioManager {

	private final InputStream rx;
	private final OutputStream tx;
	
	/**
	 * 
	 */
	public UartDioManager(InputStream rx, OutputStream tx) {
		this.rx=rx;
		this.tx=tx;
	}

}
