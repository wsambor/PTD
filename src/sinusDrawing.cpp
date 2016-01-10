#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstring>

#include "sinusDrawing.hpp"
#define COMMANDS_NUM 2

SinusDrawing::SinusDrawing() {
  ttime = 10;
  samplingFrequency = 0;
  amplitude = 0;
  startPoint = 0;
  signalFrequency = 0;
  N = 0;
  buffer = nullptr;
}

SinusDrawing::SinusDrawing(float Time, float SamplingFrequency) {
  ttime = Time;
  samplingFrequency = SamplingFrequency;
  buffer = nullptr;
  N = Time * SamplingFrequency;

  // Amplitude = 8.0
  // Phase = 0.0
  // Signal Frequency = 10.0
  // Argumenty poniższej funkcji to kolejno:
  //  + częstotliowość sygnału (signalFrequency)
  //  + amplituda (amplitude)
  //  + faza (startingPoint)
  generateSinusSignal(5.0f, 50.0f, 0.0f);
  // printResult();
  // saveAsCSVFile();
  // drawSineChart();
}

SinusDrawing::~SinusDrawing() {
  if (buffer) delete[](buffer);
}

float SinusDrawing::getTime() { return ttime; }

float SinusDrawing::getSamplingFrequency() { return samplingFrequency; }

float *SinusDrawing::allocateBuffer(float Time, float SamplingFrequency) {
  float *tmpBuffer = new float[int(Time * SamplingFrequency)];
  return tmpBuffer;
}

void SinusDrawing::generateSinusSignal(float SignalFrequency, float Amplitude,
                                       float StartPoint) {
  buffer = nullptr;
  buffer = allocateBuffer(ttime, samplingFrequency);
  amplitude = Amplitude;
  startPoint = StartPoint;
  signalFrequency = SignalFrequency;

  for (int i = 0; i < samplingFrequency * ttime; i++) {
    buffer[i] =
        amplitude *
        sin(2 * M_PI * signalFrequency * (i / samplingFrequency) + startPoint);
  }
}

void SinusDrawing::printResult() {
  for (int i = 0; i < samplingFrequency * ttime; i++) {
    std::cout << i << ". value: " << buffer[i] << std::endl;
  }
}

void SinusDrawing::saveAsCSVFile() {
  int beforeComa = 0, afterComa = 0, scaled = 0;
  std::ofstream Morrison_File("../docs/sinusChart.csv");

  for (int i = 0; i < samplingFrequency * ttime; i++) {
    Morrison_File << i << ";";
  }

  Morrison_File << std::endl;

  for (int i = 0; i < samplingFrequency * ttime; i++) {
    scaled = buffer[i] * 100;
    buffer[i] = static_cast<float>(scaled) / 100.0;
    beforeComa = buffer[i];
    afterComa = (buffer[i] - beforeComa) * 100;
    if (buffer[i] < 0) {
      afterComa *= (-1);
    }

    Morrison_File << beforeComa << "," << afterComa << ";";
  }

  Morrison_File.close();
}

void SinusDrawing::drawSineChart() {
  char *commandsForGnuplot[] = {
      (char *)"set title \"PTD; Sine Chart\"",
      (char *)"plot '../docs/sineChartData.temp' using 1:2 with lines"};
  // using 1:2 with lines
  // using 1:2 with impulses
  double xValues[int(samplingFrequency * ttime)];
  double yValues[int(samplingFrequency * ttime)];
  FILE *temp = fopen("../docs/sineChartData.temp", "w");
  FILE *gnuplotPipe = popen("gnuplot -persistent", "w");

  for (int j = 0; j < N - 1; j++) {
    xValues[j] = (double)j;
    yValues[j] = (double)buffer[j];
  }

  for (int i = 0; i < N - 1; i++) {
    fprintf(temp, "%lf %lf \n", xValues[i], yValues[i]);
  }

  for (int i = 0; i < COMMANDS_NUM; i++) {
    fprintf(gnuplotPipe, "%s \n",
            commandsForGnuplot[i]);  // Send commands to gnuplot one by one.
  }
}

void SinusDrawing::drawChart(char *chartName, float *buffer) {
  char *titlePref = (char *)"set title \"";
  char *plotPref = (char *)"plot '../docs/";
  char *plotSuff = (char *)".temp' using 1:2 with lines";
  char *addressPref = (char *)"../docs/";
  char *addressSuff = (char *)".temp";

  char *title;
  title = (char *)malloc(strlen(chartName) + 10 + 2 + 1);
  strcpy(title, titlePref);
  strcat(title, chartName);
  strcat(title, "\"");
  std::cout << title << std::endl;

  char *plot;
  plot = (char *)malloc(strlen(chartName) + 14 + 27 + 1);
  strcpy(plot, plotPref);
  strcat(plot, chartName);
  strcat(plot, plotSuff);
  std::cout << plot << std::endl;

  char *address;
  address = (char *)malloc(strlen(chartName) + 8 + 5 + 1);
  strcpy(address, addressPref);
  strcat(address, chartName);
  strcat(address, addressSuff);
  std::cout << address << std::endl;

  char *commandsForGnuplot[2];
  commandsForGnuplot[0] = (char *)title;
  commandsForGnuplot[1] = (char *)plot;

  double xValues[int(samplingFrequency * ttime)];
  double yValues[int(samplingFrequency * ttime)];
  FILE *temp = fopen((char *)address, "w");
  FILE *gnuplotPipe = popen("gnuplot -persistent", "w");

  for (int j = 0; j < N - 1; j++) {
    xValues[j] = (double)j;
    yValues[j] = (double)buffer[j];
    std::cout << j << ". " << chartName << " value : " << buffer[j]
              << std::endl;
  }

  for (int i = 0; i < N - 1; i++) {
    fprintf(temp, "%lf %lf \n", xValues[i], yValues[i]);
  }

  for (int i = 0; i < COMMANDS_NUM; i++) {
    fprintf(gnuplotPipe, "%s \n",
            commandsForGnuplot[i]);  // Send commands to gnuplot one by one.
  }
}