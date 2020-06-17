import logging
import numpy as np

class TestVectorGenerator:

    __fs               = None
    __fcarrier         = None
    __target_snr       = None
    __prsk             = [None, None]
    __bits             = [None, None]

    __signal           = None
    __time             = None

    def __init__(self, fs, fcarrier, target_snr):
        self.__fs               = fs
        self.__fcarrier         = fcarrier
        self.__target_snr       = target_snr
        self.__generate_prsk()
        self.__generate_bits()

    def __generate_prsk(self):
        lsfr = 0
        seq_len = 512
        chip_sequence = np.zeros(seq_len, dtype=int)
        for idx in range(seq_len):
            chip = lsfr & 1
            chip_sequence[idx] = chip
            lsfr >>= 1
            if (chip == 1) or (lsfr == 0):
                lsfr ^= 0x110

        self.__prsk[0] = chip_sequence
        self.__prsk[1] = chip_sequence ^ 1

    def __generate_bits(self):
        self.__bits[0] = np.ones(int(self.__fs), dtype=np.complex128)
        self.__bits[0][0 : int(self.__fs / 10)] = 0.15
        self.__bits[1] = np.ones(int(self.__fs), dtype=np.complex128)
        self.__bits[1][0 : int(self.__fs / 20)] = 0.15

    def __encode_bitstream(self, bitstream):
        logging.info("Encoding bitstream = %s" % str(bitstream))
        self.__time = np.arange(0, len(bitstream), 1 / self.__fs)
        self.__signal = np.exp(1j * 2 * np.pi * self.__fcarrier * self.__time)

        for idx in range(len(bitstream)):
            start = int(idx * self.__fs)
            end = int((idx + 1) * self.__fs)
            self.__signal[start : end] *= self.__bits[bitstream[idx]]

        self.__signal = np.imag(self.__signal)

    def __add_noise(self):
        signal_avr_power = 10 * np.log10(np.mean(self.__signal ** 2))
        logging.info("Average test_vector power %.2fdBm, target SNR = %.2fdB" % (signal_avr_power, self.__target_snr))
        if signal_avr_power > self.__target_snr:
            noise_avr_power = signal_avr_power - self.__target_snr
            mean_noise = 0
            noise = np.random.normal(mean_noise, np.sqrt(10 ** (noise_avr_power / 10)), len(self.__signal))
            self.__signal += noise

    def __add_harmonics(self):
        f0 = self.__fcarrier / 2
        f1 = self.__fcarrier * 2
        f2 = self.__fcarrier * 3
        self.__signal += np.imag(0.5 * np.exp(1j * 2 * np.pi * f0 * self.__time) +
                                   2 * np.exp(1j * 2 * np.pi * f1 * self.__time) +
                                   3 * np.exp(1j * 2 * np.pi * f2 * self.__time))

    def generate(self, bitstream):
        self.__encode_bitstream(bitstream)
        self.__add_harmonics()
        self.__add_noise()
        return (self.__time, self.__signal)

