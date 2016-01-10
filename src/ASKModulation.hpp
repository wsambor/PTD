#ifndef ASK_MODULATION_HPP
#define ASK_MODULATION_HPP

#include <vector>
#include "sinusDrawing.hpp"

class ASKModulation : public SinusDrawing {
 public:
  using SinusDrawing::SinusDrawing;

  ASKModulation();
  ASKModulation(float Time, float SamplingFrequency);
  ASKModulation(float Time, float SamplingFrequency,
                const std::vector<int>& bitesVector);
  ~ASKModulation();

  void generateModulation(const std::vector<int>& bitesVector);
  void drawASKChart();
  float* getBuffer();

 protected:
  float* askBuffer;
};

#endif