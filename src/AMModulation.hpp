#ifndef AM_MODULATION_HPP_
#define AM_MODULATION_HPP_

#include "sinusDrawing.hpp"

class AMModulation : public SinusDrawing {
 public:
  using SinusDrawing::SinusDrawing;

  AMModulation();
  AMModulation(float Time, float SamplingFrequency);
  ~AMModulation();

  void generateAMModulation();
  void drawAMModulationChart();

 private:
  float* messageSignal, *carrierSignal, *modulatedSignal;
};

#endif