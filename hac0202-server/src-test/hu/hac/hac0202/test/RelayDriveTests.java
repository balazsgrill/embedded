package hu.hac.hac0202.test;

import hu.hac.hac0202.server.HAC0202Manager;
import hu.hac.hac0202.server.impl.HAC0202Frame;
import hu.mcp2200.MCP2200Exception;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class RelayDriveTests {

	HAC0202Manager manager;
	
	@Before
	public void setUp() throws Exception {
		manager = new HAC0202Manager();
		manager.getConnection();
	}

	@After
	public void tearDown() throws Exception {
		manager.dispose();
	}

	@Test
	public void test() throws MCP2200Exception, Exception {
		HAC0202Frame frame = new HAC0202Frame(0, 2);
		for(int i=0;i<1000;i++){
			for(HAC0202Frame fr : manager.read()){
				System.out.println(fr);
			}
			
			System.out.println("Sending.."+i);
			manager.send(frame);
			Thread.sleep(1000);
		}
	}

}
