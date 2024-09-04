//
// Prerelease License - for engineering feedback and testing purposes
// only. Not for sale.
// File: airspy_decimate.cpp
//
// MATLAB Coder version            : 24.2
// C/C++ source code generated on  : 04-Sep-2024 12:38:58
//

// Include Files
#include "airspy_decimate.h"
#include "ComplexSingleSamplesUDPReceiver.h"
#include "ComplexSingleSamplesUDPSender.h"
#include "FIRDecimator.h"
#include "airspy_decimate_data.h"
#include "airspy_decimate_initialize.h"
#include "airspy_decimate_types.h"
#include "tic.h"
#include "toc.h"
#include "coder_posix_time.h"
#include "time.h"
#include "udp.h"
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include <string>

// Function Declarations
static void b_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void rtErrorWithMessageID(const char *aFcnName, int aLineNum);

// Function Definitions
//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void b_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::stringstream outStream;
  outStream << "Assertion failed.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  throw std::runtime_error(outStream.str());
}

//
// Arguments    : const char *aFcnName
//                int aLineNum
// Return Type  : void
//
static void rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  std::stringstream outStream;
  outStream
      << "Detected a run-time error from a call to the function ASSERT or "
         "ERROR, but unable to report the details in standalone code. To s"
         "ee the error message, generate and execute a MEX function.";
  outStream << "\n";
  ((((outStream << "Error in ") << aFcnName) << " (line ") << aLineNum) << ")";
  throw std::runtime_error(outStream.str());
}

