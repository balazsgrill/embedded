/**
 * 
 */
package hu.hac.server.generator;

import org.eclipse.emf.common.util.URI;

import hu.textualmodeler.grammar.GrammarModel;
import hu.textualmodeler.parser.AbstractTextualResource;
import hu.textualmodeler.parser.BasicFeatureResolver;
import hu.textualmodeler.parser.IFeatureResolver;
import hu.textualmodeler.parser.grammar.GrammarRegistry;

/**
 * @author balazs.grill
 *
 */
public class ControlResource extends AbstractTextualResource {

	/**
	 * @param uri
	 */
	public ControlResource(URI uri) {
		super(uri);
	}

	/* (non-Javadoc)
	 * @see hu.textualmodeler.parser.AbstractTextualResource#loadGrammar()
	 */
	@Override
	protected GrammarModel loadGrammar() {
		return GrammarRegistry.getInstance().getGrammar("hac.controls");
	}

	/* (non-Javadoc)
	 * @see hu.textualmodeler.parser.AbstractTextualResource#createFeatureResolver()
	 */
	@Override
	protected IFeatureResolver createFeatureResolver() {
		return new BasicFeatureResolver(getResourceSet());
	}

}
