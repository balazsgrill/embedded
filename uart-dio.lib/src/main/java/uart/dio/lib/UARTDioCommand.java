/**
 * 
 */
package uart.dio.lib;

/**
 * @author balazs.grill
 *
 */
public enum UARTDioCommand {
//	* 0: Set TRISA (1 = input, 0 = output)
	TRISA_SET(0),
//	 * 1: Set TRISC (1 = input, 0 = output)
	TRISC_SET(1),
//	 * 2: OR LATA
	LATA_OR(2),
//	 * 3: OR LATC
	LATC_OR(3),
//	 * 4: AND LATA
	LATA_AND(4),
//	 * 5: AND LATC
	LATC_AND(5),
//	 * 6: SET LATA
	LATA_SET(6),
//	 * 7: SET LATC
	LATC_SET(7),
//	 * 8: XOR LATA
	LATA_XOR(8),
//	 * 9: XOR LATC
	LATC_XOR(9),
//	 * 13: Read255
	READ255(13),
//	 * 14: Read
	READ(14),
//	 * 15: NOP
	NOP(15)
	;
	
	public static int byteToInt(byte b){
		if (b < 0)
			return 256+b;
		else
			return (int)b;
	}
	
	public static byte intToByte(int b){
		int n = b & 0xFF;
		if (n < 128) 
			return (byte)n;
		else
			return (byte)(n - 256);
	}
	
	private UARTDioCommand(int code){
		this.code = code;
	}
	
	public final int code;
	
	public byte getByte(int argument){
		int b = (code & 0xF) + ((argument & 0xF) << 4);
		return intToByte(b);
	}
	
	public byte getByte(Arg argument){
		return getByte(argument.getData());
	}
	
	public static ReadData parse(byte input){
		int data = byteToInt(input);
		RAArg RA = new RAArg();
		RCArg RC = new RCArg();
		
		RA.RA2 = ((data & 1) != 0);
		RA.RA4 = ((data & 4) != 0);
		RA.RA5 = ((data & 8) != 0);
		
		RC.RC0 = ((data & 16) != 0);
		RC.RC1 = ((data & 32) != 0);
		RC.RC2 = ((data & 64) != 0);
		RC.RC3 = ((data & 128) != 0);
		
		return new ReadData(RA, RC);
	}
	
}
