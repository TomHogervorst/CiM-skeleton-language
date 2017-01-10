/*
* reg.cpp
* Implementation of reg class
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

#include "reg.h"

void reg<delay>::Out()
{
  if (reset.read())
  {
    timer = 0;
    active = false;
  }
  else if (valid.read())
  {
    timer = 0;
    data = data_in.read();
    active = true;
  }
  else if (active)
  {
    timer++;
  }

  if (timer==delay)
  {
    data_out.write(data);
    done.write(true);
    timer = 0;
    active = false;
  }
  else
  {
    done.write(false);
  }
}

