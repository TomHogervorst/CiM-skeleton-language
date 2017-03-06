/*
* mux2.h
* SystemC class of 2-input 32-bit multiplexer
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

#ifndef _CIM_MUX2_H
#define _CIM_MUX2_H

#define MUX2_DELAY 30

#include <systemc.h>

class mux2: sc_module
{

public:
    // ports
    sc_in<sc_int<32> > input1;
    sc_in<sc_int<32> > input2;
	sc_in<sc_int<32> > input3;
    sc_out<sc_int<32> > output;
    sc_in<bool> clk;
    sc_in<bool> reset;
    sc_out<bool> done;
    sc_in<bool> valid1;
	sc_in<bool> valid2;
	sc_in<bool> valid3;

    int timer;
    bool active;
	bool check1, check2, check3;
    int a_in;
    int b_in;
	int c_in;

    void SelectNumber();

    // default constructor
    SC_CTOR(mux2)
    {
        timer = 0;
        active = false;
		check1 = false;
		check2 = false;
		check3 = false;
        // process declarations
        SC_METHOD(SelectNumber);
		sensitive << clk.pos();
    }

}; // end module adder

#endif
