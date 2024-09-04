//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: tic.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 04-Sep-2024 12:38:58
//

// Include Files
#include "tic.h"
#include "airspy_decimate_data.h"
#include "airspy_decimate_rtwutil.h"
#include "airspy_decimate_types.h"
#include "timeKeeper.h"
#include "coder_posix_time.h"
#include <string>

// Function Definitions
//
// Arguments    : coderTimespec &savedTime
// Return Type  : void
//
namespace coder {
void tic(coderTimespec &savedTime)
{
  coderTimespec b_timespec;
  int status;
  if (!freq_not_empty) {
    freq_not_empty = true;
    status = coderInitTimeFunctions(&freq);
    if (status != 0) {
      rtErrorWithMessageID(std::string(&cv[0], 22), status, emlrtRTEI.fName,
                           emlrtRTEI.lineNo);
    }
  }
  status = coderTimeClockGettimeMonotonic(&b_timespec, freq);
  if (status != 0) {
    rtErrorWithMessageID(std::string(&cv1[0], 30), status, emlrtRTEI.fName,
                         emlrtRTEI.lineNo);
  }
  internal::b_time::impl::timeKeeper(b_timespec.tv_sec, b_timespec.tv_nsec,
                                     savedTime);
}

} // namespace coder

//
// File trailer for tic.cpp
//
// [EOF]
//
