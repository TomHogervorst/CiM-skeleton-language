/*
* adder_signed.cpp
* Implementation of adder_signed class
*
* Delft University of Technology
* Computer Engineering Laboratory
*
* Change History:
* Date        Author     Description
* ----------  ---------  -----------------
* 2016-06-21  Tom        Initial version
*
*/

#include "mux2.h"

void mux2::SelectNumber()
{
  if(valid1.read())
	check1 = true;
  if(valid2.read())
	check2 = true;
  if(valid3.read())
	check3 = true;
  if (reset.read())
  {
    timer = 0;
    active = false;
  }
  else if (check1 && check2 && check3)
  {
    timer = 0;
    a_in = input1.read();
    b_in = input2.read();
	c_in = input3.read();
    active = true;
	check1 = false;
	check2 = false;
  }
  else if (active)
  {
    timer++;
  }
  if (timer>=MUX2_DELAY)
  {
	if(b_in == 0)
		output.write(a_in);
	else
		output.write(c_in);
    done.write(true);
    active = false;
	timer = 0;
  }
  else
  {
    done.write(false);
  }
}

