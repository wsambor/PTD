#ifndef PM_MODULATION_HPP_
#define PM_MODULATION_HPP_

#include "sinusDrawing.hpp"

class PMModulation : public SinusDrawing {
 public:
  using SinusDrawing::SinusDrawing;

  PMModulation();
  PMModulation(float Time, float SamplingFrequency);
  ~PMModulation();

  void generatePMModulation();
  void drawPMModulationChart();

 private:
  float* messageSignal, *carrierSignal, *modulatedSignal;
};

#endif