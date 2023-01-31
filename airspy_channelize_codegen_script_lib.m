% airspy_decimate_CODEGEN_SCRIPT_LIB   Generate executable airspy_decimate
%  from airspy_decimate.
% 
% Script copied then edited from project 'airspy_channelize_codegen_script_lib' on 30-01-2023.
% 
% See also CODER, CODER.CONFIG, CODER.TYPEOF, CODEGEN.

curr_dir = pwd;
current_folder_name = curr_dir(find(curr_dir=='/',1,'last')+1:end);
if ~strcmp(current_folder_name,'airspy_decimate')
    error('This function must be run in the airspy_decimate root directory. Navigate to <repo location>/airspy_decimate and run again.')
end

%% Create configuration object of class 'coder.CodeConfig'.
cfg = coder.config('lib','ecoder',false);
cfg.CustomInclude = [curr_dir,'/codegen/lib/decimate_8/examples'];
cfg.CustomSource  = [curr_dir,'/codegen/lib/decimate_8/examples/main.c'];
cfg.GenCodeOnly = true;
cfg.GenerateReport = true;
cfg.ReportPotentialDifferences = false;
cfg.RuntimeChecks = true;



%% Define argument types for entry-point 'airspy_decimate'.
% ARGS = cell(1,1);
% ARGS{1} = cell(2,1);
% ARGS{1}{1} = coder.typeof(0);
% ARGS{1}{2} = coder.typeof(0);

%% Invoke MATLAB Coder.
%cd('/home/dasl/airspy_decimate');
tic
codegen -config cfg decimate_8
toc
cd([curr_dir,'/codegen/lib/decimate_8'])
[makestatus,makecmdout] = system('make -f decimate_8_rtw.mk');
if makestatus==0
    disp('Make process complete.')
else
    disp(['Compile failed with output: ',cmplcmdout])
end
disp('Make complete.')
load buildInfo.mat
packNGo(buildInfo,'packType','flat','fileName','portairspy_decimate')
disp('Zip complete.')
cd(curr_dir)
[mkdirstatus, mkdircmdout] = system('mkdir ~/Desktop/portairspy_decimate');
[mvzipstatus, mvzipcmdout] = system('mv portairspy_decimate.zip ~/Desktop/portairspy_decimate/portairspy_decimate.zip');
disp('Zip transfer complete.')
cd('~/Desktop/portairspy_decimate')
[unzipstatus, unzipcmdout] = system('unzip portairspy_decimate');
disp('Unzip complete.')
[cp1status,cp1cmdout] = system('cp /usr/lib/x86_64-linux-gnu/libdl.so ~/Desktop/portairspy_decimate/libdl.so');
systemcopycommand = ['cp ',matlabroot,'/sys/os/glnxa64/libiomp5.so ~/Desktop/portairspy_decimate/libiomp5.so'];
[cp2status,cp2cmdout] = system(systemcopycommand);
[exprtstatus, exprtcmdout] = system('export LD_LIBRARY_PATH=~/Desktop/portairspy_decimate');
disp('Library transfers complete')
[cmplstatus, cmplcmdout] = system('gcc main.c *.a *.so -o decimate_8 -lm');
if cmplstatus==0
    disp('Process complete. Executable generated.')
else
    disp(['Compile failed with output: ',cmplcmdout])
end

