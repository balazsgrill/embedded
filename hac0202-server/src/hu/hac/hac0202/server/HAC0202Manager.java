package hu.hac.hac0202.server;

import hu.hac.hac0202.server.impl.HAC0202Frame;
import hu.mcp2200.IMCP2200Connection;
import hu.mcp2200.IMCP2200Device;
import hu.mcp2200.MCP2200Configuration;
import hu.mcp2200.MCP2200Exception;
import hu.mcp2200.MCP2200JNI;
import hu.mcp2200.MCP2200Manager;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

public class HAC0202Manager {

	private IMCP2200Device device;
	private IMCP2200Connection connection;
	
	public IMCP2200Device getDevice() throws Exception {
		if (device == null){
			Collection<IMCP2200Device> devices = MCP2200Manager.detectDevices();
			if (!devices.isEmpty()){
				device = devices.iterator().next();
				try {
					connection = device.connect();
					MCP2200Configuration config = new MCP2200Configuration();
					config.desiredBaudRate = 9600;
					connection.configure(config);
				} catch (MCP2200Exception e) {
					device = null;
					throw e;
				}
			}
		}
		if (device == null){
			throw new Exception("Device not found!");
		}
		return device;
	}
	
	public void disconnect(){
		if (connection != null){
			connection.dispose();
			connection = null;
			device = null;
		}
	}
	
	public IMCP2200Connection getConnection() throws Exception{
		getDevice();
		return connection;
	}
	
	public HAC0202Manager() {
		MCP2200JNI.getInstance().init();	
	}
	
	public void send(HAC0202Frame frame) throws MCP2200Exception, Exception{
		try{
			getConnection().send(frame.toRawByte());
		}catch(MCP2200Exception e){
			
		}
	}
	
	private byte[] leftovers = new byte[0];
	
	public HAC0202Frame[] read() throws MCP2200Exception, Exception{
		List<HAC0202Frame> result = new ArrayList<>(32);
		byte[] data = new byte[64];
		int r = getConnection().receive(data);
		if (r == 0) return new HAC0202Frame[0];
		int index = 0;
		
		if (leftovers.length > 0){
			byte[] newdata = new byte[r+leftovers.length];
			System.arraycopy(leftovers, 0, newdata, 0, leftovers.length);
			System.arraycopy(data, 0, newdata, leftovers.length, r);
			data = newdata;
			r = newdata.length;
		}
		
		StringBuilder sb = new StringBuilder();
		for(int i=0;i<r;i++){
			int d = HAC0202Frame.byteToInt(data[i]);
			String s = Integer.toHexString(d);
			if (s.length() == 1) sb.append("0");
			sb.append(s);sb.append(" ");
		}
		
		while(r-index >= 2){
			HAC0202Frame frame = HAC0202Frame.parseFrame(data, index);
			if (frame != null){
				result.add(frame);
				index += 2;
			}else{
				/* Drop byte */
				index++;
			}
		}
		
		leftovers = new byte[r-index];
		System.arraycopy(data, index, leftovers, 0, leftovers.length);
		
		return result.toArray(new HAC0202Frame[result.size()]);
	}

	public void dispose(){
		MCP2200JNI.getInstance().close();
	}
	
}
