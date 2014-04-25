/**
 * 
 */
package hu.hac.server.generator;

import java.io.File;

import org.eclipse.equinox.app.IApplication;
import org.eclipse.equinox.app.IApplicationContext;

/**
 * @author balazs.grill
 *
 */
public class Application implements IApplication {

	/* (non-Javadoc)
	 * @see org.eclipse.equinox.app.IApplication#start(org.eclipse.equinox.app.IApplicationContext)
	 */
	@Override
	public Object start(IApplicationContext context) throws Exception {
		String args[] = (String[])context.getArguments().get("application.args");
		
		if (args.length != 3){
			throw new Exception("Illegal arguments");
		}
		
		String template = args[0];
		String destination = args[1];
		String className = args[2];
		
		TemplateGenerator gen = new TemplateGenerator();
		gen.generate(new File(template), new File(destination), className);
			
		return null;
	}

	/* (non-Javadoc)
	 * @see org.eclipse.equinox.app.IApplication#stop()
	 */
	@Override
	public void stop() {
		// TODO Auto-generated method stub

	}

}
