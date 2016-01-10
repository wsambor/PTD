#ifndef PSK_DEMODULATION_HPP
#define PSK_DEMODULATION_HPP

#include <vector>

#include "sinusDrawing.hpp"
#include "PSKModulation.hpp"

class PSKDemodulation : public PSKModulation {
 public:
  using PSKModulation::PSKModulation;

  PSKDemodulation();
  PSKDemodulation(float Time, float SamplingFrequency,
                  const std::vector<int>& BitesVector);
  ~PSKDemodulation();

  void generateDemodulation(const std::vector<int> BitesVector);

 private:
  float* modulatedSignal, *demodulatedSignal, *multiBuffer, *binarySignal;
  float sum;
};

#endif
