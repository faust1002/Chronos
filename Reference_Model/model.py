#!/usr/bin/python3.6

import numpy as np
import scipy.fft as fft
import matplotlib.pyplot as plt

def main():
    print("Hello")

    f0 = 77.5e3
    f1 = 77.5e3 * 2
    f2 = 77.5e3 * 3
    fmax = np.max([f0, f1, f2])
    fs = 50 * fmax

    t = np.arange(0, 10 * 1 / fmax, 1 / fs)
    signal = 10 * np.sin(2 * np.pi * f0 * t) + 20 * np.sin(2 * np.pi * f1 * t) +  30 * np.sin(2 * np.pi * f2 * t)

    signal_avr_power = 10 * np.log10(np.mean(signal ** 2))
    target_snr = 15
    print("Average signal power %.2fdBm, target SNR = %.2fdB" % (signal_avr_power, target_snr))
    noise_avr_power = signal_avr_power - target_snr
    mean_noise = 0
    noise = np.random.normal(mean_noise, np.sqrt(10 ** (noise_avr_power / 10)), len(t))
    signal += noise

    plt.subplot(1, 2, 1)
    plt.plot(t * 1e3, signal)
    plt.title("Signal + noise")
    plt.xlabel("Time [ms]")
    plt.ylabel("Voltage [V]")
    plt.grid()

    plt.subplot(1, 2, 2)
    nfft = 4098
    spectrum = fft.rfft(signal, nfft)
    spectrum = np.abs(spectrum)
    spectrum = spectrum * 2 / nfft
    freq = fft.rfftfreq(nfft, 1 / fs) / 1e3

    plt.plot(freq, spectrum)
    plt.title("Fourier transform")
    plt.xlabel("Frequency [kHz]")
    plt.ylabel("Magnitude [dB]")
    plt.grid()

    plt.show()

    print("Goodbye")

if __name__ == "__main__":
    main()
