//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: _coder_airspy_decimate_info.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 04-Sep-2024 12:50:16
//

// Include Files
#include "_coder_airspy_decimate_info.h"
#include "emlrt.h"
#include "tmwtypes.h"

// Function Declarations
static const mxArray *emlrtMexFcnResolvedFunctionsInfo();

// Function Definitions
//
// Arguments    : void
// Return Type  : const mxArray *
//
static const mxArray *emlrtMexFcnResolvedFunctionsInfo()
{
  const mxArray *nameCaptureInfo;
  const char_T *data[6]{
      "789ced58cd6eda40185c5754ed252da7aa5255f55e895a4ad448bd16529a4821561ca228"
      "f4c7cbfa034cbcb66b9b086ebc41ae7d915eab1efb087d8c3e4231f6"
      "1ab3d26a916c2872d8031fc3b03be3cf66b40b528e4f1584d013148fbf2fe2ba97e06a52"
      "1fa0e5c1f34a521f7218a59f5796e631fe2ea9c47542188731703085",
      "74a6e952cbc14e7831f100f910b8f62d9873a667d9706151d0b3a01521fa2143a520a2a2"
      "f7f501901b7d44913f08160eed2c48fbf15d70bd9515fbf156d08f2a"
      "c7778e3eab0397826ae2c0567df0dc40c5961f7893af26108be21078fc86667c4e73fa7c"
      "25f1c9f8ba4b3d1bc6bae5f46dd071048276433b0702d62df8a91f23",
      "a79f0a87177e62860cb01f55a6f72ba7de17a1de32dfa9cbefd3ecc5c6dd1a714df06ba3"
      "d0b20395d446a6a74a9a17dd5059ff9eae783d7c5d7cfff1bcfefcf1"
      "a717d54de9d1e737af37a9c7c6ffd21b0bd65bf5797c26d0ab72fc781f5fcd2271df3dbb"
      "0cafb4778306762627cd850f4da223f381047853ebdf97fc7d29f1c9",
      "784184e8e0ccc206c99ff76dcddf4f42bd657e1df91b376f7e3b77f95b901e1b65cf5f87"
      "9e340faf5bc3f7e1c1a9e69f1ff748b7498fca93bf8660beac8ffc10"
      "f5b1283dd9f9a39a30c4069ccdc9694ebda2f7cdbf73fa010ef37e18df395beb4656e1fb"
      "6c087c97256fcaaeb7a93c6d5fb72e0f9b7a63d8faf8ad3dec4f347c",
      "a09112ed670dc1fc6dcdd34742bd98f1e39f7c69f3b42ff1c3f875e729df6743e0bb2c79"
      "5376bd5d9e16b3be2198bfad792a3b5707b3b368566f9a53afe8ff15"
      "f2e66957e287f16bc95376d0575897ef4fde945d6f97a7f9d6ff07aa8dab9f",
      ""};
  nameCaptureInfo = nullptr;
  emlrtNameCaptureMxArrayR2016a(&data[0], 7176U, &nameCaptureInfo);
  return nameCaptureInfo;
}

//
// Arguments    : void
// Return Type  : mxArray *
//
mxArray *emlrtMexFcnProperties()
{
  mxArray *xEntryPoints;
  mxArray *xInputs;
  mxArray *xResult;
  const char_T *propFieldName[9]{"Version",
                                 "ResolvedFunctions",
                                 "Checksum",
                                 "EntryPoints",
                                 "CoverageInfo",
                                 "IsPolymorphic",
                                 "PropertyList",
                                 "UUID",
                                 "ClassEntryPointIsHandle"};
  const char_T *epFieldName[8]{
      "QualifiedName",    "NumberOfInputs", "NumberOfOutputs", "ConstantInputs",
      "ResolvedFilePath", "TimeStamp",      "Constructor",     "Visible"};
  xEntryPoints =
      emlrtCreateStructMatrix(1, 1, 8, (const char_T **)&epFieldName[0]);
  xInputs = emlrtCreateLogicalMatrix(1, 0);
  emlrtSetField(xEntryPoints, 0, "QualifiedName",
                emlrtMxCreateString("airspy_decimate"));
  emlrtSetField(xEntryPoints, 0, "NumberOfInputs",
                emlrtMxCreateDoubleScalar(0.0));
  emlrtSetField(xEntryPoints, 0, "NumberOfOutputs",
                emlrtMxCreateDoubleScalar(0.0));
  emlrtSetField(xEntryPoints, 0, "ConstantInputs", xInputs);
  emlrtSetField(xEntryPoints, 0, "ResolvedFilePath",
                emlrtMxCreateString(
                    "/home/dasl/repos/airspy_decimate/airspy_decimate.m"));
  emlrtSetField(xEntryPoints, 0, "TimeStamp",
                emlrtMxCreateDoubleScalar(739499.52195601852));
  emlrtSetField(xEntryPoints, 0, "Constructor",
                emlrtMxCreateLogicalScalar(false));
  emlrtSetField(xEntryPoints, 0, "Visible", emlrtMxCreateLogicalScalar(true));
  xResult =
      emlrtCreateStructMatrix(1, 1, 9, (const char_T **)&propFieldName[0]);
  emlrtSetField(
      xResult, 0, "Version",
      emlrtMxCreateString("24.2.0.2670998 (R2024b) Prerelease Update 3"));
  emlrtSetField(xResult, 0, "ResolvedFunctions",
                (mxArray *)emlrtMexFcnResolvedFunctionsInfo());
  emlrtSetField(xResult, 0, "Checksum",
                emlrtMxCreateString("MI5ABRodIMfrtwr3ME1UcH"));
  emlrtSetField(xResult, 0, "EntryPoints", xEntryPoints);
  return xResult;
}

//
// File trailer for _coder_airspy_decimate_info.cpp
//
// [EOF]
//
