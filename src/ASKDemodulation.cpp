#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <string.h>

#include "ASKDemodulation.hpp"
#define COMMANDS_NUM 2

ASKDemodulation::ASKDemodulation() {
  modulatedSignal = nullptr;
  demodulatedSignal = nullptr;
  multiBuffer = nullptr;
  sum = 0;
}

ASKDemodulation::ASKDemodulation(float Time, float SamplingFrequency,
                                 const std::vector<int> &BitesVector)
    : ASKModulation(Time, SamplingFrequency, BitesVector) {
  modulatedSignal = getBuffer();

  generateDemodulation(BitesVector);
  drawChart((char *)"Chart_after_multiplication", multiBuffer);
  drawChart((char *)"Demodulated_signal", demodulatedSignal);
  drawChart((char *)"Binary_signal", binarySignal);
}

ASKDemodulation::~ASKDemodulation() {
  // if (modulatedSignal) delete[](modulatedSignal);
  if (demodulatedSignal) delete[](demodulatedSignal);
  if (multiBuffer) delete[](multiBuffer);
  if (binarySignal) delete[](binarySignal);
}

void ASKDemodulation::generateDemodulation(
    const std::vector<int> &BitesVector) {
  multiBuffer = allocateBuffer(this->ttime, this->samplingFrequency);
  demodulatedSignal = allocateBuffer(this->ttime, this->samplingFrequency);
  binarySignal = allocateBuffer(this->ttime, this->samplingFrequency);

  int bit = 0;
  int i = 0;
  this->sum = 0;

  for (auto x : BitesVector) {
    std::cout << i << ". bit's value: " << x << std::endl;
    for (int j = 0; j < 100; j++) {
      bit = (i * 100) + j;
      multiBuffer[bit] =
          modulatedSignal[bit] * this->amplitude *
          sin((2 * M_PI * (this->signalFrequency / 2) * bit) / 100);
      this->sum += multiBuffer[bit];
      demodulatedSignal[bit] = this->sum;
    }
    this->sum = 0;
    ++i;
  }

  i = 0;
  for (int k = 0; k < BitesVector.size(); ++k) {
    for (int j = 0; j < 100; j++) {
      bit = (i * 100) + j;
      if (demodulatedSignal[bit] > 0) {
        binarySignal[bit] = 1.0f;
      } else {
        binarySignal[bit] = 0.0f;
      }
    }
    ++i;
  }
  binarySignal[bit - 1] = 1.2f;
}