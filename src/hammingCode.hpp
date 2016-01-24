#ifndef HAMMING_CODE_HPP_
#define HAMMING_CODE_HPP_

#include "sinusDrawing.hpp"

#include <vector>
#include <string>

class HammingCode {
 public:
  HammingCode(std::vector<int>& inputSignal);
  ~HammingCode();

  void encodeSignal(std::vector<int>& inputSignal);
  void crashSignal();
  void decodeSignal();
  void correcError();
  void printSignal(std::vector<int>& signal, std::string title);

 private:
  std::vector<int> basicSignal, encodedSignal, crashedSignal, decodedSignal;
};

#endif