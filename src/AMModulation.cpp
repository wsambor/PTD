#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>

#include "AMModulation.hpp"
#define COMMANDS_NUM 2

AMModulation::AMModulation() : SinusDrawing() {
  messageSignal = nullptr;
  carrierSignal = nullptr;
  modulatedSignal = nullptr;
};

AMModulation::AMModulation(float Time, float SamplingFrequency)
    : SinusDrawing(Time, SamplingFrequency) {
  generateAMModulation();
  drawAMModulationChart();
};

void AMModulation::generateAMModulation() {
  // z(t)
  carrierSignal = allocateBuffer(this->ttime, this->samplingFrequency);
  // w(t)
  messageSignal = allocateBuffer(this->ttime, this->samplingFrequency);
  // u(t)
  modulatedSignal = allocateBuffer(this->ttime, this->samplingFrequency);

  for (int i = 0; i < N - 1; ++i) {
    carrierSignal[i] =
        amplitude * sin(2 * M_PI * signalFrequency * (i / samplingFrequency));

    messageSignal[i] =
        0.6 * cos(2 * M_PI * (signalFrequency / 7) * (i / samplingFrequency));

    modulatedSignal[i] = (1 + messageSignal[i]) * carrierSignal[i];
  }
}

AMModulation::~AMModulation() {
  if (messageSignal) delete[](messageSignal);
  if (carrierSignal) delete[](carrierSignal);
  if (modulatedSignal) delete[](modulatedSignal);
}

void AMModulation::drawAMModulationChart() {
  char* commandsForGnuplot[] = {
      (char*)"set title \"PTD; AM Modulation Chart\"",
      (char*)"plot '../docs/AMModulationChartData.temp' using 1:2 with lines"};
  // using 1:2 with lines
  // using 1:2 with impulses
  double xValues[int(samplingFrequency * ttime)];
  double yValues[int(samplingFrequency * ttime)];
  FILE* temp = fopen("../docs/AMModulationChartData.temp", "w");
  FILE* gnuplotPipe = popen("gnuplot -persistent", "w");

  for (int j = 0; j < N - 1; j++) {
    xValues[j] = (double)j;
    yValues[j] = (double)modulatedSignal[j];
  }

  for (int i = 0; i < N - 1; i++) {
    fprintf(temp, "%lf %lf \n", xValues[i], yValues[i]);
  }

  for (int i = 0; i < COMMANDS_NUM; i++) {
    fprintf(gnuplotPipe, "%s \n",
            commandsForGnuplot[i]);  // Send commands to gnuplot one by one.
  }
}
