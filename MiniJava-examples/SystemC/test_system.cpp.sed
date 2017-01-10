/*
* test_adder_reg.cpp
* Test file for adder_reg module
*
* Delft University of Technology
* Computer Engineering Laboratory
*
* Change History:
* Date        Author     Description
* ----------  ---------  -----------------
* 2016-02-18  Jintao     Initial version
*
*/

#include "generated_system.h"
#include <stdlib.h>
#include <stdio.h>


int sc_main(int argc, char* argv[])
{
  sc_core::sc_report_handler::set_actions( "/IEEE_Std_1666/deprecated",
                                           sc_core::SC_DO_NOTHING );

  sc_clock clk("clock", 1, 0.5);
  sc_signal<sc_int<32> > *inputs;
  sc_signal<sc_int<32> > *outputs;
  sc_signal<bool> reset;
  sc_signal<bool> *dones;
  sc_signal<bool> valid;

  int INSIZE = IN_SIZE;
  int OUTSIZE = OUT_SIZE;
  //int STEP_SIZE = 10;
  int MAX_STEPS = 50000;
  int k = 0;
  int temp;
  int inArray[16] = {1,0,4,2,2,1,8,7,0,2,1,8,0,1,2,8};

  generated_system<IN_SIZE, OUT_SIZE> gen_sys("system");

  

  printf("Generated system successfully.\n");  

  inputs = new sc_signal<sc_int<32> >[INSIZE];
  outputs = new sc_signal<sc_int<32> >[OUTSIZE];
  dones = new sc_signal<bool>[OUTSIZE];

  // Open VCD file
  sc_trace_file *wf = sc_create_vcd_trace_file("counter");
  // Dump the desired signals
  sc_trace(wf, clk, "clock");
  sc_trace(wf, reset, "reset");
  

  for(int i = 0; i < INSIZE; i++){
    gen_sys.input_sigs[i](inputs[i]);
  }
  for(int j = 0; j < OUTSIZE; j++){
    gen_sys.output_sigs[j](outputs[j]);
    gen_sys.done[j](dones[j]);
	char name_output[] = "output";
	char name_done[] = "done";
	char one[2];
	sprintf(one,"%d", j);
	sc_trace(wf, outputs[j], strcat(name_output, one));
    sc_trace(wf, dones[j], strcat(name_done, one));
  }
  gen_sys.clk(clk);
  gen_sys.reset(reset);
  gen_sys.valid(valid);

  reset.write(true);
  cout << "Input: ";

  srand(time(NULL));
  for(int i = 0; i < INSIZE; i++){
    temp = rand()%1000;
	inputs[i].write(temp);
    //inputs[i].write(inArray[i]);
  }
    cout << endl;
  sc_start(1, SC_NS);

  reset.write(false);
  valid.write(true);
  sc_start(1, SC_NS);

  valid.write(false);

  while(dones[OUTSIZE-1] != 1 and k < MAX_STEPS)
  {
    sc_start(1, SC_NS);
    reset.write(false);
    k++;
  }
  sc_close_vcd_trace_file(wf);
  cout << "Simulation stopped after " << k << " cycles. Output: ";
  for(int j = 0; j < OUTSIZE; j++)
    cout << "[" << j << "] = " << outputs[j] << " ";
  cout << endl;

  return 0;
}
