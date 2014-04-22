package hu.hac;
import hu.hac.server.IControlPage;
import hu.hac.server.IControlAction;
import hu.hac.server.CommandLineAction
public class TestControl implements IControlPage{
private final byte[] outputData = {60, 33, 68, 79, 67, 84, 89, 80, 69, 32, 104, 116, 109, 108, 62, 10, 60, 104, 116, 109, 108, 62, 10, 60, 104, 101, 97, 100, 62, 10, 60, 109, 101, 116, 97, 32, 99, 104, 97, 114, 115, 101, 116, 61, 34, 85, 84, 70, 45, 56, 34, 62, 10, 60, 116, 105, 116, 108, 101, 62, 73, 110, 115, 101, 114, 116, 32, 116, 105, 116, 108, 101, 32, 104, 101, 114, 101, 60, 47, 116, 105, 116, 108, 101, 62, 10, 60, 47, 104, 101, 97, 100, 62, 10, 60, 98, 111, 100, 121, 62, 10, 10, 110, 117, 108, 108};
@Override
public byte[] getPage(){
	return outputData;
}
@Override
public IControlAction getAction(String actionID, Map<String, String> options){
	switch(actionID){
	default: return null;
	}
}
}