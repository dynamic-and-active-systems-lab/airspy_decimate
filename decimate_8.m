function []= decimate_8() %#codegen
%DECIMATE_8 receives complex (IQ) data over a UDP connection from 
%an Airspy Mini SDR at 3MSPS and decimates by 8, sending the 375 KSPS
%data out over UDP.
%   This function is designed specifically to receive incoming data that
%   has been passed to it via an interanl UDP connection. The parameters of
%   the incoming data are specific to the Airspy Mini. The program expects
%   128 sample frames of 8-byte complex samples (4 real, 4 imaginary) to be
%   sent over UDP. The program receives that data and fills a buffer until
%   enough samples have been received that 1024 samples will be generated
%   on the output channels at the decimated sample rate. 
%
%   Once the buffer fills, the data is decimated and
%   served via UDP to a UDP port. The function opens a command
%   channel so that integers can be passed to enable basic control
%   authority over the program operation, enabling starting of data
%   processing, pausing, and termination of the program. This function
%   start in 'run' mode. 
%
%   Note that all UDP ports have been hardcoded for this function because
%   they are used within the dsp.udpsender and dsp.udpreceiver system
%   objects. When deploying this code to C via Matlab coder, these system
%   object arguments must be constants, which limits the ability of this
%   function to receive ports as arguments and set them at run time. They
%   must be a constant at compile time.
%%
%   Data sent over the UDP output channels are single valued complex
%   frames. Each output frame contains 1024 complex values, or 2048
%   individual single precision values. 
%
%
%   PORT LISTING
%       40000       Receive port for airspy data
%                      Complex single precision data
%                      Maximum message size 1024 bytes
%       40001       Receive port for fucntion control commands
%                      Real int8 data
%                      Maximum message size 1024 bytes
%                      Valid inputs are
%                           1   Start data reception/transmission
%                           0   Stop (pause) data reception/transmission
%                               and flush the buffer
%                           -1  Terminate the function
%       10000       Send ports for serving channelized UDP data. The
%                   center frequency of the channel for port 20000 is the
%                   center frequency of the incoming data. Subsequent port
%                   correspond to the increasing channel numbers and
%                   frequency, eventually wrapping to negative frequencies
%                   above Fs/2. See notes about channel center frequencies
%                   below.The max port number is equal to 
%                   20000+numberofchannels-1
%
%
%   INPUTS:
%       none
%
%   OUTPUTS:
%       none
%%
%
%
%Notes:   
%       ABOUT INCOMING DATA:
%       An Airspy Mini connected to the machine via USB is received using
%       the airspy_rx executable. Using the program with the '-r stdout'
%       option allows the data to be piped to another program with the |
%       character. Netcat can then be use to provide the data to this
%       function via UDP. An example commandline input would be
%
%       /usr/local/bin/airspy_rx -f 148.523 -r - -p 0 -a 3000000 -t 0
%           -n 6000000 -d | netcat -u localhost 40000
%
%
%       Note that this system call must executed after this function is
%       already running or a 'Connection refused' error will occur in
%       terminal.
%       Command signals send via UDP can be entered in the command line as
%       follows:
%           Start (send a 1): 
%               echo -e -n '\x01'| netcat -u localhost 40001
%           Pause (send a 0): 
%               echo -e -n '\x00'| netcat -u localhost 40001
%           Kill (send a -1): 
%               echo -e -n '\xFF'| netcat -u localhost 40001
%
%-------------------------------------------------------------------------
%Author:    Michael Shafer
%Date:      2023-01-17
%-------------------------------------------------------------------------

%RADIO SAMPLE RATE:     3e6
%OUTPUT SAMPLE RATE:   3750e3

fprintf('Decimate: Starting up...\n')
coder.varsize('state')

%General Seeting Settings
rawSampleRate       = 3e6; %Airspy mini sample rate
decimationFactor    = 8;
outputSampleRate    = rawSampleRate/decimationFactor;
pauseWhenIdleTime   = 0.25;

%UDP Settings
udpReceivePort      = 40000;
udpCommandPort      = 40001;
udpServePort        = 10000;

%Incoming Data Variables
rawFrameLength      = 128;

rawFrameTime        = rawFrameLength/rawSampleRate;
bytesPerSample      = 8;


fprintf('Decimate: Setting up UDP command and data ports...\n')
%% SETUP UDP COMMAND INPUT OBJECT
udpCommand = dsp.UDPReceiver('RemoteIPAddress','127.0.0.1',...%127.0.0.1',...  %Accept all
    'LocalIPPort',udpCommandPort,...
    'ReceiveBufferSize',2^6,...%2^16 = 65536, 2^18
    'MaximumMessageLength',1024,...
    'MessageDataType','int8',...
    'IsMessageComplex',false);

setup(udpCommand);

%% SETUP UDP DATA INPUT OBJECT
udpReceive = dsp.UDPReceiver('RemoteIPAddress','127.0.0.1',...%127.0.0.1',... %Accept all
    'LocalIPPort',udpReceivePort,...
    'ReceiveBufferSize',2^18,...%2^16 = 65536, 2^18
    'MaximumMessageLength',4096,...%1024,...%128 on a Mac and 2048 on Linux
    'MessageDataType','single',...
    'IsMessageComplex',true);

