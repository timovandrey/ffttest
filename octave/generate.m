%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Initialize
init;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Constants

DEBUG_WRITE_CHECKUP_FILE = true;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Create wave

A = [2 1 0.5 0.25];   % Amplitude
f = [20 40 80 160];   % Frequencies
w = 2 * pi * f;       % Angular frequency

y = 0;
for i = 1:length(A)
  y = y + A(i) * sin(w(i) * t);
endfor

y = y;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% FFT the wave

N = length(y);
Y = fft(y);
Y_check = Y;    % To create a checkup file to check whether the scripts are working correctly
Y = 2 * abs(Y)/N;
Y = Y(1:((N/2)+1));
dF = Fs/N;
fx = 0:dF:Fs/2;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Plot
if(DEBUG)
  fig1 = figure();
  ax1 = subplot(1, 2, 1);
  plot(t, y);
  grid minor;
  ax2 = subplot(1, 2, 2);
  stem(fx, Y);
  xlim([0 (max(f) + 100)]);
  grid minor;
endif
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Write to file

outputFile = strcat(SHARED_DIR, SIGNAL_FILE);
fid = fopen(outputFile,'wb'); % opens the file for writing
fwrite(fid, N, 'uint16');
fwrite(fid, y, ACCURACY);
fclose(fid);

if(DEBUG_WRITE_CHECKUP_FILE)
  checkupFile = strcat(SHARED_DIR, CHECK_FILE);
  fid = fopen(checkupFile,'wb');
  fwrite(fid, N, 'uint16');
  fwrite(fid, real(Y_check), ACCURACY);
  fwrite(fid, imag(Y_check), ACCURACY);
  fclose(fid);
endif

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Read file and verify

fid = fopen(outputFile,'rb'); % opens the file for reading
N_read = fread(fid, 1, 'uint16');
if(N_read == N)
  disp("N is the same!");
else
  disp("Error reading the file!");
endif
y_read = fread(fid, N_read, ACCURACY);
if(abs(y_read' - y) < MAX_ERROR)
  disp("y is the same!");
else
  disp("Error reading the file!");
endif

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Other
save("../shared/Y_check.mat", "Y_check");










