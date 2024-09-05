// Include Files
#include "main.h"
#include "airspy_decimate.h"
#include "airspy_decimate_terminate.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>
#include <stdlib.h>

int main(int argc, char ** argv)
{
  airspy_decimate();


  // Terminate the application.
  // You do not need to do this more than one time.
  airspy_decimate_terminate();

  return 0;
}
