/**
 * @file    Plant.cpp
 * @brief   Plant of the control system source
 *
 * @author  Tiago Pereira Vidigal
 * @version 1.4
 *
 */
/*------------------------------------------------------------------------------
 *
 * History
 *
 * Version  Date        Author       Note
 * 1.0      2016/09/07  TVIDIGAL     Document created.
 * 1.1      2016/09/16  TVIDIGAL     Added matrixes and transports
 * 1.2      2016/09/24  TVIDIGAL     Correcting thread (making it loop)
 * 1.3      2016/10/02  TVIDIGAL     Using state matrix as a pointer and 
 *                                   correcting plantFunction
 * 1.4      2016/10/03  TVIDIGAL     plantFunction validated
 *
 *----------------------------------------------------------------------------*/

#include "../hdr/Plant.hpp"
SC_HAS_PROCESS(Plant);


/* Public ********************************************************************/

//Constructor
Plant::Plant(sc_module_name inst) : sc_module(inst),

	initOut("PlantInitOut"),
	initFeedback("PlantInitFeedback"),
	trgtGain("PlantTrgtGain"),
	m_A(3, 3, (float_pid*) MATRIX_A),
	m_B(3, 1, (float_pid*) MATRIX_B),
	m_C(1, 3, (float_pid*) MATRIX_C)

{
	cout << "Constructing Plant \t" << name() << endl;
	state = new Matrix(3, 1);

	//Transports and methods
	trgtGain.register_b_transport(this, &Plant::doPlant);
	SC_THREAD(threadSendOutput);
	sensitive << send_output;
}


/* Private ********************************************************************/


//Tables

const float_pid Plant::MATRIX_A[][3] = {
	{  -0.313,    56.7,     0.0 },
	{ -0.0139,  -0.426,     0.0 },
	{     0.0,    56.7,     0.0 }
};

const float_pid Plant::MATRIX_B[][1] = {
	{   0.232 },
	{  0.0203 },
	{     0.0 }
};

const float_pid Plant::MATRIX_C[][3] = {
	{     0.0,     0.0,     1.0 }
};


//Methods

void Plant::doPlant(tlm::tlm_generic_payload& trans, sc_time& delay) {
	tlm::tlm_command cmd = trans.get_command();
	unsigned char*   ptr = trans.get_data_ptr();
	unsigned int     len = trans.get_data_length();
	unsigned int     wid = trans.get_streaming_width();

	// Validate payload
	if ( wid != len || len != sizeof(float_pid) )
		SC_REPORT_ERROR("TLM-2", "Invalid payload transaction");

	// Commands
	if ( cmd == tlm::TLM_WRITE_COMMAND )
		memcpy(&(gain), ptr, len);

	else
		SC_REPORT_ERROR("TLM-2", "Invalid command");

	// Response status
	trans.set_response_status( tlm::TLM_OK_RESPONSE );
	send_output.notify(SC_ZERO_TIME);
}

void Plant::threadSendOutput() {
	float_pid output;

	while(true) {

		wait();

		// Initializations
		output = plantFunction(gain);
	    sc_time delay = sc_time(SC_ZERO_TIME);
	    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
	    tlm::tlm_generic_payload* feedb = new tlm::tlm_generic_payload;

		trans->set_command( tlm::TLM_WRITE_COMMAND );
		trans->set_data_ptr( reinterpret_cast<unsigned char*>(&output) );
		trans->set_data_length( sizeof(float_pid) );
		trans->set_streaming_width( sizeof(float_pid) );
		trans->set_dmi_allowed( false );
		trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );
		memcpy(feedb, trans, sizeof(*trans));

		// Transport call
		initOut->b_transport( *trans, delay );
		if ( trans->is_response_error() )
			SC_REPORT_ERROR("TLM-2", "Response error from b_transport");
		wait(delay);

		initFeedback->b_transport( *feedb, delay );
		if ( feedb->is_response_error() )
			SC_REPORT_ERROR("TLM-2", "Response error from b_transport");
		wait(delay);
	}
}

float_pid Plant::plantFunction(float_pid gain) {

	Matrix *f, *df;
	Matrix *aux1, *aux2;
	float output;

	//f = A * states[K] + B * gain
	aux1 = new Matrix(m_A.product(*state));
	aux2 = new Matrix(m_B.productElem(gain));
	f    = new Matrix(aux1->sum(*aux2));

	//df = f * CLK_PERIOD
	df = new Matrix(f->productElem(CLK_PERIOD));

	//output = C * states[K]
	delete aux2;
	aux2 = new Matrix(m_C.product(*state));
	output = aux2->read(0,0);

	//states[K+1] = states[K] + df
	delete aux1;
	aux1 = new Matrix(df->sum(*state));
	delete this->state;
	this->state = new Matrix(*aux1);

	//Exiting
	delete f;
	delete df;
	delete aux1;
	delete aux2;
	return output;
}