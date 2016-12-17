/**
 * @file    Control_System.cpp
 * @brief   Control System of a Control Surface of an Aircraft source
 *
 * @author  Tiago Pereira Vidigal
 * @version 2.0
 *
 */
/*------------------------------------------------------------------------------
 *
 * History
 *
 * Version  Date        Author       Note
 * 1.0      2016/09/19  TVIDIGAL     Document created.
 * 1.1      2016/09/21  TVIDIGAL     Copying and sending transaction and
 *                                   adding PID type configuration method.
 * 2.0      2016/10/17  TVIDIGAL     Adding actuator
 *
 *----------------------------------------------------------------------------*/

#include "../hdr/Control_System.hpp"


/* Public ********************************************************************/

//Constructor
Control_System::Control_System(sc_module_name inst, PID* pid, bool enable_faults) : sc_module(inst),

	initOutput("SystemInitOutput"),
	initSetpoint("SystemInitSetpoint"),
	trgtOutput("SystemTrgtOutput"),
	trgtSetpoint("SystemTrgtSetpoint"),
	subtractor("Subtractor"),
	actuator("Actuator"),
	plant("Plant"),
	fi_manager("FaultManager")

{
	cout << "Constructing System\t" << name();
	if(enable_faults) cout << " (Faults enabled)";
	cout << endl;

	this->pid = new PID_TLM("SystemPID", pid);
	trgtOutput.register_b_transport(this, &Control_System::receiveOutput);
	trgtSetpoint.register_b_transport(this, &Control_System::receiveSetpoint);

	this->initSetpoint.bind( subtractor.trgtSetpoint );
	subtractor.initError.bind( this->pid->trgtError );
	this->pid->initGain.bind( actuator.trgtGain );
	actuator.initGain.bind( plant.trgtGain );
	plant.initFeedback.bind( subtractor.trgtOutput );
	plant.initOut.bind( this->trgtOutput );

	this->enable_faults = enable_faults;
}


/* Private *******************************************************************/

void Control_System::receiveSetpoint(tlm::tlm_generic_payload& trans, sc_time& delay) {

	//Inject faults (if enabled)
	if(enable_faults)
		fi_manager.inject_faults.notify(SC_ZERO_TIME);

	//Copy and send transport
	tlm::tlm_generic_payload* trans_copied = new tlm::tlm_generic_payload;
	memcpy(trans_copied, &trans, sizeof(trans));
	initSetpoint->b_transport( *trans_copied, delay );

	// Check response status and delay
	if ( trans_copied->is_response_error() )
		SC_REPORT_ERROR("TLM-2", "Response error from b_transport");
	wait(delay);

	// Response original transport
	trans.set_response_status( tlm::TLM_OK_RESPONSE );
}

void Control_System::receiveOutput(tlm::tlm_generic_payload& trans, sc_time& delay) {

	//Copy and send transport
	tlm::tlm_generic_payload* trans_copied = new tlm::tlm_generic_payload;
	memcpy(trans_copied, &trans, sizeof(trans));
	initOutput->b_transport( *trans_copied, delay );

	// Check response status and delay
	if ( trans_copied->is_response_error() )
		SC_REPORT_ERROR("TLM-2", "Response error from b_transport");
	wait(delay);

	// Response original transport
	trans.set_response_status( tlm::TLM_OK_RESPONSE );
}