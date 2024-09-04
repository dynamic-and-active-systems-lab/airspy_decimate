//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: airspy_decimate_rtwutil.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 04-Sep-2024 12:50:16
//

// Include Files
#include "airspy_decimate_rtwutil.h"
#include <sstream>
#include <stdexcept>
#include <string>

// Custom Source Code
#include "udp.h"

// Function Definitions
//
// Arguments    : const std::string r
//                const int i
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
void rtErrorWithMessageID(const std::string r, const int i,
                          const char *aFcnName, int aLineNum)
{
  std::stringstream outStream;
  ((((outStream << "Call to \'") << r) << "\' failed with return value ") << i)
      << ".";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  throw std::runtime_error(outStream.str());
}

//
// File trailer for airspy_decimate_rtwutil.cpp
//
// [EOF]
//
