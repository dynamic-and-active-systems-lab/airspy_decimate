# airspy_decimat
This code allows decimates incoming SDR data from an Airspy Mini and provides it to other processes via UDP. This software is designed specifically to work with the Airpy Mini operatating at 3 MSPS. It was was developed in Matlab and can be converted to an executable using Matlab Coder. Instructions to do so are contained within this REAME. Some of the Matlab functions developed here has some interesting methods necessitated by the restrictions on system objects in Matlab when using Matlab Coder. 

**NOTE: This software only currently supports incoming sample rates of 3 MSPS and decimates by a factor of 8. It has been simplified to be specifically designed for the UAV-RT project. It is designed to be used in conjunction with airspy_channelize and incoming Airspy Mini IQ data at 3 MSPS ** 

The development of this code was funded via [National Science Foundation grant no. 2104570](https://nsf.gov/awardsearch/showAward?AWD_ID=2104570&HistoricalAwards=false).

## Pre-reqs
- [Airspy Mini](https://airspy.com/airspy-mini/): Details on the install can be seen at this link or at the bottom of this readme. 
- Netcat must be installed on your machine to move data from airspyhf_rx to the channelizer via UDP.
- Running either of the the `decimate_8_codegen_script_***` scripts requires that [Matlab Coder](https://www.mathworks.com/products/matlab-coder.html) be installed with your Matlab install. This requires an installed compiler on your machine. More information on Coder requirements can be found [here](https://www.mathworks.com/help/coder/gs/installing-prerequisite-products.html). For macOS, XCode should be installed (don't forget to [accept the license agreement](https://stackoverflow.com/questions/31384994/how-to-accept-xcode-license) or you might get errors). For Linux systems, you need to have the `build-essentials` package installed. Additionally, the Matlab DSP toolbox must be installed, as the channelizer uses DSP objects. Note that if you generate an executable using Coder or gcc, the resulting executable does not depend on the Matlab install. Matlab is only needed at the time of code generation. 

## Setup
### Setup for running in Matlab
After cloning this repo, the decimate_8.m function can be run directly in Matlab. No additional setup should be needed.
### Setup for building a compiled executable 
The `decimate_8` function can be converted to an executable using Matlab Coder. In this way the channelizer will not require Matlab to run. The scripts to do the code generation are `decimate_8_codegen_script_exe_***.m`. 
#### Executable for macOS
The script `decimate_8_codegen_script_exe_Mac.m`) can be used to generate the executable directly from Matlab. We have tested this on macOS and it generates a executable that can be run in terminal. You will need to add the path to libmwnetworkdevice.dyld to your DYLD_LIBRARY_PATH environmental variable before running the program. This file can be found in MATLABROOT/bin/maci64. To write this as the DYLD_LIBRARY_PATH for all future zshell instances, open or create the .zshrc file in /Users/YOURUSERNAME/.zshrc and add 'export DYLD_LIBRARY_PATH=/Applications/MATLAB_R2023ab.app/bin/maci64:/Applications/MATLAB_R2023ab.app/sys/os/maci64' to the end of this file. 
#### Executable for Linux
When testing `decimated_8_codegen_script_exe_***.m` for executable generation on Linux though (Ubuntu 20.04), Matlab Coder failed. In order to generate an executable for Linux, additional steps are needed and listed below. The steps below will generate an executable and have been placed within the Matlab script `decimate_8_codegen_script_exe_Linux.m` but can also be manually run. The step listed below summarize the steps within this script. 
1. After cloning this repo run Code Generation in Matlab with the following commands while in the repo directory. This may take a long time to run due to the codegen.
```matlab
curr_dir = pwd;
%% Create configuration object of class 'coder.CodeConfig'.
cfg = coder.config('lib','ecoder',false);
cfg.CustomInclude = [curr_dir,'/codegen/lib/decimate_8/examples'];
cfg.CustomSource  = [curr_dir,'/codegen/lib/decimate_8/examples/main.c'];
cfg.GenCodeOnly = true;
cfg.GenerateReport = true;
cfg.ReportPotentialDifferences = false;
cfg.RuntimeChecks = true;
% Invoke MATLAB Coder.
codegen -config cfg decimate_8
```
2. Coder will generate a `codegen` directory within the repo directory. Navigate to the `codegen/lib/decimate_8/` directory in a new terminal window and use the resulting make file (`decimate_8_rtw.mk`) to generate the static library (`*.a`) file. To do this, run `$ make -f decimate_8_rtw.mk` in terminal.
3. We now need to package all of the dependencies to simplify the compiling that is about to come. Go back to Matlab be sure you are in the repo directory. Run the following in Matlab to package all the dependencies into a single .zip file called `portairspy_decimate.zip`.
    - Run `>> load buildInfo.mat`
   - Run `>> packNGo(buildInfo, 'packType','flat','filename','portairspy_decimate')`
4. Move the `portairspy_decimate.zip` file to a new location on your system and unzip. 
5. Unfortunately, we have found that two dependencies aren't included with the packNGo functionality and must now be copied manually into the unzipped directory. 
    - Find the `libdl.so`  library symbolic link on your machine. For a typical install it should be in `/usr/lib/x86_64-linux-gnu`. Copy the symbolic link to the unzipped directory. 
    - Find the `libiomp5.so` library in your Matlab root directory. For a typical install of Matlab R2022b it should be in `/<MATLAB_ROOT>/sys/os/glnxa64`. Copy `libiomp5.so` to the unzipped directory. 
6. Open a terminal in the directory of the unzipped files and run `$ export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:<PATH TO THE UNZIPPED FILES>"`.
7. In this terminal, run `gcc main.c *.a *.so -o decimate_8 -lm`
8. The executable should be generated. To run this on a linux machine `./` needs to precede the `decimate_8` commands listed below in Basic Operation. ie. `./decimate_8`. IMPORTANT: On subsequent calls of the program or in other terminal windows, you'll need to re-run `$ export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:<PATH TO THE UNZIPPED FILES>"` prior to calling airspy_channelizer. 

## Basic Operation
### Starting the program
Start the decimator by issuign the following command in terminal within the directory where the executable exists

`./decimate_8`

### Starting the incoming SDR data
The data coming into the decimator program should be served on local port 40000. For example, the command below will pipe airspy_rx outputs to netcat, which will forward to the decimator on local port 4000.

`airspy_rx -f 148.523 -r - -p 0 -a 3000000 -t 0  -d | netcat -u localhost 40000`


This requires the installation of [airspy_rx](https://github.com/airspy/airspyone_host). Installation instructions for this can be found [below](https://github.com/dynamic-and-active-systems-lab/airspy_channelize#installing-airspy_rx).

### Controlling operation
After running these two commands the program will start up. There are three states of operation: 1) Idle/Pause 2) Running 3) Dead/Killed. The program starts in the 'Run' state. The program accepts commands to transition between states from local port 40001. Transmitting a 1 will start the channelization and output. Transmitting a 0 will pause the operation and put the program into a idle state. Transmitting a -1 will terminate the program. In a separate terminal window, transmit the start, pause, or kill commands with commands: 

