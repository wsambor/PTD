#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <vector>

#include "FSKDemodulation.hpp"
#define COMMANDS_NUM 2

FSKDemodulation::FSKDemodulation() {
  modulatedSignal = nullptr;
  demodulatedSignal = nullptr;
  multiBuffer1 = nullptr;
  multiBuffer2 = nullptr;
  sumHighFrequency = 0;
  sumLowFrequency = 0;
}

FSKDemodulation::FSKDemodulation(float Time, float SamplingFrequency,
                                 const std::vector<int> &BitesVector)
    : FSKModulation(Time, SamplingFrequency, BitesVector) {
  modulatedSignal = getBuffer();

  generateDemodulation(BitesVector);
  drawChart((char *)"FSK_After_multiplication_no1", multiBuffer1);
  drawChart((char *)"FSK_After_multiplication_no2", multiBuffer2);
  drawChart((char *)"FSK_Demodulation", demodulatedSignal);
  drawChart((char *)"FSK_Binary_Signal", binarySignal);
}

FSKDemodulation::~FSKDemodulation() {
  // if (modulatedSignal) delete[](modulatedSignal);
  if (demodulatedSignal) delete[](demodulatedSignal);
  if (multiBuffer1) delete[](multiBuffer1);
  if (multiBuffer2) delete[](multiBuffer2);
  if (binarySignal) delete[](binarySignal);
}

void FSKDemodulation::generateDemodulation(
    const std::vector<int> &BitesVector) {
  multiBuffer1 = allocateBuffer(this->ttime, this->samplingFrequency);
  multiBuffer2 = allocateBuffer(this->ttime, this->samplingFrequency);
  demodulatedSignal = allocateBuffer(this->ttime, this->samplingFrequency);
  binarySignal = allocateBuffer(this->ttime, this->samplingFrequency);

  int bit = 0, tempBit = 0, i = 0, ii = 0, highFrequency = 0, lowFrequency = 0;
  this->sumHighFrequency = 0;
  this->sumLowFrequency = 0;

  for (auto x : BitesVector) {
    std::cout << i << ". bit's value: " << x << std::endl;
    for (int j = 0; j < 100; j++) {
      bit = (i * 100) + j;
      multiBuffer2[bit] =
          modulatedSignal[bit] * this->amplitude *
          sin((6 * M_PI * (this->signalFrequency / 2) * bit) / 100);
      multiBuffer1[bit] =
          modulatedSignal[bit] * this->amplitude *
          sin((2 * M_PI * (this->signalFrequency / 2) * bit) / 100);

      this->sumHighFrequency += multiBuffer2[bit];
      this->sumLowFrequency += multiBuffer1[bit];

      demodulatedSignal[bit] = this->sumHighFrequency - this->sumLowFrequency;
    }

    this->sumHighFrequency = 0;
    this->sumLowFrequency = 0;
    ++i;
  }

  i = 0;
  for (int k = 0; k < BitesVector.size(); ++k) {
    for (int j = 0; j < 100; j++) {
      bit = (i * 100) + j;
      if (demodulatedSignal[bit] > 0) {
        ++highFrequency;
      } else {
        ++lowFrequency;
      }
    }
    for (int j = 0; j < 100; j++) {
      tempBit = (ii * 100) + j;
      if (highFrequency > lowFrequency) {
        binarySignal[tempBit] = 1;
      } else {
        binarySignal[tempBit] = 0;
      }
    }
    highFrequency = 0;
    lowFrequency = 0;
    ++i;
    ++ii;
  }
  binarySignal[tempBit - 1] = 1.2f;
}