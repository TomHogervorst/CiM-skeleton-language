/*
* gt.h
* SystemC class of 32-bit comparator, that give 1 if the first input is larger than the second one.
*
* Delft University of Technology
* Computer Engineering Laboratory
*
* Change History:
* Date        Author     Description
* ----------  ---------  -----------------
* 2016-06-21  Tom     Initial version
*
*/

#ifndef _CIM_GT_H
#define _CIM_GT_H

#define GT_DELAY 20

#include <systemc.h>

class gt: sc_module
{

public:
    // ports
    sc_in<sc_int<32> > input1;
    sc_in<sc_int<32> > input2;
    sc_out<sc_int<32> > output;
    sc_in<bool> clk;
    sc_in<bool> reset;
    sc_out<bool> done;
    sc_in<bool> valid1;
	sc_in<bool> valid2;

    int timer;
    bool active;
	bool check1, check2;
    int a_in;
    int b_in;

    void CompareNumbers();

    // default constructor
    SC_CTOR(gt)
    {
        timer = 0;
        active = false;
		check1 = false;
		check2 = false;
        // process declarations
        SC_METHOD(CompareNumbers);
		sensitive << clk.pos();
    }

}; // end module adder

#endif
