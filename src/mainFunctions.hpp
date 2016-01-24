#ifndef MAIN_FUNCTONS_HPP
#define MAIN_FUNCTONS_HPP

#include <vector>

std::vector<int> returnBitesVector(int size) {
  srand(time(NULL));
  std::vector<int> bitesVector(0, 0);
  int randNumber = 0;
  auto it = bitesVector.begin();

  for (int i = 0; i < size; ++i) {
    bitesVector.push_back(rand() % 2);
  }

  return bitesVector;
}

#endif