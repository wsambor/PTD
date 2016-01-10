#include <iostream>
#include <math.h>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <complex>

#include "spectrumDrawing.hpp"
#define COMMANDS_NUM 2

SpectrumDrawing::SpectrumDrawing() {
  /// SinusDrawing class attributes
  ttime = 0;
  samplingFrequency = 0;
  amplitude = 0;
  startPoint = 0;
  signalFrequency = 0;
  buffer = nullptr;

  /// Current class attributes
  sNumbersBuffer = nullptr;
  exponent = 0;
  alfaBuffer = nullptr;
  resultBuffer = nullptr;
}

SpectrumDrawing::SpectrumDrawing(float Time, float SamplingFrequency) {
  /// SinusDrawing class attributes
  ttime = Time;
  samplingFrequency = SamplingFrequency;
  buffer = nullptr;
  N = Time * SamplingFrequency;

  // Amplitude = 8.0
  // Phase = 0.0
  // Signal Frequency = 10.0
  generateSinusSignal(10.0f, 8.0f, 0.0f);
  saveAsCSVFile();
  drawSineChart();

  /// Current class attributes
  makeMagic();
  printComplexNumbers();
  printResult();
  saveAsSpectrumCSVFile();
  drawSpectrumChart();
}

SpectrumDrawing::~SpectrumDrawing() {
  if (sNumbersBuffer) delete[](sNumbersBuffer);
  if (resultBuffer) delete[](resultBuffer);
}

dcmplx* SpectrumDrawing::allocateComplexBuffer() {
  dcmplx* tmpBuffer = new dcmplx[int(ttime * samplingFrequency)];
  return tmpBuffer;
}

dcmplx* SpectrumDrawing::getBuffer() { return sNumbersBuffer; }

void SpectrumDrawing::makeMagic() {
  sNumbersBuffer = allocateComplexBuffer();
  resultBuffer = allocateBuffer(this->ttime, this->samplingFrequency);
  dcmplx tmpNumber = (0, 0);

  for (int i = 0; i < N - 1; ++i) {
    tmpNumber = (0, 0);
    for (int j = 0; j < N - 1; ++j) {
      exponent = (2 * M_PI * i * j) / N;
      tmpNumber +=
          (dcmplx)((buffer[j] * cos(exponent)), (buffer[j] * sin(exponent)));
    }
    resultBuffer[i] =
        sqrt(pow(std::real(tmpNumber), 2) + pow(std::imag(tmpNumber), 2));
    sNumbersBuffer[i] = tmpNumber;
  }
}

void SpectrumDrawing::saveAsSpectrumCSVFile() {
  std::ofstream Morrison_File_S("../docs/spectrum.csv");

  for (int i = 0; i < int(N / 2); i++) {
    Morrison_File_S << int(std::real(sNumbersBuffer[i])) << ";"
                    << int(std::imag(sNumbersBuffer[i])) << std::endl;
  }

  Morrison_File_S.close();
}

void SpectrumDrawing::printComplexNumbers() {
  for (int i = 0; i < N; ++i) {
    std::cout << i << ". element (cmplx number) : " << sNumbersBuffer[i]
              << std::endl;
  }
}

void SpectrumDrawing::printResult() {
  for (int i = 0; i < N; ++i) {
    std::cout << i << ". element (result number) : " << resultBuffer[i]
              << std::endl;
  }
}

void SpectrumDrawing::drawSpectrumChart() {
  char* commandsForGnuplot[] = {
      (char*)"set title \"PTD; Spectrum Chart\"",
      (char*)"plot '../docs/spectrumData.temp' using 1:2 with lines"};
  // using 1:2 with lines
  // using 1:2 with impulses
  double xValues[int(N / 2) + 1];
  double yValues[int(N / 2) + 1];
  FILE* temp = fopen("../docs/spectrumData.temp", "w");
  FILE* gnuplotPipe = popen("gnuplot -persistent", "w");

  for (int j = 0; j < (N / 2) - 1; j++) {
    xValues[j] = (double)j;
    yValues[j] = (double)resultBuffer[j];
  }

  for (int i = 0; i < (N / 2) - 1; i++) {
    fprintf(temp, "%lf %lf \n", xValues[i], yValues[i]);
  }

  for (int i = 0; i < COMMANDS_NUM; i++) {
    fprintf(gnuplotPipe, "%s \n",
            commandsForGnuplot[i]);  // Send commands to gnuplot one by one.
  }
}

void SpectrumDrawing::calculateAlfa() {
  alfaBuffer = allocateBuffer(this->ttime, this->samplingFrequency);

  for (int i = 0; i < N; ++i) {
    alfaBuffer[i] = atan(
        (float)(std::real(sNumbersBuffer[i]) / std::imag(sNumbersBuffer[i])));
  }
}