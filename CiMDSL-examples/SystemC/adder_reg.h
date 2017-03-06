/*
* adder_reg.h
* SystemC class of one adder and two registers
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

#ifndef _CIM_ADDER_REG_H
#define _CIM_ADDER_REG_H

#include "reg.h"
#include "adder_signed.h"

template <int input_size = 2, int output_size = 1>
class adder_reg: sc_module
{
public:
    // ports
    sc_in<sc_int<32> > *input_sigs;
    sc_out<sc_int<32> > *output_sigs;
    sc_in<bool> clk;
    sc_in<bool> reset;
    sc_out<bool> done;
    sc_in<bool> valid;

    adder_signed *mod1;
    reg<0> *r11;
    reg<0> *r12;

    sc_signal<sc_int<32> > r11_out;
    sc_signal<sc_int<32> > r12_out;
    sc_signal<bool> r11_done;
    sc_signal<bool> r12_done;

    // default constructor
    SC_CTOR(adder_reg)
    {
	  input_sigs = new sc_in<sc_int<32> >[input_size];
	  output_sigs = new sc_out<sc_int<32> >[output_size];
	  r11 = new reg<0>("r11");
	  r12 = new reg<0>("r12");
	  mod1 = new adder_signed("mod1");

      r11->clk(clk);
      r11->reset(reset);
      r11->data_in(input_sigs[0]);
      r11->data_out(r11_out);
      r11->valid(valid);
      r11->done(r11_done);

      r12->clk(clk);
      r12->reset(reset);
      r12->data_in(input_sigs[1]);
      r12->data_out(r12_out);
      r12->valid(valid);
      r12->done(r12_done);

      mod1->clk(clk);
      mod1->reset(reset);
      mod1->a(r11_out);
      mod1->b(r12_out);
      mod1->output(output_sigs[0]);
      mod1->valid1(r11_done);
	  mod1->valid2(r12_done);
      mod1->done(done);
    }

}; // end module adder

#endif
