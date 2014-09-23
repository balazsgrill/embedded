/**
 */
package hu.hac.controls;


/**
 * <!-- begin-user-doc -->
 * A representation of the model object '<em><b>Command Line Action</b></em>'.
 * <!-- end-user-doc -->
 *
 * <p>
 * The following features are supported:
 * <ul>
 *   <li>{@link hu.hac.controls.CommandLineAction#getCommand <em>Command</em>}</li>
 * </ul>
 * </p>
 *
 * @see hu.hac.controls.ControlsPackage#getCommandLineAction()
 * @model
 * @generated
 */
public interface CommandLineAction extends Action {

	/**
	 * Returns the value of the '<em><b>Command</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <p>
	 * If the meaning of the '<em>Command</em>' attribute isn't clear,
	 * there really should be more of a description here...
	 * </p>
	 * <!-- end-user-doc -->
	 * @return the value of the '<em>Command</em>' attribute.
	 * @see #setCommand(String)
	 * @see hu.hac.controls.ControlsPackage#getCommandLineAction_Command()
	 * @model
	 * @generated
	 */
	String getCommand();

	/**
	 * Sets the value of the '{@link hu.hac.controls.CommandLineAction#getCommand <em>Command</em>}' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @param value the new value of the '<em>Command</em>' attribute.
	 * @see #getCommand()
	 * @generated
	 */
	void setCommand(String value);
} // CommandLineAction
