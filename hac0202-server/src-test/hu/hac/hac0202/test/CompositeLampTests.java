package hu.hac.hac0202.test;

import hu.hac.IDeviceControl;
import hu.hac.hac0202.server.impl.CompositeLamp;

import org.junit.Assert;
import org.junit.Test;

public class CompositeLampTests {

	private class MockupControl implements IDeviceControl{
		
		private final String id;
		
		public MockupControl(String id) {
			this.id = id;
		}
		
		@Override
		public void requestValue(int value) {
			System.out.println(id+" = "+value);
			Assert.assertTrue(value >= 0 && value < 256);
		}

		@Override
		public void step() {
		}
	}
	
	@Test
	public void test() {
		CompositeLamp lamp = new CompositeLamp(new MockupControl("R"), new MockupControl("P"));
		
		for(int i=0;i<1000;i++){
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			if (i==5){
				lamp.requestValue(100);
			}
			if (i==100){
				lamp.requestValue(255);
			}
			if (i==200){
				lamp.requestValue(0);
			}
			if (i==300){
				lamp.requestValue(255);
			}
			
			lamp.step();
		}
	}

	

}
