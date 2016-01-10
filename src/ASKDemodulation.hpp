#ifndef ASK_DEMODULATION_HPP
#define ASK_DEMODULATION_HPP

#include <vector>

#include "sinusDrawing.hpp"
#include "ASKModulation.hpp"

class ASKDemodulation : public ASKModulation {
 public:
  using ASKModulation::ASKModulation;

  ASKDemodulation();
  ASKDemodulation(float Time, float SamplingFrequency,
                  const std::vector<int>& BitesVector);
  ~ASKDemodulation();

  void generateDemodulation(const std::vector<int>& BitesVector);

 private:
  float* modulatedSignal, *demodulatedSignal, *multiBuffer, *binarySignal;
  float sum;
};

#endif