Start: `echo -e -n '\x01'| netcat -u -c localhost 40001`

Pause: `echo -e -n '\x00'| netcat -u -c localhost 40001`

Kill:  `echo -e -n '\xFF'| netcat -u -c localhost 40001`


## Installing airspy_rx
[airspy_rx](https://github.com/airspy/airspyone_host/blob/master/airspy-tools/src/airspy_rx.c) is useful for manual control of the [Airspy Mini](https://airspy.com/airspy-mini/) software defined radio. 

#### Linux installation 
https://github.com/airspy/airspyone_host#how-to-build-the-host-software-on-linux

The instrunctions for installing airspyhf on Linux can be found in the airspyhf repo under "[How to build the host software on Linux](https://github.com/airspy/airspyone_host#how-to-build-the-host-software-on-linux)". This will include the dependencies necessary for the installation and use of airspyhf. 

#### macOS installation 

To install this on macOS, you'll need to do a few things first:

1. [Ensure homebrew is installed](https://brew.sh/) and run brew doctor to see if any errors come up 
2. Ensure homebrew is updated by running the following command in a terminal window brew update 
3. Need wget: run the following command in a terminal window brew install wget 
4. Need cmake: run the following command in a terminal window brew install cmake 
5. Need libusb: run the following command in a terminal window brew install libusb

To install airspy, open a terminal directory where you want airspyone_host-master directory downloaded to. You don't need to keep this directory after installing. Now, run the commands below for building and installing. 
```
wget https://github.com/airspy/airspyone_host/archive/master.zip
unzip master.zip
cd airspyone_host-master
mkdir build
cd build
export CMAKE_PREFIX_PATH=/usr/local/Cellar/libusb/1.0.24/include/libusb-1.0
cmake ../ -DINSTALL_UDEV_RULES=ON
make
sudo make install
```
That's it. It should be installed. 

All of the instructions here are the same as those found in the repo under "[How to build the host software on Linux](https://github.com/airspy/airspyone_host#how-to-build-the-host-software-on-linux)" except for the export command. CMake doesn't know how to find libusb, so we run the export command to tell it where it is. It's a temp fix in that if you run CMake for this build process again, you'll have to do the same thing. But you would only need to run CMake once theoretically, since we are building/installing and then leaving it be. 
