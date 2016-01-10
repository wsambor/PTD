#pragma once

class SinusDrawing {
 public:
  SinusDrawing();
  SinusDrawing(float Time, float SamplingFrequency);
  ~SinusDrawing();

  void drawSineChart();
  void generateSinusSignal(float signalFrequency, float Amplitude,
                           float StartPoint);
  void printResult();
  float getTime();
  float getSamplingFrequency();
  float* allocateBuffer(float ttime, float samplingFrequency);
  void saveAsCSVFile();

  void drawChart(char* chartName, float* buffer);

 protected:
  float ttime, samplingFrequency, amplitude, startPoint, signalFrequency, N;
  float* buffer;
};