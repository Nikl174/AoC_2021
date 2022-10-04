#include <bitset>
#include <cstdio>
#include <future>
#include <iostream>
#include <vector>

#define SIZE 12

void mostCommonBit(int bit, int &mcb, char bin[SIZE + 1],
                   std::vector<char *> &zero, std::vector<char *> &one) {
  switch (bin[bit]) {
  case '1':
    mcb += 1;
    one.push_back(bin);
    break;
  case '0':
    mcb -= 1;
    zero.push_back(bin);
    break;
  default:
    std::cout << "FEHLER!" << std::endl;
    return;
  }
}

void mostCommonBitNextGen(int bit, int &mcb, std::vector<char *> input,
                          std::vector<char *> &zero, std::vector<char *> &one) {
  for (char *i : input) {
    mostCommonBit(bit, mcb, i, zero, one);
  }
}

// LRF==Live Support Rating
char* recursevlyCalcOGR(int bit, std::vector<char *> input) {
  if (bit == SIZE) {
    return input.back();
  }
  int mcb;
  std::vector<char *> oneList, zeroList;
  mostCommonBitNextGen(bit, mcb, input, zeroList, oneList);
  if (mcb > 0) {
    return recursevlyCalcOGR(bit + 1, oneList);
  } else if (mcb < 0) {
    return recursevlyCalcOGR(bit + 1, zeroList);
  } else {
    return recursevlyCalcOGR(bit + 1, oneList);
  }
}

char *recursevlyCalcCSR(int bit, std::vector<char *> input) {
  if (bit == SIZE) {
    return input.back();
  }
  int mcb;
  std::vector<char *> oneList, zeroList;
  mostCommonBitNextGen(bit, mcb, input, zeroList, oneList);
  if (mcb > 0) {
    return recursevlyCalcCSR(bit + 1, zeroList);
  } else if (mcb < 0) {
    return recursevlyCalcCSR(bit + 1, oneList);
  } else {
    return recursevlyCalcCSR(bit + 1, zeroList);
  }
}

int main(int argc, char *argv[]) {
  int mcb = 0;
  char bin[SIZE + 1];
  std::vector<char *> oneList, zeroList;
  while (std::cin >> bin) {
    mostCommonBit(0, mcb, bin, zeroList, oneList);
  }
  std::future<char*> tOGR;
      std::future<char*> tCSR;
  if (mcb>0) {
      tOGR = std::async(recursevlyCalcOGR,1,oneList);
      tCSR = std::async(recursevlyCalcCSR,1,zeroList);
  } else if (mcb<0) {
      tOGR = std::async(recursevlyCalcOGR,1,zeroList);
      tCSR = std::async(recursevlyCalcCSR,1,oneList);
  } else {
      tOGR = std::async(recursevlyCalcOGR,1,oneList);
      tCSR = std::async(recursevlyCalcCSR,1,zeroList);
  }
  char* csr = tCSR.get();
  char* ogr = tOGR.get();
  int i, CSR=0, OGR=0;
  for (i = 0; i < SIZE; ++i) {
      CSR += int(csr[i])<<(SIZE-i-1);
      OGR += int(ogr[i])<<(SIZE-i-1);
  }

  std::cout << "Solution: "<< CSR*OGR << std::endl;
  return 0;
}
