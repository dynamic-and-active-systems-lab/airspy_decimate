//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: FIRDecimator.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 04-Sep-2024 12:38:58
//

// Include Files
#include "FIRDecimator.h"
#include "airspy_decimate_types.h"
#include "coder_bounded_array.h"
#include <algorithm>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <string>

// Type Definitions
struct rtEqualityCheckInfo {
  int lineNo;
  const char *fName;
};

// Function Declarations
static void b_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum);

static void rtErrorWithMessageID(const char *r, const char *aFcnName,
                                 int aLineNum);

static void rtSizeEq1DError(const int aDim1, const int aDim2,
                            const rtEqualityCheckInfo &aInfo);

// Function Definitions
//
// Arguments    : const char *r
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void b_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                   int aLineNum)
{
  std::stringstream outStream;
  ((outStream << "The ") << r)
      << " method cannot be called on an initialized System object or after "
         "calling the release method.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  throw std::runtime_error(outStream.str());
}

//
// Arguments    : const char *r
//                const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void rtErrorWithMessageID(const char *r, const char *aFcnName,
                                 int aLineNum)
{
  std::stringstream outStream;
  ((outStream << "The ") << r)
      << " method cannot be called after calling the release method.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  throw std::runtime_error(outStream.str());
}

//
// Arguments    : const int aDim1
//                const int aDim2
//                const rtEqualityCheckInfo &aInfo
// Return Type  : void
//
static void rtSizeEq1DError(const int aDim1, const int aDim2,
                            const rtEqualityCheckInfo &aInfo)
{
  std::stringstream outStream;
  ((((outStream << "Sizes mismatch: ") << aDim1) << " ~= ") << aDim2) << ".";
  outStream << "\n";
  ((((outStream << "Error in ") << aInfo.fName) << " (line ") << aInfo.lineNo)
      << ")";
  throw std::runtime_error(outStream.str());
}

