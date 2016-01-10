#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <vector>

#include "PSKModulation.hpp"
#define COMMANDS_NUM 2

PSKModulation::PSKModulation() : SinusDrawing() { pskBuffer = nullptr; }

PSKModulation::PSKModulation(float Time, float SamplingFrequency,
                             const std::vector<int>& bitesVector)
    : SinusDrawing(Time, SamplingFrequency) {
  generateModulation(bitesVector);
  drawPSKChart();
}

PSKModulation::~PSKModulation() {
  if (pskBuffer) delete[](pskBuffer);
}

float* PSKModulation::getBuffer() { return pskBuffer; }

void PSKModulation::generateModulation(const std::vector<int>& bitesVector) {
  pskBuffer = allocateBuffer(this->ttime, this->samplingFrequency);

  int bit = 0;
  int i = 0;

  for (auto x : bitesVector) {
    std::cout << i << ". Wartosc bitu : " << x << std::endl;
    for (int j = 0; j < 100; j++) {
      bit = (i * 100) + j;
      if (x == 1) {
        pskBuffer[bit] =
            this->amplitude *
            sin((2 * M_PI * (this->signalFrequency / 2) * bit) / 100);
      } else {
        pskBuffer[bit] =
            this->amplitude *
            sin(((2 * M_PI * (this->signalFrequency / 2) * bit) + 300) / 100);
      }
    }
    ++i;
  }
}

void PSKModulation::drawPSKChart() {
  char* commandsForGnuplot[] = {
      (char*)"set title \"PTD; PSK Modulation Chart\"",
      (char*)"plot '../docs/PSKModulationChartData.temp' using 1:2 with lines"};
  // using 1:2 with lines
  // using 1:2 with impulses
  double xValues[int(samplingFrequency * ttime)];
  double yValues[int(samplingFrequency * ttime)];
  FILE* temp = fopen("../docs/PSKModulationChartData.temp", "w");
  FILE* gnuplotPipe = popen("gnuplot -persistent", "w");

  for (int j = 1; j < N - 1; j++) {
    xValues[j] = (double)j;
    yValues[j] = (double)pskBuffer[j];
    std::cout << j << ". PSK value : " << pskBuffer[j] << std::endl;
  }

  for (int i = 0; i < N - 1; i++) {
    fprintf(temp, "%lf %lf \n", xValues[i], yValues[i]);
  }

  for (int i = 0; i < COMMANDS_NUM; i++) {
    fprintf(gnuplotPipe, "%s \n",
            commandsForGnuplot[i]);  // Send commands to gnuplot one by one.
  }
}