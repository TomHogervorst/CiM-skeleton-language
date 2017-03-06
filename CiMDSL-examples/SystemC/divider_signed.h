/*
* divider_signed.h
* SystemC class of 32-bit signed divider
*
* Delft University of Technology
* Computer Engineering Laboratory
*
* Change History:
* Date        Author     Description
* ----------  ---------  -----------------
* 2016-02-17  Jintao     Initial version
* 2016-06-21  Tom		 Version suitable for generated systemC
*
*/

#ifndef _CIM_DIVIDER_SIGNED_H
#define _CIM_DIVIDER_SIGNED_H

#define DIV_DELAY 6064

#include <systemc.h>

class divider_signed: sc_module
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

    bool active;
    int timer;
    int a_in;
    int b_in;
	bool check1, check2;

    void DivNumbers();

    // default constructor
    SC_CTOR(divider_signed)
    {
        timer = 0;
		active = false;
		check1 = false;
		check2 = false;
        // process declarations
        SC_METHOD(DivNumbers);
	sensitive << clk.pos();
    }

}; // end module adder

#endif
