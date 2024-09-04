//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: airspy_decimate_initialize.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 04-Sep-2024 12:38:58
//

// Include Files
#include "airspy_decimate_initialize.h"
#include "CoderTimeAPI.h"
#include "airspy_decimate_data.h"
#include "timeKeeper.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void airspy_decimate_initialize()
{
  CoderTimeAPI::callCoderClockGettime_init();
  timeKeeper_init();
  isInitialized_airspy_decimate = true;
}

//
// File trailer for airspy_decimate_initialize.cpp
//
// [EOF]
//
