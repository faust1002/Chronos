#!/usr/bin/python3

import logging
import numpy as np
import scipy.fft as fft
import scipy.signal as signal
import matplotlib.pyplot as plt

fcarrier = 77.5e3
fs       = 1e6

def configure_logging(logfile):
    formatter = logging.Formatter("[%(asctime)s] %(levelname)s - %(message)s")
    logger = logging.getLogger()
    logger.setLevel(logging.INFO)

    handler = logging.StreamHandler()
    handler.setLevel(logging.INFO)
    handler.setFormatter(formatter)
    logger.addHandler(handler)

    handler = logging.FileHandler(logfile, mode='w')
    handler.setLevel(logging.DEBUG)
    handler.setFormatter(formatter)
    logger.addHandler(handler)

def plot_signal_in_time_and_freq_domain(time, test_vector, freq, spectrum):
    plt.subplot(1, 2, 1)
    plt.plot(time * 1e3, test_vector)
    plt.title("Signal + noise")
    plt.xlabel("Time [ms]")
    plt.ylabel("Voltage [V]")
    plt.grid()

    plt.subplot(1, 2, 2)

    plt.plot(freq, spectrum)
    plt.title("Fourier transform")
    plt.xlabel("Frequency [kHz]")
    plt.ylabel("Magnitude [dB]")
    plt.grid()

    plt.show()

def encode_bitstream(bitstream):
    logging.info("Encoding bitstream = %s" % str(bitstream))
    vector = np.array([])
    for idx in bitstream:
        bit = bitstream[idx]
        low = int(fs / 10 * (1 + bit))
        v = np.ones(int(fs))
        v[0:low] = 0.15
        vector = np.concatenate([vector, v])

    time = np.arange(0, len(bitstream), 1 / fs)
    vector = np.exp(1j * 2 * np.pi * fcarrier * time) * vector
    return (time, np.imag(vector))

def generate_test_vector():
    time, test_vector = encode_bitstream(np.array([0, 1, 0, 1]))
    f0 = fcarrier / 2
    f1 = fcarrier * 2
    f2 = fcarrier * 3
    test_vector += np.imag(0.5 * np.exp(1j * 2 * np.pi * f0 * time) +
                             2 * np.exp(1j * 2 * np.pi * f1 * time) +
                             3 * np.exp(1j * 2 * np.pi * f2 * time))
    return (time, test_vector)

def calculate_fft(test_vector, nfft):
    spectrum = fft.rfft(test_vector, nfft)
    spectrum = np.abs(spectrum)
    spectrum = spectrum * 2 / nfft
    freq = fft.rfftfreq(nfft, 1 / fs) / 1e3
    return (spectrum, freq)

def add_noise(test_vector, target_snr):
    test_vector_avr_power = 10 * np.log10(np.mean(test_vector ** 2))
    logging.info("Average test_vector power %.2fdBm, target SNR = %.2fdB" % (test_vector_avr_power, target_snr))
    noise_avr_power = test_vector_avr_power - target_snr
    mean_noise = 0
    noise = np.random.normal(mean_noise, np.sqrt(10 ** (noise_avr_power / 10)), len(test_vector))
    test_vector += noise
    return test_vector

def bandpass_filter(test_vector, fdelta):
    fpass = np.array([fcarrier - fdelta, fcarrier + fdelta])
    fstop = np.array([fcarrier - 2 * fdelta, fcarrier + 2 * fdelta])
    N, Wn = signal.buttord(fpass, fstop, 3, 40, fs = fs)
    logging.info("Bandpass: %skHz, stopband: %skHz, filter order = %d" % ((str(fpass / 1e3), str(fstop / 1e3), N)))
    sos = signal.butter(N, Wn, "bandpass", output = "sos", fs = fs)
    return signal.sosfilt(sos, test_vector)

def main():
    print("Hello")

    configure_logging("log.txt")
    plt.style.use("dark_background")

    time, test_vector = generate_test_vector()

    target_snr = 5
    test_vector = add_noise(test_vector, target_snr)

    nfft = 4098
    spectrum, freq = calculate_fft(test_vector, nfft)
    plot_signal_in_time_and_freq_domain(time, test_vector, freq, spectrum)

    fdelta = 5e3
    test_vector = bandpass_filter(test_vector, fdelta)

    spectrum, freq = calculate_fft(test_vector, nfft)
    plot_signal_in_time_and_freq_domain(time, test_vector, freq, spectrum)

    peek = freq[np.argmax(spectrum)]
    logging.info("Found peek = %.2fkHz" % peek)

    print("Goodbye")

if __name__ == "__main__":
    main()
