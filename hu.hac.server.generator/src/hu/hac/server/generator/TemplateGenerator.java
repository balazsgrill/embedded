/**
 * 
 */
package hu.hac.server.generator;

import hu.hac.controls.Action;
import hu.hac.controls.Button;
import hu.hac.controls.CommandLineAction;

import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Map.Entry;

import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.emf.ecore.resource.impl.ResourceSetImpl;

/**
 * @author balazs.grill
 *
 */
public class TemplateGenerator {

	private final ResourceSet resourceSet;
	
	private final Map<String, Action> actions = new LinkedHashMap<>();
	
	private int actionIdCounter = 0;
	
	/**
	 * 
	 */
	public TemplateGenerator() {
		resourceSet = new ResourceSetImpl();
	}
	
	private String getElementText(EObject element){
		StringBuilder sb = new StringBuilder();
		if (element instanceof Button){
			String label = ((Button) element).getLabel();
			String actionID = "action"+actionIdCounter; actionIdCounter++; 
			Action action = ((Button) element).getAction();
			actions.put(actionID, action);
			
			sb.append("<form action=\"\" method=\"get\">");
			sb.append("<input type=\"hidden\" value=\"");sb.append(actionID);sb.append("\"/>");
			sb.append("<input type=\"submit\" value=\"");sb.append(label);sb.append("\"/>");
			sb.append("</form>");
		}
		return sb.toString();
	}
	
	private String getControlText(String item){
		Resource resource = new ControlResource(null);
		resourceSet.getResources().add(resource);
		
		try(InputStream is = new ByteArrayInputStream(item.getBytes())){
			resource.load(is, null);
			
			EObject element = resource.getContents().get(0);
			return getElementText(element);
			
		}catch (Exception e) {
			e.printStackTrace();
			return e.getLocalizedMessage();
		}
		
	}
	
	private String getOutput(File template) throws IOException{
		try (InputStream in = new FileInputStream(template)){
			byte[] data = new byte[in.available()];
			in.read(data);
			String input = new String(data);
			
			StringBuilder sb = new StringBuilder();
			
			int next = -1;
			int position = 0;
			while( (next = input.indexOf("{{", position)) != -1 ){
				if (next > position){
					sb.append(input.substring(position, next));
					position = next+2;
				}
				
				int end = input.indexOf("}}", next);
				if (end != -1){
					String item = input.substring(next+2, end);
					sb.append(getControlText(item));
					position = end+2;
				}
				
			}
			
			return sb.toString();
		}
	}
	
	public void generate(File template, File targetDir, String qualifiedName) throws IOException{
		String packName = "";
		String className = "";
		
		int dot = qualifiedName.lastIndexOf('.');
		if (dot == -1){
			className = qualifiedName;
		}else{
			packName = qualifiedName.substring(0, dot);
			className = qualifiedName.substring(dot+1);
		}
		
		File dir = targetDir;
		for(String p : packName.split("\\.")){
			if (!p.isEmpty()){
				dir = new File(dir, p);
			}
		}
		
		File outputFile = new File(dir,className+".java");
		
		
		String output = getOutput(template);
		byte[] outputData = output.getBytes(StandardCharsets.UTF_8);
		
		StringBuilder sb = new StringBuilder();
		if (!packName.isEmpty()){
			sb.append("package ");
			sb.append(packName);
			sb.append(";\n");
		}
		
		sb.append("import hu.hac.server.IControlPage;\n");
		sb.append("import hu.hac.server.IControlAction;\n");
		sb.append("import hu.hac.server.CommandLineAction\n");
		
		sb.append("public class ");sb.append(className);
		sb.append(" implements IControlPage");sb.append("{\n");
		{
			sb.append("private final byte[] outputData = {");
			boolean first = true;
			for(int i=0;i<outputData.length;i++){
				if (first) first=false; else sb.append(", ");
				sb.append(outputData[i]);
			}
			sb.append("};\n");
		}
		
		sb.append("@Override\npublic byte[] getPage(){\n\treturn outputData;\n}\n");
		
		sb.append("@Override\npublic IControlAction getAction(String actionID, Map<String, String> options){\n");
		sb.append("\tswitch(actionID){\n");
		for(Entry<String, Action> actionEntry : actions.entrySet()){
			sb.append("\t\tcase \"");sb.append(actionEntry.getKey());sb.append("\":\t\t");
			sb.append("return ");
			Action a = actionEntry.getValue();
			if (a instanceof CommandLineAction){
				sb.append("new CommandLineAction(\"");
				sb.append(((CommandLineAction) a).getCommand());
				sb.append("\");\n");
				
			}else{
				sb.append("null;\n");
			}
		}
		sb.append("\tdefault: return null;\n\t}\n");
		sb.append("}\n");
		
		sb.append("}");
		
		dir.mkdirs();
		try(OutputStream out = new FileOutputStream(outputFile)){
			out.write(sb.toString().getBytes(StandardCharsets.UTF_8));
			out.flush();
		}
	}

}
