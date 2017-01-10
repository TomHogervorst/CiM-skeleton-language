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
* 2016-02-17  Jintao     Initial version
* 2016-06-21  Tom		 Version suitable for generated systemC
*
*/

#include "adder_signed.h"

void adder_signed::AddNumbers()
{
  if(valid1.read())
	check1 = true;
  if(valid2.read())
	check2 = true;
  if (reset.read())
  {
    timer = 0;
    active = false;
  }
  else if (check1 && check2)
  {
    timer = 0;
    a_in = input1.read();
    b_in = input2.read();
    active = true;
	check1 = false;
	check2 = false;
  }
  else if (active)
  {
    timer++;
  }
  if (timer>=ADD_DELAY)
  {
    output.write(a_in + b_in);
    done.write(true);
    active = false;
	timer = 0;
  }
  else
  {
    done.write(false);
  }
}

