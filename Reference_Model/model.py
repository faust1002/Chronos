#!/usr/bin/python3.6

import numpy as np
import scipy
import scipy.signal
import matplotlib
import matplotlib.pyplot as plt

def plot_signal_in_time_and_freq_domain(fs, time, signal):
    plt.subplot(1, 2, 1)
    plt.plot(time * 1e3, signal)
    plt.title("Signal + noise")
    plt.xlabel("Time [ms]")
    plt.ylabel("Voltage [V]")
    plt.grid()

    plt.subplot(1, 2, 2)
    nfft = 4098
    spectrum = scipy.fft.rfft(signal, nfft)
    spectrum = np.abs(spectrum)
    spectrum = spectrum * 2 / nfft
    freq = scipy.fft.rfftfreq(nfft, 1 / fs) / 1e3

    plt.plot(freq, spectrum)
    plt.title("Fourier transform")
    plt.xlabel("Frequency [kHz]")
    plt.ylabel("Magnitude [dB]")
    plt.grid()

    plt.show()

    return (spectrum, freq)

def plot_filter_frequency_response(fs, fdelta, fcarrier):
    fpass = np.array([fcarrier - fdelta, fcarrier + fdelta])
    fstop = np.array([fcarrier - 2 * fdelta, fcarrier + 2 * fdelta])
    print("fcarrier = %.2fkHz, fs = %.2fkHz, fdelta = %.2fkHz, fpass = %skHz, fstop = %skHz" % (fcarrier / 1e3, fs / 1e3, fdelta / 1e3, fpass / 1e3, fstop / 1e3))
    N, Wn = scipy.signal.buttord(fpass, fstop, 3, 40, fs = fs)
    print("Filter order = %d" % N);
    b, a = scipy.signal.butter(N, Wn, "bandpass", fs = fs)
    w, h = scipy.signal.freqz(b, a)
    plt.semilogx(w, 20 * np.log10(np.abs(h)))
    plt.title("Filter frequency response")
    plt.xlabel("Frequency [kHz]")
    plt.ylabel("Amplitude [dB]")
    plt.margins(0, 0.1)
    plt.grid(which = "both", axis = "both")

    plt.show()

    return (N, Wn)

def main():
    print("Hello")

    matplotlib.use("Qt5Agg")
    plt.style.use("dark_background")

    f0 = 60e3
    fcarrier = 77.5e3
    f2 = 77.5e3 * 2
    f3 = 77.5e3 * 3
    fmax = np.max([f0, fcarrier, f2, f3])
    fs = 1e6

    t = np.arange(0, 100 * 1 / fmax, 1 / fs)
    signal = (5 * np.sin(2 * np.pi * f0 * t) +
              10 * np.sin(2 * np.pi * fcarrier * t) +
              20 * np.sin(2 * np.pi * f2 * t) +
              30 * np.sin(2 * np.pi * f3 * t))

    signal_avr_power = 10 * np.log10(np.mean(signal ** 2))
    target_snr = 15
    print("Average signal power %.2fdBm, target SNR = %.2fdB" % (signal_avr_power, target_snr))
    noise_avr_power = signal_avr_power - target_snr
    mean_noise = 0
    noise = np.random.normal(mean_noise, np.sqrt(10 ** (noise_avr_power / 10)), len(t))
    signal += noise

    plot_signal_in_time_and_freq_domain(fs, t, signal)

    fdelta = 5e3
    N, Wn = plot_filter_frequency_response(fs, fdelta, fcarrier)

    sos = scipy.signal.butter(N, Wn, "bandpass", output = "sos", fs = fs)
    signal = scipy.signal.sosfilt(sos, signal)

    spectrum, freq = plot_signal_in_time_and_freq_domain(fs, t, signal)

    peek = freq[np.argmax(spectrum)]
    print("Found peek = %.2f" % peek)

    print("Goodbye")

if __name__ == "__main__":
    main()
