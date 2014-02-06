package hu.hac.hac0202.test;

import hu.hac.hac0202.server.HACFrame;

import org.junit.Assert;
import org.junit.Test;

public class FrameTests {

	@Test
	public void test1() {
		HACFrame frame = new HACFrame(1, 125);
		byte[] raw = frame.toRawByte();
		Assert.assertTrue(frame.equals(HACFrame.parseFrame(raw, 0)));
	}
	
	@Test
	public void test2() {
		HACFrame frame = new HACFrame(0, 0);
		byte[] raw = frame.toRawByte();
		Assert.assertTrue(frame.equals(HACFrame.parseFrame(raw, 0)));
	}

	@Test
	public void test3() {
		HACFrame frame = new HACFrame(15, 255);
		byte[] raw = frame.toRawByte();
		Assert.assertTrue(frame.equals(HACFrame.parseFrame(raw, 0)));
	}
	
}
