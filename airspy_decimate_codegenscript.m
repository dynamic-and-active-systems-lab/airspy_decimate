% AIRSPY_DECIMATE_CODEGEN_SCRIPT   Generate executable airspy_decimate from
%  airspy_decimate.
% 

% 
% See also CODER, CODER.CONFIG, CODER.TYPEOF, CODEGEN.

%% Create configuration object of class 'coder.EmbeddedCodeConfig'.
cfg = coder.config('exe','ecoder',true);
%cfg = coder.config('exe');
cfg.HardwareImplementation.ProdEqTarget = false;
cfg.TargetLang = 'C++';

cfg.GenCodeOnly = true;
cfg.GenerateExampleMain = 'DoNotGenerate';
% cfg.GenerateMakefile = false;
cfg.GenerateMakefile = true;%Needed so Don has example

cfg.GenerateReport = true;
cfg.MaxIdLength = 1024;
cfg.ReportPotentialDifferences = false;
cfg.TargetLangStandard = 'C++11 (ISO)';
cfg.RuntimeChecks = true;

%% Define argument types for entry-point 'airspy_channelize'.
% ARGS = cell(1,1);
% ARGS{1} = cell(1,1);
% ARGS{1}{1} = coder.typeof(int32(0),[1 Inf],[0 1]);

%% Invoke MATLAB Coder.
% codegen -config cfg airspy_decimate


cfg.CustomInclude = '/Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/airspy_decimate/matlab-coder-utils/c-udp';


% cfg = coder.config('exe');
switch computer('arch')
case 'glnxa64'
    cfg.CodeReplacementLibrary = 'DSP Intel AVX2-FMA (Linux)';
case 'win64' 
    cfg.CodeReplacementLibrary = 'DSP Intel AVX2-FMA (Windows)';
case 'maci64'
    cfg.CodeReplacementLibrary = 'DSP Intel AVX2-FMA (Mac)';
case 'maca64'
    cfg.CodeReplacementLibrary = 'DSP Intel AVX2-FMA (Mac)';
end

% cfg.GenerateExampleMain = 'GenerateCodeAndCompile'; % provides starter main.c

switch computer('arch')
case 'glnxa64'
    codegen airspy_decimate -config cfg
case 'win64'
    codegen airspy_decimate -config cfg 
case 'maci64' %Include path to c headers for UDP
    codegen airspy_decimate matlab-coder-utils/c-udp/udp.cpp matlab-coder-utils/c-udp/udp.h -config cfg -I /Users/mshafer/Library/CloudStorage/OneDrive-NorthernArizonaUniversity/CODE_PLAYGROUND/airspy_decimate/matlab-coder-utils/c-udp
case 'maca64'
    codegen airspy_decimate -config cfg
end