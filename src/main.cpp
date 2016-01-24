#include <iostream>
#include <cstdlib>

#include "mainFunctions.hpp"
#include "sinusDrawing.hpp"
#include "spectrumDrawing.hpp"
#include "AMModulation.hpp"
#include "PMModulation.hpp"
#include "ASKModulation.hpp"
#include "FSKModulation.hpp"
#include "PSKModulation.hpp"
#include "ASKDemodulation.hpp"
#include "PSKDemodulation.hpp"
#include "FSKDemodulation.hpp"
#include "hammingCode.hpp"

std::vector<int> returnBitesVector(int size);

int main(int argc, char* argv[]) {
  float exampleTime = 1.0f;
  float exampleSamplingFrequency = 900.0f;

  std::vector<int> input;
  input = returnBitesVector(4);

  //Hamming_code___________________________________________________________
  HammingCode richard(input);

  ////DEMODULACJE_ASK__PSK__FSK______________________________________________
  ////Demodulacja ASK
  // ASKDemodulation exampleASKDemodulation(exampleTime,
  // exampleSamplingFrequency, returnBitesVector(10));

  ////Demodulacja PSK
  // PSKDemodulation examplePSKDemodulation(exampleTime,
  // exampleSamplingFrequency, returnBitesVector(10));

  /// Demodulacja FSK
  // FSKDemodulation exampleFSKDemodulation(exampleTime,
  // exampleSamplingFrequency,
  //                                        returnBitesVector(10));

  ////MODULACJE__ASK__FSK__PSK_______________________________________________
  ////Modulacja ASK
  // ASKModulation exampleASKModulation(exampleTime, exampleSamplingFrequency,
  //                                    returnBitesVector(10));

  // FSKModulation exampleFSKModulation(exampleTime, exampleSamplingFrequency,
  //                                    returnBitesVector(10));

  // PSKModulation examplePSKModulation(exampleTime, exampleSamplingFrequency,
  //                                    returnBitesVector(10));

  ////GENEROWANIE WYKRESU FUNKCJI SINUS_____________________________________
  // SinusDrawing exampleObject(exampleTime, exampleSamplingFrequency);

  ////GENEROWANIE WYKRESU WIDMA_____________________________________________
  // SpectrumDrawing exampleSpectrumObject(exampleTime,
  // exampleSamplingFrequency);

  /// GENEROWANIE MODULACJI__AM__PM__________________________________________
  // Aby uzyskać ciekawy rezultatat w konstruktorze sinusDrawing: wielkosc
  // amplitudy wprowadzic równą 5.0f,
  // częstotliwość
  // sygnału równą 15.0f
  /// AMModulation exampleAMModulationObject(exampleTime,
  /// exampleSamplingFrequency);

  // Aby uzyskać ciekawy rezultatat w konstruktorze sinusDrawing: wielkosc
  // amplitudy wprowadzic równą 2.0f,
  // częstotliwość
  // sygnału równą 5.0f
  /// PMModulation examplePMModulationObject(exampleTime,
  /// exampleSamplingFrequency);

  return 0;
}
