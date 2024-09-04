//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: airspy_decimate_data.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 04-Sep-2024 12:50:16
//

// Include Files
#include "airspy_decimate_data.h"
#include "airspy_decimate_types.h"

// Custom Source Code
#include "udp.h"

// Variable Definitions
double freq;

boolean_T freq_not_empty;

rtRunTimeErrorInfo emlrtRTEI{
    159,                   // lineNo
    "coderTimeCheckStatus" // fName
};

const char cv[22]{'c', 'o', 'd', 'e', 'r', 'I', 'n', 'i', 't', 'T', 'i',
                  'm', 'e', 'F', 'u', 'n', 'c', 't', 'i', 'o', 'n', 's'};

const char cv1[30]{'c', 'o', 'd', 'e', 'r', 'T', 'i', 'm', 'e', 'C',
                   'l', 'o', 'c', 'k', 'G', 'e', 't', 't', 'i', 'm',
                   'e', 'M', 'o', 'n', 'o', 't', 'o', 'n', 'i', 'c'};

boolean_T isInitialized_airspy_decimate{false};

//
// File trailer for airspy_decimate_data.cpp
//
// [EOF]
//
