#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <vector>

#include "ASKModulation.hpp"
#define COMMANDS_NUM 2

ASKModulation::ASKModulation() : SinusDrawing() { askBuffer = nullptr; }

ASKModulation::ASKModulation(float Time, float SamplingFrequency,
                             const std::vector<int>& bitesVector)
    : SinusDrawing(Time, SamplingFrequency) {
  generateModulation(bitesVector);
  drawASKChart();
}

ASKModulation::~ASKModulation() {
  if (askBuffer) delete[](askBuffer);
}

void ASKModulation::generateModulation(const std::vector<int>& bitesVector) {
  askBuffer = allocateBuffer(this->ttime, this->samplingFrequency);

  int bit = 0;
  int i = 0;

  for (auto x : bitesVector) {
    std::cout << i << ". Wartosc bitu : " << x << std::endl;
    for (int j = 0; j < 100; j++) {
      bit = (i * 100) + j;
      if (x == 1) {
        askBuffer[bit] =
            this->amplitude *
            sin((2 * M_PI * (this->signalFrequency / 2) * bit) / 100);
      } else {
        askBuffer[bit] = 0;
        // 0.5 * this->amplitude *
        // sin((2 * M_PI * (this->signalFrequency / 2) * bit) / 100);
      }
    }
    ++i;
  }
}

float* ASKModulation::getBuffer() { return askBuffer; }

void ASKModulation::drawASKChart() {
  char* commandsForGnuplot[] = {
      (char*)"set title \"PTD; ASK Modulation Chart\"",
      (char*)"plot '../docs/ASKModulationChartData.temp' using 1:2 with lines"};
  // using 1:2 with lines
  // using 1:2 with impulses
  double xValues[int(samplingFrequency * ttime)];
  double yValues[int(samplingFrequency * ttime)];
  FILE* temp = fopen("../docs/ASKModulationChartData.temp", "w");
  FILE* gnuplotPipe = popen("gnuplot -persistent", "w");

  for (int j = 0; j < N - 1; j++) {
    xValues[j] = (double)j;
    yValues[j] = (double)askBuffer[j];
    std::cout << j << ". ASK value : " << askBuffer[j] << std::endl;
  }

  for (int i = 0; i < N - 1; i++) {
    fprintf(temp, "%lf %lf \n", xValues[i], yValues[i]);
  }

  for (int i = 0; i < COMMANDS_NUM; i++) {
    fprintf(gnuplotPipe, "%s \n",
            commandsForGnuplot[i]);  // Send commands to gnuplot one by one.
  }
}