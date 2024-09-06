//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: toc.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 06-Sep-2024 12:39:48
//

// Include Files
#include "toc.h"
#include "airspy_decimate_data.h"
#include "airspy_decimate_rtwutil.h"
#include "airspy_decimate_types.h"
#include "timeKeeper.h"
#include "coder_posix_time.h"
#include <string>

// Function Definitions
//
// Arguments    : const coderTimespec &savedTime
// Return Type  : double
//
namespace coder {
double toc(const coderTimespec &savedTime)
{
  coderTimespec b_timespec;
  double t;
  double tstart_tv_nsec;
  int status;
  t = internal::b_time::impl::timeKeeper(savedTime, tstart_tv_nsec);
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
  return (b_timespec.tv_sec - t) +
         (b_timespec.tv_nsec - tstart_tv_nsec) / 1.0E+9;
}

} // namespace coder

//
// File trailer for toc.cpp
//
// [EOF]
//
