/**
 * 
 */
package hu.hac.hac0202.server;

/**
 * @author balage
 *
 */
public interface IHAC0202Service {

	public void relay1(boolean on);
	
	public void relay2(boolean on);
	
	public void pwm1(float value, float rampSpeed);
	
	public void pwm2(float value, float rampSpeed);
}