setup(udpReceive);

%% SETUP UDP OUTPUT OBJECTS
fprintf('Decimatr: Setting up output channel UDP ports...\n')
samplesPerChannelMessage = 1024; % Must be a multiple of 128
samplesAtFlush           = samplesPerChannelMessage * decimationFactor;
bytesPerChannelMessage   = bytesPerSample * samplesPerChannelMessage;%
sendBufferSize           = 2^nextpow2( bytesPerChannelMessage );
dataBufferFIFO           = dsp.AsyncBuffer( 2 * samplesAtFlush );
write( dataBufferFIFO , single(1 + 1i) );%Write a single value so the number of channels is specified for coder. Specify complex single for airspy data
read(dataBufferFIFO);     %Read out that single sample to empty the buffer.

udpSend                  = dsp.UDPSender('RemoteIPAddress', '127.0.0.1',...
                            'RemoteIPPort', udpServePort  , ...
                            'SendBufferSize', sendBufferSize);

%% SETUP DECIMATOR OBJECTS
%decimator                = dsp.FIRDecimator(decimationFactor, 'ProductDataType', 'Same as input');
decimator                = dsp.CICDecimator(decimationFactor);
%Scale for cicdecimator gain
diffDelay                = decimator.DifferentialDelay;
NumSect                  = decimator.NumSections;
gainCIC                  = (decimationFactor * diffDelay)^NumSect;


%Make initial call to udps. First call is very slow and can cause missed
%samples if left within the while loop
singleZeros = complex(single(zeros(samplesPerChannelMessage,1)));
nullPacket  = singleZeros;
udpSend(nullPacket);%Add one for blank time stamp

state = 'run';
fprintf('Decimate: Setup complete. Running...\n')
tic;

%Initialize for coder
data = single(complex(zeros(samplesAtFlush, 1)));

%Setup loop time variables for tracking actual processing time
flushes        = 0;
loopTime       = 0;
loopTimeRecordHorizon = 100;
loopTimeRecord = nan(loopTimeRecordHorizon,1);

while 1 
    switch state
        case 'run'
            state = 'run';
            dataReceived = udpReceive();

            if (~isempty(dataReceived)) 
                %If input data isn't streaming initially, the decimator may
                %read a real value and then when it starts coming in
                %complex, decimator crashes because the type changed
                %without releasing first
                if isreal(dataReceived)
                    release(decimator)
                end
                
                write(dataBufferFIFO, dataReceived(:));%Call with (:) to help coder realize it is a single channel

                if dataBufferFIFO.NumUnreadSamples >= samplesAtFlush
                    loopTime = toc;
                    loopTimeRecord( 1 + mod( flushes, loopTimeRecordHorizon), 1 ) = loopTime;
                    flushes = flushes + 1;
                    fprintf('Flushing Decimate Buffer: Running - Buffer filled with %u samples. Flushing to output.\n',uint32(samplesAtFlush))
                    fprintf('Moving average of time between buffer flushes: %6.6f.  Expected: %6.6f. \n', mean(loopTimeRecord,"all","omitnan") , samplesPerChannelMessage/outputSampleRate)
                    tic;
                    %Call out indicies so coder knows it is a fixed size. 
                    data( 1:samplesAtFlush ) = read( dataBufferFIFO, samplesAtFlush );
                    dataDecimated            = decimator(data) / gainCIC;
                    udpSend(dataDecimated(:))
                    time2Decimate = toc;
                    fprintf('Time required to decimate: %6.6f \n', time2Decimate)
                end
                
            else

                pause(rawFrameTime/2);

            end
            
            cmdReceived  = udpCommand();
            state = checkcommand(cmdReceived,state);
            
        case 'idle'
            state = 'idle';
            reset(dataBufferFIFO);
            fprintf('Decimate: Idle. Waiting for command...\n')
            pause(pauseWhenIdleTime);%Wait a bit so to throttle idle execution
            cmdReceived  = udpCommand();
            state = checkcommand(cmdReceived,state);
            if strcmp(state,'run')
                reset(udpReceive);%Reset to clear buffer so data is fresh - in case state had been idle
            end

        case 'kill'
            fprintf('Decimate: Entering Kill state. Shutting down.\n')
            state = 'dead';
            release(dataBufferFIFO);
            release(udpReceive)
            release(udpCommand)
            break

        otherwise
            %Should never get to this case, but jump to idle if we get
            %here.
            state = 'idle';

    end

end


function state = checkcommand(cmdReceived,currentState)
%This function is designed to check the incoming command and decide what to
%do based on the received command and the current state
if ~isempty(cmdReceived)
    if cmdReceived == -1
        fprintf('Decimate: Kill command received.\n')
        state = 'kill';
    elseif cmdReceived == 0
        fprintf('Decimate: Idle command received.\n')
        state = 'idle';
    elseif cmdReceived == 1
        fprintf('Decimate: Run command received.\n')
        state = 'run';
    else
        %Invalid command. Continue with current state.
        state = currentState;
    end
else
    %Nothing received. Continue with current state.
    state = currentState;
end
end

end
