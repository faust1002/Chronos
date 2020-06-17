import logging
import numpy as np

class TestVectorGenerator:

    __fs               = None
    __fcarrier         = None
    __target_snr       = None
    __offset           = 0
    __chip_length      = 0
    __prsk_length      = 512
    __prsk             = [None, None]
    __bits             = [None, None]
    __phasors          = [None, None]

    __signal           = None
    __time             = None

    def __init__(self, fs, fcarrier, target_snr):
        self.__fs               = fs
        self.__fcarrier         = fcarrier
        self.__target_snr       = target_snr
        self.__offset           = int(fs / 10)
        self.__chip_length      = int(1.55e-3 * fs)
        self.__generate_bits()
        self.__generate_prsk()
        self.__generate_phasors()

    def __generate_bits(self):
        self.__bits[0] = np.ones(int(self.__fs), dtype=np.complex128)
        self.__bits[0][0 : self.__offset] = 0.15
        self.__bits[1] = np.ones(int(self.__fs), dtype=np.complex128)
        self.__bits[1][0 : 2 * self.__offset] = 0.15

    def __generate_prsk(self):
        lsfr = 0
        chip_sequence = np.zeros(self.__prsk_length, dtype=int)
        for idx in range(self.__prsk_length):
            chip = lsfr & 1
            chip_sequence[idx] = chip
            lsfr >>= 1
            if (chip == 1) or (lsfr == 0):
                lsfr ^= 0x110

        self.__prsk[0] = chip_sequence
        self.__prsk[1] = chip_sequence ^ 1

    def __generate_phasors(self):
        phase_shift = 13 * np.pi / 180
        self.__phasors[0] = np.exp(1j * phase_shift)
        self.__phasors[1] = np.exp(-1j * phase_shift)

    def __encode_one_bit(self, bit_idx, bit_value):
        start = int(bit_idx * self.__fs)
        end = int((bit_idx + 1) * self.__fs)
        signal = self.__signal[start : end]
        signal *= self.__bits[bit_value]
        prsk = self.__prsk[bit_value]
        for idx in range(self.__prsk_length):
            start = 2 * self.__offset + idx * self.__chip_length
            end = 2 * self.__offset + (idx + 1) * self.__chip_length
            signal[start : end] *= self.__phasors[prsk[idx]]

    def __encode_bitstream(self, bitstream):
        logging.info("Encoding bitstream = %s" % str(bitstream))
        self.__time = np.arange(0, len(bitstream), 1 / self.__fs)
        self.__signal = np.exp(1j * 2 * np.pi * self.__fcarrier * self.__time)

        for idx in range(len(bitstream)):
            self.__encode_one_bit(idx, bitstream[idx])

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

