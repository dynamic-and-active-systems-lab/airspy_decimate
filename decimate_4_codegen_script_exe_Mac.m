% DECIMATE_8_CODEGEN_SCRIPT   Generate executable decimate_8 from decimate_8.
% 
% Script generated from project 'decimate_8.prj' on 18-Jan-2023.
% 
% See also CODER, CODER.CONFIG, CODER.TYPEOF, CODEGEN.

%% Create configuration object of class 'coder.CodeConfig'.
cfg = coder.config('exe','ecoder',false);
cfg.GenerateExampleMain = 'GenerateCodeAndCompile';
cfg.GenerateReport = true;
cfg.ReportPotentialDifferences = false;

%% Invoke MATLAB Coder.
codegen -config cfg decimate_4

