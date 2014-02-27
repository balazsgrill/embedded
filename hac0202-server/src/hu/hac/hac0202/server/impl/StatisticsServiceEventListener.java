/**
 * 
 */
package hu.hac.hac0202.server.impl;

import hu.hac.IHACServiceEventListener;

import java.util.Calendar;

/**
 * @author balazs.grill
 *
 */
public class StatisticsServiceEventListener implements IHACServiceEventListener{

	private final int[][] data; 
	
	private final int maxhours;
	private int current = 0;
	private int lastHour;
	
	public int[][] getData() {
		return data;
	}
	
	public int getCurrent() {
		return current;
	}
	
	/**
	 * 
	 */
	public StatisticsServiceEventListener(int hours) {
		this.maxhours = hours;
		data = new int[maxhours][];
		lastHour = getCurrentHour();
	}
	
	private int getCurrentHour(){
		return Calendar.getInstance().get(Calendar.HOUR_OF_DAY);
	}
	
	private int[] row(){
		int hr = getCurrentHour();
		if (lastHour != hr){
			int diff = hr-lastHour;
			if (diff < 0){
				diff += 24;
			}
			current = (current + diff)%maxhours;
			data[current] = null;
		}
		
		int[] r = data[current];
		if (r == null){
			r = new int[]{0,0,0};
			data[current] = r;
		}
		
		return r;
	}

	@Override
	public synchronized void messageTimeoutOccurred(int msgID) {
		row()[0]++;
	}

	@Override
	public synchronized void messageSendingFailed(int msgID) {
		row()[1]++;
	}

	@Override
	public synchronized void messageSendingSucceeded(int msgID) {
		row()[2]++;
	}

}
