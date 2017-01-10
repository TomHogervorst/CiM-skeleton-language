/*
* adder_signed.h
* SystemC class of 32-bit comparator.
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

#ifndef _CIM_ADDER_SIGNED_H
#define _CIM_ADDER_SIGNED_H

#define ADD_DELAY 180

#include <systemc.h>

class adder_signed: sc_module
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

    void AddNumbers();

    // default constructor
    SC_CTOR(adder_signed)
    {
        timer = 0;
        active = false;
		check1 = false;
		check2 = false;
        // process declarations
        SC_METHOD(AddNumbers);
		sensitive << clk.pos();
    }

}; // end module adder

#endif
