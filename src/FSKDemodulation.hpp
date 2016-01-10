#ifndef FSK_DEMODULATION_HPP
#define FSK_DEMODULATION_HPP

#include <vector>

#include "sinusDrawing.hpp"
#include "FSKModulation.hpp"

class FSKDemodulation : public FSKModulation {
 public:
  using FSKModulation::FSKModulation;

  FSKDemodulation();
  FSKDemodulation(float Time, float SamplingFrequency,
                  const std::vector<int>& BitesVector);
  ~FSKDemodulation();

  void generateDemodulation(const std::vector<int>& BitesVector);
  void drawMulti1Chart();
  void drawMulti2Chart();
  void drawDemodulationChart();
  void drawBinaryChart();

 private:
  float* modulatedSignal, *demodulatedSignal, *multiBuffer1, *multiBuffer2,
      *binarySignal;
  float sumHighFrequency, sumLowFrequency;
};

#endif