//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: _coder_airspy_decimate_mex.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 04-Sep-2024 12:50:16
//

// Include Files
#include "_coder_airspy_decimate_mex.h"
#include "_coder_airspy_decimate_api.h"

// Function Definitions
//
// Arguments    : int32_T nlhs
//                int32_T nrhs
// Return Type  : void
//
void airspy_decimate_mexFunction(int32_T nlhs, int32_T nrhs)
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  st.tls = emlrtRootTLSGlobal;
  // Check for proper number of arguments.
  if (nrhs != 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 0, 4,
                        15, "airspy_decimate");
  }
  if (nlhs > 0) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 15,
                        "airspy_decimate");
  }
  // Call the function.
  airspy_decimate_api();
}

//
// Arguments    : int32_T nlhs
//                mxArray *plhs[]
//                int32_T nrhs
//                const mxArray *prhs[]
// Return Type  : void
//
void mexFunction(int32_T nlhs, mxArray *[], int32_T nrhs, const mxArray *[])
{
  mexAtExit(&airspy_decimate_atexit);
  airspy_decimate_initialize();
  airspy_decimate_mexFunction(nlhs, nrhs);
  airspy_decimate_terminate();
}

//
// Arguments    : void
// Return Type  : emlrtCTX
//
emlrtCTX mexFunctionCreateRootTLS()
{
  emlrtCreateRootTLSR2022a(&emlrtRootTLSGlobal, &emlrtContextGlobal, nullptr, 1,
                           nullptr, "UTF-8", true);
  return emlrtRootTLSGlobal;
}

//
// File trailer for _coder_airspy_decimate_mex.cpp
//
// [EOF]
//
