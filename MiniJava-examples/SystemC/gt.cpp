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

#include "gt.h"

void gt::CompareNumbers()
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
  if (timer>=GT_DELAY)
  {
	if(a_in >b_in)
		output.write(1);
	else
		output.write(0);
    done.write(true);
    active = false;
	timer = 0;
  }
  else
  {
    done.write(false);
  }
}

