//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: FIRDecimator.h
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 06-Sep-2024 12:39:48
//

#ifndef FIRDECIMATOR_H
#define FIRDECIMATOR_H

// Include Files
#include "rtwtypes.h"
#include "coder_bounded_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
struct dsp_FIRDecimator_0 {
  int S0_isInitialized;
  int W0_PhaseIdx;
  creal32_T W1_Sums;
  int W2_CoeffIdx;
  creal32_T W3_StatesBuff[192];
  int W4_TapDelayIndex;
  int W5_PrevNumChan;
  creal32_T P0_IC;
  float P1_FILT[192];
  coder::bounded_array<creal32_T, 16U, 2U> O0_Y0;
};

namespace coder {
namespace dspcodegen {
class FIRDecimator {
public:
  FIRDecimator *init();
  void step(const creal32_T varargin_1_data[], const int varargin_1_size[2],
            creal32_T varargout_1_data[], int varargout_1_size[2]);

private:
  int isInitialized;
  dsp_FIRDecimator_0 cSFunObject;
};

} // namespace dspcodegen
} // namespace coder

#endif
//
// File trailer for FIRDecimator.h
//
// [EOF]
//
