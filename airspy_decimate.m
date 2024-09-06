function airspy_decimate() 
%#codegen
%AIRSPYFHCHANNELIZE100 receives complex (IQ) data over a UDP connection from 
%an SDR (single precision), channelizes it, and servers it 
%up over 100 diferent UDP ports.
%   This function is designed specifically to receive incoming data that
%   has been passed to it via an interanl UDP connection. The program expects
%   128 sample frames of 8-byte complex samples (4 real, 4 imaginary) to be
%   sent over UDP. The program receives that data and fills a buffer until
%   enough samples have been received that 1024 samples will be generated
%   on the output channels at the decimated sample rate. 
%
%   Once the buffer fills, the data is channelized and
%   served via UDP to corresponding ports. The function opens a command
%   channel so that integers can be passed to enable basic control
%   authority over the program operation, enabling starting of data
%   processing, pausing, and termination of the program.
%
%   Normal channelization allows for decimation rates and the number of
%   channels to be different. This function holds them equal. Therefore,
%   the decimated rate for each channel is equal to the raw airspy sample
%   rate divided by the number of channels. Additionally, the center
%   frequencies of each channel is therefore
%
%   Data sent over the UDP output channels are single valued complex
%   frames. Each output frame contains 1024 complex values, or 2048
%   individual single precision values. Each frame also contains a
%   timestamp encoded into a complex number in the first element of the
%   frame. The received data frame therefore contains 1025 complex values.
%   The timestamp on each frame is associate with the time of arrival of
%   the first sample in the frame. 
%
%   The timestamp is a precision posixtime value in milliseconds. The 
%   timestamp is transmitted as a single precision complex value. The
%   imaginary part of this timestamp contains the first 7 digits of the
%   time in milliseconds. The real part contains the upper digits (>=8) of
%   the timestamp. See the help for int2singlecomplex and singlecomplex2int
%   for more information on this transmission standard. 
%
%   INPUTS:
%       channelsUsed    Look at UDPChannelSender.m for an explanation of how 
%                       this works and how ports are allocated.
%
%Notes:   
%       ABOUT CHANNEL CENTER FREQUENCIES:
%       Matlab provides the centerFrequencies function that accepts a
%       channelizer object and a sample rate, and then specifies the
%       center frequencies of the associated channel. This list however is
%       centered at zero and provides negative frequencies. For example a
%       channelizer with Fs = 48000 and a decimation factor of 3 would
%       report center frequencies [-24000 -12000 0 12000]. If the fvtool is
%       used on this channelizer (with the legend turned on) the center
%       frequencies would be [0 12000 -24000 -12000] for filteres 1-4. The
%       shifting here reflects a inconsistency in Matlab's channel
%       reporting. The channelizer outputs follow the latter order, and as
%       such, so to do the UDP port outputs in this function. 
%       Because the  number of chanels and the decimation are the same, 
%       the frequency of these channels are -Fs/nc*floor(nc/2)<fc<Fs/2, 
%       (where nc is the number of channels), if nc is odd. For even nc
%       -Fs/2 < fc < Fs/2-Fs/nc. In both cases the frequency steps are 
%       Fs/nc. This was determined by using the centerFrequencies.m 
%       function on example channelizer objects. If using the
%       centerFrequencies output the circshift command can be used to get
%       the correct order of channel frequency. For example:
%       circshift(centerFrequencies(channizerObject,48000),ceil(numChannels/2))
%
%       ABOUT INCOMING DATA:
%       An Airspy connected to the machine via USB is received using
%       the airspyhf_rx or airspy_rx executable. Using the program with the
%       '-r stdout' option allows the data to be piped to another program 
%       with the | character. Netcat can then be use to provide the data to
%       this function via UDP. An example commandline input would be
%
%       /usr/local/bin/airspyhf_rx -f 91.7 -m on -a 912000 -n 9120000 -r
%       stdout -g on -l high -t 0 | netcat -u localhost 10000
%
%       Note that this system call must executed after this function is
%       already running or a 'Connection refused' error will occur in
%       terminal.
%-------------------------------------------------------------------------
%Author:    Michael Shafer
%Date:      2022-01-18
%-------------------------------------------------------------------------

coder.cinclude('time.h');

if nargin == 0
    channelsUsed = [ ];
end

%udpRawReceivePort           = 40000;
decimationFactor            = 8;
%decimator                   = dsp.CICDecimator(decimationFactor);
decimator                   = dsp.FIRDecimator(decimationFactor);

incomingSampleRate          = 3e6;
outgoingSampleRate          = incomingSampleRate / decimationFactor;

totalSampsReceived          = uint64(0);
sampsTransmitted            = uint32(0);

outputIPPort                = 10000;

startTimeStamp              = 0;
bufferTimeStamp4Sending     = complex(single(0));

tocElapsedSubtract          = 0;
tocBasedElapseTime          = 0;
sampBasedElapsedTime        = 0;


% The value for sampleFrameSize (2039) must exactly what csdr is sending per frame
airspySampleFrameSize       = 128;
sampleCountPerOutput        = airspySampleFrameSize/decimationFactor;             % Must be a multiple of 128
udpReceiver                 = ComplexSingleSamplesUDPReceiver('127.0.0.1', 40000, airspySampleFrameSize);
udpSender                   = ComplexSingleSamplesUDPSender('127.0.0.1', outputIPPort, sampleCountPerOutput);
% udpSender                   = ComplexSingleSamplesUDPSender('127.0.0.1', outputIPPort, airspySampleFrameSize);

% Start by clearing any stale data
udpReceiver.clear();

fprintf("Waiting for new udp data\n");

counter = 1;
rawSampsReceived = 0;
decimatedSampsTransmitted = 0;
tic;
data = single(complex((zeros(airspySampleFrameSize,1))));%Initialize with zeros and empty so coder knows
while true
    data = single([]);
    while (isempty(data))
        data = udpReceiver.receive();
        n = numel(data);
        %Dubugging code
        fprintf('samps received = %f \n',n);
        %
        rawSampsReceived = rawSampsReceived + n;
    end
    decimatedData = decimator(data);
    udpSender.send(decimatedData);
    decimatedSampsTransmitted = decimatedSampsTransmitted + numel(decimatedData);
    counter = counter + 1;
    if counter >= 12000
        timeDur = toc;
        counter = 1;
        fprintf('INPUT SAMPLE RATE: %f    OUTPUT SAMPLE RATE: %f \n',rawSampsReceived/timeDur, decimatedSampsTransmitted/timeDur);
        rawSampsReceived = 0;
        decimatedSampsTransmitted = 0;
        tic
    end
end
