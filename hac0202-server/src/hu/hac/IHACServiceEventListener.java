/**
 * 
 */
package hu.hac;

/**
 * @author balazs.grill
 *
 */
public interface IHACServiceEventListener {

	public void messageTimeoutOccurred(int msgID);
	
	public void messageSendingFailed(int msgID);
	
	public void messageSendingSucceeded(int msgID);
	
}
