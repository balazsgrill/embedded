package hu.hac;

import java.util.Map;

import hu.hac.server.IControlPage;
import hu.hac.server.IControlAction;
import hu.hac.server.CommandLineAction;
import hu.hac.server.AbstractControlPageServlet;

public class TestControl extends AbstractControlPageServlet implements IControlPage{


private static final long serialVersionUID = 3638065393572224000L;

private final byte[] outputData = {
		  60,  33,  68,  79,  67,  84,  89,  80,  69,  32, 104, 116, 109, 108,  62,  10,  60, 104, 116, 109,
		 108,  62,  10,  60, 104, 101,  97, 100,  62,  10,  60, 109, 101, 116,  97,  32,  99, 104,  97, 114,
		 115, 101, 116,  61,  34,  85,  84,  70,  45,  56,  34,  62,  10,  60, 116, 105, 116, 108, 101,  62,
		  73, 110, 115, 101, 114, 116,  32, 116, 105, 116, 108, 101,  32, 104, 101, 114, 101,  60,  47, 116,
		 105, 116, 108, 101,  62,  10,  60,  47, 104, 101,  97, 100,  62,  10,  60,  98, 111, 100, 121,  62,
		  10,  10,  60, 102, 111, 114, 109,  32,  97,  99, 116, 105, 111, 110,  61,  34,  34,  32, 109, 101,
		 116, 104, 111, 100,  61,  34, 103, 101, 116,  34,  62,  60, 105, 110, 112, 117, 116,  32, 116, 121,
		 112, 101,  61,  34, 104, 105, 100, 100, 101, 110,  34,  32, 110,  97, 109, 101,  61,  34,  97,  99,
		 116, 105, 111, 110, 105, 100,  34,  32, 118,  97, 108, 117, 101,  61,  34,  97,  99, 116, 105, 111,
		 110,  48,  34,  47,  62,  60, 105, 110, 112, 117, 116,  32, 116, 121, 112, 101,  61,  34, 115, 117,
		  98, 109, 105, 116,  34,  32, 118,  97, 108, 117, 101,  61,  34,  84,  69,  83,  84,  34,  47,  62,
		  60,  47, 102, 111, 114, 109,  62
	};

@Override
public IControlPage getPage(){
	return this;
}

@Override
public byte[] getPageContent(){
	return outputData;
}

@Override
public IControlAction getAction(String actionID, Map<String, String> options){
	switch(actionID){
		case "action0":		return new CommandLineAction("echo test");
	default: return null;
	}
}
}