//
// AIRSPYFHCHANNELIZE100 receives complex (IQ) data over a UDP connection from
// an SDR (single precision), channelizes it, and servers it
// up over 100 diferent UDP ports.
//    This function is designed specifically to receive incoming data that
//    has been passed to it via an interanl UDP connection. The program expects
//    128 sample frames of 8-byte complex samples (4 real, 4 imaginary) to be
//    sent over UDP. The program receives that data and fills a buffer until
//    enough samples have been received that 1024 samples will be generated
//    on the output channels at the decimated sample rate.
//
//    Once the buffer fills, the data is channelized and
//    served via UDP to corresponding ports. The function opens a command
//    channel so that integers can be passed to enable basic control
//    authority over the program operation, enabling starting of data
//    processing, pausing, and termination of the program.
//
//    Normal channelization allows for decimation rates and the number of
//    channels to be different. This function holds them equal. Therefore,
//    the decimated rate for each channel is equal to the raw airspy sample
//    rate divided by the number of channels. Additionally, the center
//    frequencies of each channel is therefore
//
//    Data sent over the UDP output channels are single valued complex
//    frames. Each output frame contains 1024 complex values, or 2048
//    individual single precision values. Each frame also contains a
//    timestamp encoded into a complex number in the first element of the
//    frame. The received data frame therefore contains 1025 complex values.
//    The timestamp on each frame is associate with the time of arrival of
//    the first sample in the frame.
//
//    The timestamp is a precision posixtime value in milliseconds. The
//    timestamp is transmitted as a single precision complex value. The
//    imaginary part of this timestamp contains the first 7 digits of the
//    time in milliseconds. The real part contains the upper digits (>=8) of
//    the timestamp. See the help for int2singlecomplex and singlecomplex2int
//    for more information on this transmission standard.
//
//    INPUTS:
//        channelsUsed    Look at UDPChannelSender.m for an explanation of how
//                        this works and how ports are allocated.
//
// Notes:
//        ABOUT CHANNEL CENTER FREQUENCIES:
//        Matlab provides the centerFrequencies function that accepts a
//        channelizer object and a sample rate, and then specifies the
//        center frequencies of the associated channel. This list however is
//        centered at zero and provides negative frequencies. For example a
//        channelizer with Fs = 48000 and a decimation factor of 3 would
//        report center frequencies [-24000 -12000 0 12000]. If the fvtool is
//        used on this channelizer (with the legend turned on) the center
//        frequencies would be [0 12000 -24000 -12000] for filteres 1-4. The
//        shifting here reflects a inconsistency in Matlab's channel
//        reporting. The channelizer outputs follow the latter order, and as
//        such, so to do the UDP port outputs in this function.
//        Because the  number of chanels and the decimation are the same,
//        the frequency of these channels are -Fs/nc*floor(nc/2)<fc<Fs/2,
//        (where nc is the number of channels), if nc is odd. For even nc
//        -Fs/2 < fc < Fs/2-Fs/nc. In both cases the frequency steps are
//        Fs/nc. This was determined by using the centerFrequencies.m
//        function on example channelizer objects. If using the
//        centerFrequencies output the circshift command can be used to get
//        the correct order of channel frequency. For example:
//        circshift(centerFrequencies(channizerObject,48000),ceil(numChannels/2))
//
//        ABOUT INCOMING DATA:
//        An Airspy connected to the machine via USB is received using
//        the airspyhf_rx or airspy_rx executable. Using the program with the
//        '-r stdout' option allows the data to be piped to another program
//        with the | character. Netcat can then be use to provide the data to
//        this function via UDP. An example commandline input would be
//
//        /usr/local/bin/airspyhf_rx -f 91.7 -m on -a 912000 -n 9120000 -r
//        stdout -g on -l high -t 0 | netcat -u localhost 10000
//
//        Note that this system call must executed after this function is
//        already running or a 'Connection refused' error will occur in
//        terminal.
// -------------------------------------------------------------------------
// Author:    Michael Shafer
// Date:      2022-01-18
// -------------------------------------------------------------------------
//
// Arguments    : void
// Return Type  : void
//
void airspy_decimate()
{
  static rtRunTimeErrorInfo b_emlrtRTEI{
      24,     // lineNo
      "error" // fName
  };
  static rtRunTimeErrorInfo c_emlrtRTEI{
      31,                                  // lineNo
      "ComplexSingleSamplesUDPSender/send" // fName
  };
  ComplexSingleSamplesUDPReceiver udpReceiver;
  ComplexSingleSamplesUDPSender udpSender;
  coder::dspcodegen::FIRDecimator decimator;
  coderTimespec savedTime;
  creal32_T complexBuffer_data[128];
  creal32_T complexData_data[16];
  creal32_T decimatedData_data[16];
  double decimatedSampsTransmitted;
  double rawSampsReceived;
  int data_size[2];
  int counter;
  if (!isInitialized_airspy_decimate) {
    airspy_decimate_initialize();
  }
  // udpRawReceivePort           = 40000;
  // decimator                   = dsp.CICDecimator(decimationFactor);
  decimator.init();
  //  The value for sampleFrameSize (2039) must exactly what csdr is sending per
  //  frame Must be a multiple of 128
  udpReceiver.udpReceiver = udpReceiverSetup(40000.0);
  if (udpReceiver.udpReceiver <= 0) {
    rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  udpSender.udpSender = udpSenderSetup(10000.0);
  if (udpSender.udpSender <= 0) {
    rtErrorWithMessageID(b_emlrtRTEI.fName, b_emlrtRTEI.lineNo);
  }
  //  udpSender                   = ComplexSingleSamplesUDPSender('127.0.0.1',
  //  outputIPPort, airspySampleFrameSize); Start by clearing any stale data
  udpReceiverClear(udpReceiver.udpReceiver);
  std::printf("Waiting for new udp data\n");
  std::fflush(stdout);
  counter = 1;
  rawSampsReceived = 0.0;
  decimatedSampsTransmitted = 0.0;
  coder::tic(savedTime);
  // Initialize with zeros and empty so coder knows
  data_size[0] = 128;
  data_size[1] = 1;
  while (1) {
    int decimatedData_size[2];
    int loop_ub_tmp;
    std::memset(&complexBuffer_data[0], 0, 128U * sizeof(creal32_T));
    udpReceiverReadComplex(udpReceiver.udpReceiver, &complexBuffer_data[0],
                           128.0);
    //  disp(n);
    rawSampsReceived += 128.0;
    decimator.step(complexBuffer_data, data_size, decimatedData_data,
                   decimatedData_size);
    loop_ub_tmp = decimatedData_size[0] * decimatedData_size[1];
    if (loop_ub_tmp - 1 >= 0) {
      std::copy(&decimatedData_data[0], &decimatedData_data[loop_ub_tmp],
                &complexData_data[0]);
    }
    if (loop_ub_tmp != 16) {
      b_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
    }
    udpSenderSendComplex(udpSender.udpSender, &complexData_data[0], 16.0);
    decimatedSampsTransmitted += 16.0;
    counter++;
    if (counter >= 12000) {
      double timeDur;
      timeDur = coder::toc(savedTime);
      counter = 1;
      std::printf("INPUT SAMPLE RATE: %f    OUTPUT SAMPLE RATE: %f \n",
                  rawSampsReceived / timeDur,
                  decimatedSampsTransmitted / timeDur);
      std::fflush(stdout);
      rawSampsReceived = 0.0;
      decimatedSampsTransmitted = 0.0;
      coder::tic(savedTime);
    }
  }
}

//
// File trailer for airspy_decimate.cpp
//
// [EOF]
//
