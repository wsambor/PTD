#ifndef SPECTRUM_DRAWING_HPP_
#define SPECTRUM_DRAWING_HPP_

#include <complex>
#include "sinusDrawing.hpp"

typedef std::complex<double> dcmplx;

class SpectrumDrawing : public SinusDrawing {
 public:
  SpectrumDrawing();
  SpectrumDrawing(float Time, float SamplingFrequency);
  ~SpectrumDrawing();
  dcmplx* allocateComplexBuffer();
  dcmplx* getBuffer();
  void makeMagic();
  void calculateAlfa();
  void printResult();
  void printComplexNumbers();
  void saveAsSpectrumCSVFile();
  void drawSpectrumChart();

 private:
  dcmplx* sNumbersBuffer;
  float exponent, *alfaBuffer, *resultBuffer;
};

#endif