/*
* divider_signed.cpp
* Implementation of divider_signed class
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

#include "divider_signed.h"
#include <stdio.h>

void divider_signed::DivNumbers()
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
	check1 = false;
	check2 = false;
    a_in = input1.read();
    b_in = input2.read();
    active = true;
  }
  else if (active)
  {
    timer++;
  }

  if (timer==DIV_DELAY)
  {
	cout << "div_ins: " << a_in << ", " << b_in << ".\n";
    output.write(a_in / b_in);
    done.write(true);
    timer = 0;
    active = false;
  }
  else
  {
    done.write(false);
  }
}

