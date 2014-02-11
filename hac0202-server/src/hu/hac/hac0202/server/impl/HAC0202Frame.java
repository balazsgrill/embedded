/**
 * 
 */
package hu.hac.hac0202.server.impl;

/**
 * @author balazs.grill
 *
 */
public class HAC0202Frame {

	private final int id;
	private final int data;
	
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
	
	public int getCheckCode(){
		int check = 0xFFFF;
		check -= id;
		check -= data & 0xf;
		check -= (data >> 4) & 0xf;
		return check & 0xf;
	}
	
	/**
	 * 
	 */
	public HAC0202Frame(int id, int data) {
		if (id < 0 || id > 15) throw new IllegalArgumentException("Frame ID must be between 0 and 15");
		if (data < 0 || data > 255) throw new IllegalArgumentException("Frame data must be between 0 and 255");
		this.id = id;
		this.data = data;
	}
	
	public byte[] toRawByte(){
		int check = getCheckCode();
		int head = (check << 4) + id;
		return new byte[]{ intToByte(head), intToByte(data) };
	}
	
	public static HAC0202Frame parseFrame(byte[] data, int index){
		int head = byteToInt(data[index]);
		int payload = byteToInt(data[index+1]);
		
		int id = head & 0xf;
		int check = (head >> 4) & 0xf;
		HAC0202Frame frame = new HAC0202Frame(id, payload);
		if (check == frame.getCheckCode()){
			return frame;
		}else{
			return null;
		}
	}
	
	@Override
	public String toString() {
		return "FRAME["+id+"] = "+data;
	}
	
	@Override
	public int hashCode() {
		return id*256+data;
	}
	
	@Override
	public boolean equals(Object arg0) {
		if (arg0 instanceof HAC0202Frame){
			HAC0202Frame other = (HAC0202Frame)arg0;
			return (id == other.id) && (data == other.data);
		}
		return super.equals(arg0);
	}
	
	public int getId() {
		return id;
	}
	
	public int getData() {
		return data;
	}
	
}
