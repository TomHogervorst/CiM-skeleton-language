/*
* reg.h
* SystemC class of 32-bit registers
*
* Delft University of Technology
* Computer Engineering Laboratory
*
* Change History:
* Date        Author     Description
* ----------  ---------  -----------------
* 2016-02-17  Jintao     Initial version
*
*/

#ifndef _CIM_REG_H
#define _CIM_REG_H

#include <systemc.h>

template <int delay = 1>
class reg: sc_module
{

public:
    // ports
    sc_in<sc_int<32> > data_in;
    sc_out<sc_int<32> > data_out;
    sc_in<bool> clk;
    sc_in<bool> reset;
    sc_out<bool> done;
    sc_in<bool> valid;

    int data;
    int timer;
    bool active;

    void Out(){
  		if (reset.read())
  		{
   			timer = 0;
    		active = false;
 		}
  		else if (valid.read())
  		{
    		data = data_in.read();
			timer = 0;
			if(delay == 0)
    			active = false;
			else
    			active = true;
  		}
  		else if (active)
  		{
    		timer++;
  		}
  
  		if (timer>=delay && delay != 0)
  		{
    		data_out.write(data);
    		done.write(true);
    		active = false;
			timer = 0;
  		}
  		else
  		{
			if(valid.read() && delay == 0){
				done.write(true);
				data_out.write(data);
			}
			else
    			done.write(false);
  		}
	};

    // default constructor
    SC_CTOR(reg)
    {
        // process declarations
        SC_METHOD(Out);
	sensitive << clk.pos();
    }

}; // end module adder


#endif
