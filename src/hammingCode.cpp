#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "hammingCode.hpp"

HammingCode::HammingCode(std::vector<int>& inputSignal) {
  this->encodeSignal(inputSignal);
  this->crashSignal();
  this->correcError();
  this->decodeSignal();
}

HammingCode::~HammingCode() {}

void HammingCode::encodeSignal(std::vector<int>& inputSignal) {
  int i = 0;

  for (auto x : inputSignal) {
    this->basicSignal.push_back(x);
  }

  printSignal(this->basicSignal, "Input signal");

  this->encodedSignal.push_back(
      (basicSignal[0] + basicSignal[1] + basicSignal[3]) % 2);
  this->encodedSignal.push_back(
      (basicSignal[0] + basicSignal[2] + basicSignal[3]) % 2);
  this->encodedSignal.push_back(basicSignal[0]);
  this->encodedSignal.push_back(
      (basicSignal[1] + basicSignal[2] + basicSignal[3]) % 2);
  
  this->encodedSignal.push_back(basicSignal[1]);
  this->encodedSignal.push_back(basicSignal[2]);
  this->encodedSignal.push_back(basicSignal[3]);

  printSignal(this->encodedSignal, "Encoded signal");
}

void HammingCode::crashSignal() {
  int whichOne = 0;

  std::srand(std::time(0));
  whichOne = std::rand() % 8;

  for (auto x : this->encodedSignal) {
    this->crashedSignal.push_back(x);
  }

  this->crashedSignal[whichOne] = (this->crashedSignal[whichOne] + 1) % 2;

  printSignal(this->crashedSignal, "Crashed Signal");
}

void HammingCode::correcError() {
  int p1 = 0, p2 = 0, p3 = 0;
  int p1Right = 0, p2Right = 0, p3Right = 0;

  p1 = this->crashedSignal[0];
  p2 = this->crashedSignal[1];
  p3 = this->crashedSignal[3];

  p1Right = (p1 == ((this->crashedSignal[2] + this->crashedSignal[4] +
                     this->crashedSignal[6]) %
                    2));
  p2Right = (p2 == ((this->crashedSignal[2] + this->crashedSignal[5] +
                     this->crashedSignal[6]) %
                    2));
  p3Right = (p3 == ((this->crashedSignal[4] + this->crashedSignal[5] +
                     this->crashedSignal[6]) %
                    2));

  if (!p1Right and p2Right and p3Right) {
    this->crashedSignal[0] = (this->crashedSignal[0] + 1) % 2;
  } else if (!p2Right and p1Right and p3Right) {
    this->crashedSignal[1] = (this->crashedSignal[1] + 1) % 2;
  } else if (!p3Right and p1Right and p2Right) {
    this->crashedSignal[3] = (this->crashedSignal[3] + 1) % 2;
  } else {
    std::cout << "None of bits was changed" << std::endl;
  }

  if (p1 != ((this->crashedSignal[2] + this->crashedSignal[4] +
              this->crashedSignal[6]) %
             2) and
      p2 != ((this->crashedSignal[2] + this->crashedSignal[5] +
              this->crashedSignal[6]) %
             2) and
      p3 == ((this->crashedSignal[4] + this->crashedSignal[5] +
              this->crashedSignal[6]) %
             2)) {
    this->crashedSignal[2] = (this->crashedSignal[2] + 1) % 2;
  }

  if (p1 == ((this->crashedSignal[2] + this->crashedSignal[4] +
              this->crashedSignal[6]) %
             2) and
      p2 != ((this->crashedSignal[2] + this->crashedSignal[5] +
              this->crashedSignal[6]) %
             2) and
      p3 != ((this->crashedSignal[4] + this->crashedSignal[5] +
              this->crashedSignal[6]) %
             2)) {
    this->crashedSignal[5] = (this->crashedSignal[5] + 1) % 2;
  }

  if (p1 != ((this->crashedSignal[2] + this->crashedSignal[4] +
              this->crashedSignal[6]) %
             2) and
      p2 == ((this->crashedSignal[2] + this->crashedSignal[5] +
              this->crashedSignal[6]) %
             2) and
      p3 != ((this->crashedSignal[4] + this->crashedSignal[5] +
              this->crashedSignal[6]) %
             2)) {
    this->crashedSignal[4] = (this->crashedSignal[4] + 1) % 2;
  }

  if (p1 != ((this->crashedSignal[2] + this->crashedSignal[4] +
              this->crashedSignal[6]) %
             2) and
      p2 != ((this->crashedSignal[2] + this->crashedSignal[5] +
              this->crashedSignal[6]) %
             2) and
      p3 != ((this->crashedSignal[4] + this->crashedSignal[5] +
              this->crashedSignal[6]) %
             2)) {
    this->crashedSignal[6] = (this->crashedSignal[6] + 1) % 2;
  }

  printSignal(this->crashedSignal, "Repaired signal");
}

void HammingCode::decodeSignal() {
  decodedSignal.assign(4, 0);

  if (this->crashedSignal[2]) decodedSignal[0] = 1;
  if (this->crashedSignal[4]) decodedSignal[1] = 1;
  if (this->crashedSignal[5]) decodedSignal[2] = 1;
  if (this->crashedSignal[6]) decodedSignal[3] = 1;

  printSignal(this->decodedSignal, "Decoded signal");
}

void HammingCode::printSignal(std::vector<int>& v, std::string title) {
  std::cout << std::endl
            << title << std::endl;

  for (auto x : v) {
    std::cout << x << "  ";
  }
  std::cout << std::endl;
}
