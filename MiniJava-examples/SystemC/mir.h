/*
* mir.h
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

#ifndef _CIM_MIR_H
#define _CIM_MIR_H

#include "reg.h"

class mir: sc_module
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
	reg<0> *reg1;

    // default constructor
    SC_CTOR(mir)
    {
        reg1 = new reg<0>("mir");
		reg1->data_in(input1);
		reg1->data_out(output);
		reg1->clk(clk);
		reg1->reset(reset);
		reg1->done(done);
		reg1->valid(valid1);
    }

}; // end module mir


#endif
