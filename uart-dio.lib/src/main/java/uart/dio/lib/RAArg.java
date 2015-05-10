/**
 * 
 */
package uart.dio.lib;

/**
 * @author balazs.grill
 *
 */
public class RAArg implements Arg {

	public boolean RA2 = false;
	public boolean RA4 = false;
	public boolean RA5 = false;

	/* (non-Javadoc)
	 * @see uart.dio.lib.Arg#getData()
	 */
	@Override
	public int getData() {
		int d = 0;
		d += RA2 ? 1 : 0;
		d += RA4 ? 4 : 0;
		d += RA5 ? 8 : 0;
		return d;
	}

}
