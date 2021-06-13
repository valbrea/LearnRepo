import numpy as np
import math
size = 10
unipolar1 = np.zeros(size)

def bpsk(snr_db, unipolar):
  # 输入SNR_dB，SNR = Eb ./ N0 = 10 .^ (SNR_dB / 10)
  bipolar = 2 * unipolar - 1
  
  n = 1 / math.sqrt(2)*(randn(1,length(bipolar)) + 1i*randn(1,length(bipolar))) # white gaussian noise, 0dB variance 
  h = 1/math.sqrt(2)*(randn(1,length(bipolar)) + 1i*randn(1,length(bipolar))) # Rayleigh channel
  # Channel and noise Noise addition
  y = h.*input + 10^(-snr/20)*n
  # equalization
  yHat = y./h
  # receiver - hard decision decoding
  output = double(real(yHat)>0)