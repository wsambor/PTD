#ifndef FSK_MODULATION_HPP
#define FSK_MODULATION_HPP

#include <vector>

#include "sinusDrawing.hpp"

class FSKModulation : public SinusDrawing {
 public:
  using SinusDrawing::SinusDrawing;

  FSKModulation();
  FSKModulation(float Time, float SamplingFrequency);
  FSKModulation(float Time, float SamplingFrequency,
                const std::vector<int>& bitesVector);
  ~FSKModulation();

  void generateModulation(const std::vector<int>& bitesVector);
  void drawFSKChart();
  float* getBuffer();

 protected:
  float* fskBuffer;
};

#endif