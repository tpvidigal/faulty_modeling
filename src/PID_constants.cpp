/**
 * @file    PID_constants.cpp
 * @brief   Global functions implementation of the PID system 
 *
 * @author  Tiago Pereira Vidigal
 * @version 1.0
 *
 */
/*------------------------------------------------------------------------------
 *
 * History
 *
 * Version  Date        Author       Note
 * 1.0      2016/09/07  TVIDIGAL     File created
 *
 *----------------------------------------------------------------------------*/

#include "../hdr/PID_constants.hpp"

#include <iostream>

double bin2double(const char* bin)
{
    union
    {
        unsigned long long i;
        double    d;
    } value;

    int i;
    
    value.i = 0;
    for(i=0; bin[i]!='\0'; i++) {
    	if(bin[i]=='0')
    		value.i =     (value.i << 1);
    	else if (bin[i]=='1')
    		value.i = 1 | (value.i << 1);
    }

    return value.d;
}
