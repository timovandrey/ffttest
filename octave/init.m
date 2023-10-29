%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Reset
clc;
clear all;
close all;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Load packages
pkg load control;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Constants

DEBUG = false;

SHARED_DIR = "../shared/";
SIGNAL_FILE = "signal.bin";
SPECTRUM_FILE = "spectrum.bin";
CHECK_FILE = "spectrum_check.bin";

MAX_ERROR = 0.001;
ACCURACY = 'float64';

TRecord = 0.2;      % Seconds
Fs = 48e3;          % Hz
t = 0:1/Fs:TRecord; % Time vector
