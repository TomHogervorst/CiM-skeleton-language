/*
* nop.h
* SystemC class of 32-bit 0-delay registers
*
* Delft University of Technology
* Computer Engineering Laboratory
*
* Change History:
* Date        Author     Description
* ----------  ---------  -----------------
* 2016-06-21  Tom    Initial version
*
*/

#ifndef _CIM_NOP_H
#define _CIM_NOP_H

#include "reg.h"

class nop: sc_module
{

public:
    // ports
    sc_in<sc_int<32> > input1;
    sc_out<sc_int<32> > output;
    sc_in<bool> clk;
    sc_in<bool> reset;
    sc_out<bool> done;
    sc_in<bool> valid1;

	// module
	reg<0> *reg0;

    // default constructor
    SC_CTOR(nop)
    {
        reg0 = new reg<0>("nop");
		reg0->data_in(input1);
		reg0->data_out(output);
		reg0->clk(clk);
		reg0->reset(reset);
		reg0->done(done);
		reg0->valid(valid1);
    }

}; // end module nop


#endif
