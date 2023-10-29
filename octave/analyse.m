%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Initialize
init;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Prepare signal

# Read data
signalFile = strcat(SHARED_DIR, SIGNAL_FILE);
fid = fopen(signalFile,'rb');
N_read = fread(fid, 1, 'uint16');
signal = fread(fid, N_read, ACCURACY);
fclose(fid);

# FFT
Y_read = fft(signal);
Y_read = 2*abs(Y_read)/N_read;
Y_read = Y_read(1:(N_read/2 + 1));

dF = Fs/N_read;
frequencies_read = 0:dF:(Fs/2 + 1);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Prepare spectrum

spectrum = [];
spectrumFile = strcat(SHARED_DIR, SPECTRUM_FILE);
spectrumFile = strcat(SHARED_DIR, CHECK_FILE);
fid = fopen(spectrumFile, 'rb');
N_restored = fread(fid, 1, 'uint16');
real = fread(fid, N_restored, ACCURACY);
imaginary = fread(fid, N_restored, ACCURACY);
fclose(fid);

spectrum = real + i * imaginary;

# iFFT
y_restored = ifft(spectrum);

# Normalize spectrum
spectrum = 2 * abs(spectrum)/N_restored;
spectrum = spectrum(1:(N_restored/2 + 1));

dF_restored = Fs/N_restored;
frequencies_restored = 0:dF_restored:(Fs/2 + 1);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Plot
fig1 = figure();
ax1 = subplot(2, 2, 1);
plot(t, signal);
grid minor;
ax2 = subplot(2, 2, 2);
stem(frequencies_read, Y_read);
xlim([0 500]);
grid minor;
ax3 = subplot(2, 2, 3);
plot(t, y_restored);
grid minor;
ax4 = subplot(2, 2, 4);
stem(frequencies_restored, spectrum');
xlim([0 500]);
