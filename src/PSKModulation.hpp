#ifndef PSK_MODULATION_HPP
#define PSK_MODULATION_HPP

#include "sinusDrawing.hpp"

class PSKModulation : public SinusDrawing {
 public:
  using SinusDrawing::SinusDrawing;

  PSKModulation();
  PSKModulation(float Time, float SamplingFrequency);
  PSKModulation(float Time, float SamplingFrequency,
                const std::vector<int>& bitesVector);
  ~PSKModulation();

  void generateModulation(const std::vector<int>& bitesVector);
  void drawPSKChart();
  float* getBuffer();

 protected:
  float* pskBuffer;
};

#endif