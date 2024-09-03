//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: timeKeeper.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 03-Sep-2024 10:57:31
//

// Include Files
#include "timeKeeper.h"
#include "airspy_decimate_data.h"
#include "airspy_decimate_rtwutil.h"
#include "airspy_decimate_types.h"
#include "coder_posix_time.h"
#include <sstream>
#include <stdexcept>
#include <string>

// Custom Source Code
#include "udp.h"

// Variable Definitions
static boolean_T savedTime_not_empty;

// Function Declarations
static void c_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void c_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::stringstream outStream;
  outStream << "You must call TIC without an output argument before calling "
               "TOC without an input argument.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  throw std::runtime_error(outStream.str());
}

//
// Arguments    : const coderTimespec &savedTime
//                double &outTime_tv_nsec
// Return Type  : double
//
namespace coder {
namespace internal {
namespace b_time {
namespace impl {
double timeKeeper(const coderTimespec &savedTime, double &outTime_tv_nsec)
{
  static rtRunTimeErrorInfo b_emlrtRTEI{
      11,          // lineNo
      "timeKeeper" // fName
  };
  double outTime_tv_sec;
  if (!savedTime_not_empty) {
    c_rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  outTime_tv_sec = savedTime.tv_sec;
  outTime_tv_nsec = savedTime.tv_nsec;
  return outTime_tv_sec;
}

//
// Arguments    : double newTime_tv_sec
//                double newTime_tv_nsec
//                coderTimespec &savedTime
// Return Type  : void
//
void timeKeeper(double newTime_tv_sec, double newTime_tv_nsec,
                coderTimespec &savedTime)
{
  if (!savedTime_not_empty) {
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
    savedTime_not_empty = true;
  }
  savedTime.tv_sec = newTime_tv_sec;
  savedTime.tv_nsec = newTime_tv_nsec;
}

//
// Arguments    : void
// Return Type  : void
//
} // namespace impl
} // namespace b_time
} // namespace internal
} // namespace coder
void timeKeeper_init()
{
  savedTime_not_empty = false;
}

//
// File trailer for timeKeeper.cpp
//
// [EOF]
//
