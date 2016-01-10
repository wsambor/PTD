#ifndef MAIN_FUNCTONS_HPP
#define MAIN_FUNCTONS_HPP

#include <vector>

std::vector<int> returnBitesVector() {
  srand(time(NULL));
  std::vector<int> bitesVector(0, 0);
  int randNumber = 0;
  auto it = bitesVector.begin();

  for (int i = 0; i < 9; ++i) {
    bitesVector.push_back(rand() % 2);
  }

  return bitesVector;
}

#endif