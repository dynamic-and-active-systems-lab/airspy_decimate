//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: _coder_airspy_decimate_info.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 03-Sep-2024 10:57:31
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
  const char_T *data[7]{
      "789ced584d6fd34010b55110bd003920240e15429c83a556aac4b1c4216dd53a565c57a5"
      "11aa37ce24de60afc3daa99272c9892b12bf017140e2e327f5c8cfc0"
      "8ee37c58ac36924330267b198f9f77dfcc8efdc6b6201e9e888220dc13a2f1733bb27727"
      "7e71626f098b23898b137b3be10bd3f385857931fe61624d97f830f0",
      "23872007a6335bae830922fee9b0070205cfb5afa03546dad88653ec8036ef28a1e7bc9c"
      "83a64e0885c7650bcc375adf11a8e5cd22b4e79de97edc30f22d2cb9"
      "1fef18fb514ce08dca6b49f7807a92e359a80d543ac64d8ae8502adb6ebfa5f92e451d90"
      "6a04648aafa0a4b8d4b780927d8aaf5d8274129ca41ef683eb6b72e5",
      "523dde7f55add774459610a65e6f78d902133bc887a4ffcc59c8779432dfc79c7c63bcec"
      "3a3d1b061a261d1b34143a9e2eab753021cc641a8f91329e42c29fc5"
      "1321a685686863be2d311ddf6726df22de28ffe17a0789110236be062928b38d9a25d36d"
      "012df57d6c7b9259eab77a12a708e1adc1abc3fd25f7256967d76f8d",
      "ed0febe9f8a15e17df37f4e0c93af9e2f1b7f8068cf596bdaf1f32f88a097cb083ce0389"
      "de716b67feb9fadc9211191e556771a81c1e5e1c02c35fd7fa378cf9"
      "9b7ef0fb7cb739f9c638438a3420816809fce726abfde013936f11cf723f888a10dd1879"
      "ed071fdf3fdaf40361f5fd803847d5bd0ba5fbc2df3d5169fdb06d36",
      "ab4e253ffdc060cce7ed6372b0f671557cbcefb3e204316d40f37a3b4ac9b7eaef81624a"
      "3dfeca8927c61bb50c0bf2ec055d4cd6cb60e49f17ddca3bdfba7459"
      "bf50cef6aa9adc550edeeaddce5045bbaa99a3f77483313fabba7c87c91721347ae473ab"
      "cbdf39f1c4f8bfa2cbc97a198cfcf3a25b79e7dbe8f26ad63718f3b3",
      "aacbbcff055ef06d3ccf374ac9b7eaff256975f90b279e18cfb42ec73f30c4b85aff8f6e"
      "e59d6fa3cbe9d6ff05f3e66456",
      ""};
  nameCaptureInfo = nullptr;
  emlrtNameCaptureMxArrayR2016a(&data[0], 7680U, &nameCaptureInfo);
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
  emlrtSetField(
      xEntryPoints, 0, "ResolvedFilePath",
      emlrtMxCreateString("/Users/mshafer/Library/CloudStorage/"
                          "OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/"
                          "airspy_decimate/airspy_decimate.m"));
  emlrtSetField(xEntryPoints, 0, "TimeStamp",
                emlrtMxCreateDoubleScalar(739493.36282407411));
  emlrtSetField(xEntryPoints, 0, "Constructor",
                emlrtMxCreateLogicalScalar(false));
  emlrtSetField(xEntryPoints, 0, "Visible", emlrtMxCreateLogicalScalar(true));
  xResult =
      emlrtCreateStructMatrix(1, 1, 9, (const char_T **)&propFieldName[0]);
  emlrtSetField(xResult, 0, "Version",
                emlrtMxCreateString("24.2.0.2622594 (R2024b) Prerelease"));
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
