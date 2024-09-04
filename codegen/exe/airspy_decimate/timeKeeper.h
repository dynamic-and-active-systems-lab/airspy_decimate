//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: timeKeeper.h
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 04-Sep-2024 12:50:16
//

#ifndef TIMEKEEPER_H
#define TIMEKEEPER_H

// Include Files
#include "rtwtypes.h"
#include "coder_posix_time.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace b_time {
namespace impl {
double timeKeeper(const coderTimespec &savedTime, double &outTime_tv_nsec);

void timeKeeper(double newTime_tv_sec, double newTime_tv_nsec,
                coderTimespec &savedTime);

} // namespace impl
} // namespace b_time
} // namespace internal
} // namespace coder
void timeKeeper_init();

#endif
//
// File trailer for timeKeeper.h
//
// [EOF]
//
