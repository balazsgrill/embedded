package hu.hac.hac0202.test;

import hu.hac.hac0202.server.impl.HAC0202Frame;

import org.junit.Assert;
import org.junit.Test;

public class FrameTests {

	@Test
	public void test1() {
		HAC0202Frame frame = new HAC0202Frame(1, 125);
		byte[] raw = frame.toRawByte();
		Assert.assertTrue(frame.equals(HAC0202Frame.parseFrame(raw, 0)));
	}
	
	@Test
	public void test2() {
		HAC0202Frame frame = new HAC0202Frame(0, 0);
		byte[] raw = frame.toRawByte();
		Assert.assertTrue(frame.equals(HAC0202Frame.parseFrame(raw, 0)));
	}

	@Test
	public void test3() {
		HAC0202Frame frame = new HAC0202Frame(15, 255);
		byte[] raw = frame.toRawByte();
		Assert.assertTrue(frame.equals(HAC0202Frame.parseFrame(raw, 0)));
	}
	
}