//
// Arguments    : void
// Return Type  : FIRDecimator *
//
namespace coder {
namespace dspcodegen {
FIRDecimator *FIRDecimator::init()
{
  static const float fv[192]{-1.7094213E-5F,
                             5.48757E-5F,
                             -0.000133232301F,
                             0.000276248669F,
                             -0.000515818945F,
                             0.000894707F,
                             -0.00147507526F,
                             0.00236285757F,
                             -0.00378390402F,
                             0.00638127513F,
                             -0.0131043233F,
                             0.121763438F,
                             0.0170651339F,
                             -0.0074212295F,
                             0.00427812524F,
                             -0.00265435083F,
                             0.0016624165F,
                             -0.00101782253F,
                             0.000595487654F,
                             -0.000325641799F,
                             0.000161825781F,
                             -6.98390795E-5F,
                             2.37981931E-5F,
                             -4.61831132E-6F,
                             -2.63968286E-5F,
                             8.93446122E-5F,
                             -0.00022258806F,
                             0.0004690192F,
                             -0.000885566464F,
                             0.00154818699F,
                             -0.00256571639F,
                             0.00411925232F,
                             -0.00658311136F,
                             0.0109795015F,
                             -0.0216273107F,
                             0.112360463F,
                             0.0369789191F,
                             -0.014864563F,
                             0.00841763616F,
                             -0.00519902492F,
                             0.00325911934F,
                             -0.00200374F,
                             0.0011803559F,
                             -0.000651823124F,
                             0.000328461756F,
                             -0.000144796606F,
                             5.12811603E-5F,
                             -1.11776162E-5F,
                             -2.84942817E-5F,
                             0.000102402293F,
                             -0.000262287154F,
                             0.000562125642F,
                             -0.00107377279F,
                             0.00189273246F,
                             -0.00315406243F,
                             0.00507742632F,
                             -0.00810337439F,
                             0.0133881895F,
                             -0.0254735313F,
                             0.097676F,
                             0.0582331792F,
                             -0.0211435854F,
                             0.0117256604F,
                             -0.00720202364F,
                             0.0045165685F,
                             -0.00278743566F,
                             0.00165273203F,
                             -0.000921277853F,
                             0.000470456114F,
                             -0.000211584527F,
                             7.76219749E-5F,
                             -1.86102643E-5F,
                             -2.51345864E-5F,
                             9.67594242E-5F,
                             -0.000255350693F,
                             0.000557138526F,
                             -0.00107725349F,
                             0.0019152679F,
                             -0.00321033F,
                             0.00518389838F,
                             -0.00826729275F,
                             0.0135504771F,
                             -0.0250427499F,
                             0.0790720135F,
                             0.0790720135F,
                             -0.0250427499F,
                             0.0135504771F,
                             -0.00826729275F,
                             0.00518389838F,
                             -0.00321033F,
                             0.0019152679F,
                             -0.00107725349F,
                             0.000557138526F,
                             -0.000255350693F,
                             9.67594242E-5F,
                             -2.51345864E-5F,
                             -1.86102643E-5F,
                             7.76219749E-5F,
                             -0.000211584527F,
                             0.000470456114F,
                             -0.000921277853F,
                             0.00165273203F,
                             -0.00278743566F,
                             0.0045165685F,
                             -0.00720202364F,
                             0.0117256604F,
                             -0.0211435854F,
                             0.0582331792F,
                             0.097676F,
                             -0.0254735313F,
                             0.0133881895F,
                             -0.00810337439F,
                             0.00507742632F,
                             -0.00315406243F,
                             0.00189273246F,
                             -0.00107377279F,
                             0.000562125642F,
                             -0.000262287154F,
                             0.000102402293F,
                             -2.84942817E-5F,
                             -1.11776162E-5F,
                             5.12811603E-5F,
                             -0.000144796606F,
                             0.000328461756F,
                             -0.000651823124F,
                             0.0011803559F,
                             -0.00200374F,
                             0.00325911934F,
                             -0.00519902492F,
                             0.00841763616F,
                             -0.014864563F,
                             0.0369789191F,
                             0.112360463F,
                             -0.0216273107F,
                             0.0109795015F,
                             -0.00658311136F,
                             0.00411925232F,
                             -0.00256571639F,
                             0.00154818699F,
                             -0.000885566464F,
                             0.0004690192F,
                             -0.00022258806F,
                             8.93446122E-5F,
                             -2.63968286E-5F,
                             -4.61831132E-6F,
                             2.37981931E-5F,
                             -6.98390795E-5F,
                             0.000161825781F,
                             -0.000325641799F,
                             0.000595487654F,
                             -0.00101782253F,
                             0.0016624165F,
                             -0.00265435083F,
                             0.00427812524F,
                             -0.0074212295F,
                             0.0170651339F,
                             0.121763438F,
                             -0.0131043233F,
                             0.00638127513F,
                             -0.00378390402F,
                             0.00236285757F,
                             -0.00147507526F,
                             0.000894707F,
                             -0.000515818945F,
                             0.000276248669F,
                             -0.000133232301F,
                             5.48757E-5F,
                             -1.7094213E-5F,
                             0.0F,
                             0.0F,
                             0.0F,
                             0.0F,
                             0.0F,
                             0.0F,
                             0.0F,
                             0.0F,
                             0.0F,
                             0.0F,
                             0.0F,
                             0.0F,
                             0.125F,
                             0.0F,
                             0.0F,
                             0.0F,
                             0.0F,
                             0.0F,
                             0.0F,
                             0.0F,
                             0.0F,
                             0.0F,
                             0.0F,
                             0.0F};
  FIRDecimator *obj;
  obj = this;
  obj->isInitialized = 0;
  // System object Constructor function: dsp.FIRDecimator
  obj->cSFunObject.P0_IC.re = 0.0F;
  obj->cSFunObject.P0_IC.im = 0.0F;
  for (int i{0}; i < 192; i++) {
    obj->cSFunObject.P1_FILT[i] = fv[i];
  }
  return obj;
}

//
// Arguments    : const creal32_T varargin_1_data[]
//                const int varargin_1_size[2]
//                creal32_T varargout_1_data[]
//                int varargout_1_size[2]
// Return Type  : void
//
void FIRDecimator::step(const creal32_T varargin_1_data[],
                        const int varargin_1_size[2],
                        creal32_T varargout_1_data[], int varargout_1_size[2])
{
  static rtEqualityCheckInfo emlrtECI{
      1,                        // lineNo
      "FIRDecimator/updateImpl" // fName
  };
  static rtRunTimeErrorInfo b_emlrtRTEI{
      1,                // lineNo
      "SystemCore/step" // fName
  };
  int i;
  int inFrameSize;
  int nextPhaseIdx;
  int nextPhaseIdx_tmp;
  int numChans_tmp;
  int outputLen;
  if (isInitialized == 2) {
    rtErrorWithMessageID("step", b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  if (isInitialized != 1) {
    if (isInitialized != 0) {
      b_rtErrorWithMessageID("setup", b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
    }
    isInitialized = 1;
    // System object Initialization function: dsp.FIRDecimator
    cSFunObject.W2_CoeffIdx = 168;
    cSFunObject.W0_PhaseIdx = 7;
    cSFunObject.W4_TapDelayIndex = 168;
    cSFunObject.W1_Sums.re = 0.0F;
    cSFunObject.W1_Sums.im = 0.0F;
    std::memset(&cSFunObject.W3_StatesBuff[0], 0, 192U * sizeof(creal32_T));
    cSFunObject.W5_PrevNumChan = -1;
  }
  // System object Outputs function: dsp.FIRDecimator
  if ((varargin_1_size[1] != 0) || (varargin_1_size[0] != 0)) {
    if (cSFunObject.W5_PrevNumChan == -1) {
      cSFunObject.W5_PrevNumChan = varargin_1_size[1];
    } else if (varargin_1_size[1] != cSFunObject.W5_PrevNumChan) {
      rtSizeEq1DError(varargin_1_size[1], cSFunObject.W5_PrevNumChan, emlrtECI);
    }
  }
  inFrameSize = varargin_1_size[0];
  numChans_tmp = varargin_1_size[1];
  // Calculate output length for the current process
  nextPhaseIdx_tmp = cSFunObject.W0_PhaseIdx;
  nextPhaseIdx = nextPhaseIdx_tmp;
  outputLen = 0;
  for (i = 0; i < inFrameSize;
       i = static_cast<int>(static_cast<unsigned int>(i) + 1U)) {
    nextPhaseIdx++;
    if (nextPhaseIdx >= 8) {
      nextPhaseIdx = 0;
      outputLen++;
    }
  }
  // Update output dimensions
  cSFunObject.O0_Y0.size[0] = outputLen;
  cSFunObject.O0_Y0.size[1] = varargin_1_size[1];
  if (varargin_1_size[0] != 0) {
    int curTapIdx;
    int curTapIdx_tmp;
    int inputIdx;
    int inputSegment;
    int outputSegment;
    int phaseIdx;
    nextPhaseIdx = cSFunObject.W2_CoeffIdx;
    i = nextPhaseIdx;
    phaseIdx = nextPhaseIdx_tmp;
    inputIdx = 0;
    outputSegment = 0;
    inputSegment = 0;
    curTapIdx_tmp = cSFunObject.W4_TapDelayIndex;
    curTapIdx = curTapIdx_tmp;
    for (int kIdx{0}; kIdx < numChans_tmp; kIdx++) {
      int maxWindow;
      int outBufIdx;
      curTapIdx = curTapIdx_tmp;
      phaseIdx = nextPhaseIdx_tmp;
      i = nextPhaseIdx;
      outBufIdx = 0;
      maxWindow = (inputSegment + (nextPhaseIdx_tmp + 1) * 24) - 24;
      for (int iIdx{0}; iIdx < inFrameSize; iIdx++) {
        float acc_im;
        float acc_re;
        int acc_re_tmp;
        int tapIdx;
        tapIdx = inputSegment + curTapIdx;
        cSFunObject.W3_StatesBuff[tapIdx] = varargin_1_data[inputIdx + iIdx];
        acc_re = cSFunObject.W1_Sums.re;
        acc_im = cSFunObject.W1_Sums.im;
        for (int jIdx{tapIdx}; jIdx <= maxWindow + 23; jIdx++) {
          acc_re_tmp = (i + jIdx) - tapIdx;
          acc_re += cSFunObject.W3_StatesBuff[jIdx].re *
                    cSFunObject.P1_FILT[acc_re_tmp];
          acc_im += cSFunObject.W3_StatesBuff[jIdx].im *
                    cSFunObject.P1_FILT[acc_re_tmp];
        }
        if (maxWindow + 23 >= tapIdx) {
          i = ((i + maxWindow) - tapIdx) + 24;
        }
        for (int jIdx{maxWindow}; jIdx < tapIdx; jIdx++) {
          acc_re_tmp = (i + jIdx) - maxWindow;
          acc_re += cSFunObject.W3_StatesBuff[jIdx].re *
                    cSFunObject.P1_FILT[acc_re_tmp];
          acc_im += cSFunObject.W3_StatesBuff[jIdx].im *
                    cSFunObject.P1_FILT[acc_re_tmp];
        }
        if (tapIdx - 1 >= maxWindow) {
          i = (i + tapIdx) - maxWindow;
        }
        cSFunObject.W1_Sums.re = acc_re;
        cSFunObject.W1_Sums.im = acc_im;
        curTapIdx += 24;
        if (curTapIdx >= 192) {
          curTapIdx -= 192;
        }
        phaseIdx++;
        if (phaseIdx < 8) {
          maxWindow += 24;
        } else {
          cSFunObject.O0_Y0.data[outputSegment + outBufIdx] =
              cSFunObject.W1_Sums;
          outBufIdx++;
          cSFunObject.W1_Sums.re = 0.0F;
          cSFunObject.W1_Sums.im = 0.0F;
          phaseIdx = 0;
          i = 0;
          curTapIdx--;
          if (curTapIdx < 0) {
            curTapIdx += 24;
          }
          maxWindow = inputSegment;
        }
      }
      inputIdx += inFrameSize;
      outputSegment += outputLen;
      inputSegment += 192;
    }
    cSFunObject.W4_TapDelayIndex = curTapIdx;
    cSFunObject.W2_CoeffIdx = i;
    cSFunObject.W0_PhaseIdx = phaseIdx;
  }
  varargout_1_size[0] = cSFunObject.O0_Y0.size[0];
  varargout_1_size[1] = cSFunObject.O0_Y0.size[1];
  nextPhaseIdx = cSFunObject.O0_Y0.size[0] * cSFunObject.O0_Y0.size[1];
  if (nextPhaseIdx - 1 >= 0) {
    std::copy(&cSFunObject.O0_Y0.data[0], &cSFunObject.O0_Y0.data[nextPhaseIdx],
              &varargout_1_data[0]);
  }
}

} // namespace dspcodegen
} // namespace coder

//
// File trailer for FIRDecimator.cpp
//
// [EOF]
//
