// Include Files
#include "main.h"
#include "airspy_decimate.h"
#include "airspy_decimate_terminate.h"
#include "airspy_decimate_types.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "omp.h"
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
  airspy_dedcimate_terminate();

  return 0;
}
