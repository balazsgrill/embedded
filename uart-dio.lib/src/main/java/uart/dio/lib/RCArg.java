package uart.dio.lib;

public class RCArg implements Arg {

	public boolean RC0 = false;
	public boolean RC1 = false;
	public boolean RC2 = false;
	public boolean RC3 = false;
	
	@Override
	public int getData() {
		int d = 0;
		d += RC0 ? 1 : 0;
		d += RC1 ? 2 : 0;
		d += RC2 ? 4 : 0;
		d += RC3 ? 8 : 0;
		return d;
	}

}
