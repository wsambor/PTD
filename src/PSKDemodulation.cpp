#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <vector>

#include "PSKDemodulation.hpp"
#define COMMANDS_NUM 2

PSKDemodulation::PSKDemodulation() {
  modulatedSignal = nullptr;
  demodulatedSignal = nullptr;
  multiBuffer = nullptr;
  sum = 0;
}

PSKDemodulation::PSKDemodulation(float Time, float SamplingFrequency,
                                 const std::vector<int>& BitesVector)
    : PSKModulation(Time, SamplingFrequency, BitesVector) {
  modulatedSignal = getBuffer();
  
  generateDemodulation(BitesVector);
  drawChart((char *)"PSK_After_multiplication", multiBuffer);
  drawChart((char *)"PSK_Demodulation", demodulatedSignal);
  drawChart((char *)"PSK_Binary_Signal", binarySignal);
}

PSKDemodulation::~PSKDemodulation() {
  // if (modulatedSignal) delete[](modulatedSignal);
  if (demodulatedSignal) delete[](demodulatedSignal);
  if (multiBuffer) delete[](multiBuffer);
  if (binarySignal) delete[](binarySignal);
}

void PSKDemodulation::generateDemodulation(const std::vector<int> BitesVector) {
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
        multiBuffer[bit] = modulatedSignal[bit] * 
                    this->amplitude * 
                    sin((2 * M_PI * (this->signalFrequency / 2) * bit) / 100);
        this->sum +=multiBuffer[bit];
        demodulatedSignal[bit] = this->sum;
      }
  this->sum = 0;
    ++i;
  }

  i = 0;
  for (auto x : BitesVector) {
      for (int j = 0; j < 100; j++) {
        bit = (i * 100) + j; 
        if (demodulatedSignal[bit] > 0) {
          binarySignal[bit] = 1;
        } else {
          binarySignal[bit] = 0;
        } 
      }
    ++i;
  }
  binarySignal[bit-1] = 1.2f;
}