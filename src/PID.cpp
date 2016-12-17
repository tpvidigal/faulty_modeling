/**
 * @file    PID.cpp
 * @brief   Proportional-Integral-Derivative (PID) Controller source
 *
 * @author  Tiago Pereira Vidigal
 * @version 2.4
 *
 */
/*------------------------------------------------------------------------------
 *
 * History
 *
 * Version  Date        Author       Note
 * 1.0      2016/07/14  TVIDIGAL     Super class created for the PIDs.
 * 2.0      2016/08/11  TVIDIGAL     Added methods for SystemVerilog wrapper
 * 2.1      2016/08/12  TVIDIGAL     All methods for SV wrapper implemented
 * 2.2      2016/08/13  TVIDIGAL     doPID now calls calcPID (change was made
 *                                   so and extern "C" call can get the gain)
 *                                   and divided DPI and PID things
 * 2.3      2016/08/24  TVIDIGAL     Adding initialization of the coefficients,
 *                                   correcting time informations and removing
 *                                   method for extern "C" call because UVM
 *                                   Connect appears to be better than the
 *                                   technique at the Cadence's RAK
 * 2.4      2016/09/22  TVIDIGAL     Forcing the doPID to don't initialize
 *
 *----------------------------------------------------------------------------*/

#include "../hdr/PID.hpp"

/* Public *********************************************************************/

PID::PID(sc_module_name inst) : sc_module(inst) {
			
	cout << "Constructing an PID\t" << name() << endl;

	this->error_old = 0.0;
	
	SC_METHOD(doPID);
	sensitive << error;
	dont_initialize();
}
