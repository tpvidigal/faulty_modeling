/**
 * @file    PID_constants.hpp
 * @brief   Global constants of the PID system 
 *
 * @author  Tiago Pereira Vidigal
 * @version 2.1
 *
 */
/*------------------------------------------------------------------------------
 *
 * History
 *
 * Version  Date        Author       Note
 * 1.0      2016/04/26  TVIDIGAL     File created
 * 1.1      2016/07/13  TVIDIGAL     Excluding bit precise types
 * 1.2      2016/08/24  TVIDIGAL     Using same coefficients as Prof. Muñoz
 *                                   that contain time information
 * 1.3      2016/09/07  TVIDIGAL     Method to use files with binary
 *                                   representations of floats
 * 1.4      2016/09/14  TVIDIGAL     Added absolute error constant and
 *                                   changed CLK_PERIOD to 0.1 (second) to
 *                                   match the Matlab's new fixed simulation
 *                                   step size.
 * 1.5      2016/10/03  TVIDIGAL     Creating error constants for PID and
 *                                   System testbenches
 * 1.6      2016/10/17  TVIDIGAL     Creating Plant and Actuator error constants
 * 2.0      2016/10/31  TVIDIGAL     Added enumeration for fault type
 * 2.1      2016/11/07  TVIDIGAL     Added proxy structure to use method pointer
 *                                   easier in faulty modules
 *
 *----------------------------------------------------------------------------*/

#ifndef PID_CONSTANTS_H_
#define PID_CONSTANTS_H_

class FaultyBuffer;


/* General ********************************************************************/

///Clock Period in seconds
#define CLK_PERIOD 0.1

///Duty cycle of the clock
#define CLK_DUTY 0.5

///Define if file read is binary
//#define BINARY_FILE

///Absolute error on the comparison of PID outputs
#define ERROR_PID 0.014453

///Absolute error on the comparison of Plant outputs
#define ERROR_PLANT 0.000118

///Absolute error on the comparison of Actuator outputs
#define ERROR_ACTUATOR 0.000001

///Absolute error on the comparison of System outputs
#define ERROR_SYS 0.05


///Time where step changes it value from zero
#define STEP_RISE_TIME 5.0

///Lambda value of the exponential distribution
#define EXP_DIST_LAMBDA 1


/* Types and Enumerations *****************************************************/

///Floating point type to use in the PID
typedef double float_pid;

///Fault Injection method pointer type
typedef void (FaultyBuffer::*FI_METHOD)(void);

///Proxy structure to convert fault injection method pointers
struct FIMethod
{
	FIMethod( FI_METHOD pp ) : p( pp ) { }
	operator FI_METHOD() { return p; }
	FI_METHOD p;
};

///Enumeration with types of fault
enum FAULT_TYPE { STUCK_AT_0 };


/* Coefficients ***************************************************************/

#define KP_DEFAULT 0.578125 
#define KI_DEFAULT 0.541992 //KP * 0.9375 = 0.541992188
#define KD_DEFAULT 0.469727 //KP * 0.8125 = 0.469726563


/* Methods ********************************************************************/

double bin2double(const char* binstr);

#endif /* PID_CONSTANTS_H_ */
