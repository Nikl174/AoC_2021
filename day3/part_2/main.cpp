#include <bitset>
#include <cstdio>
#include <future>
#include <iostream>
#include <vector>

#define SIZE 12
std::vector<char *> zero;
std::vector<char *> one;

void mostCommonBit(int bit, int &mcb, char bin[SIZE + 1]) {
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

void mostCommonBitNextGen(int bit, int &mcb, std::vector<char *> input) {
    zero.clear();
    one.clear();
    int i;
    for (i = 0; i < input.size(); ++i) {
        std::cout << input[i] << std::endl;
    mostCommonBit(bit, mcb, input[i]);
    }
}

// LRF==Live Support Rating
char *recursevlyCalcOGR(int bit, std::vector<char *> input) {
  if (bit == SIZE || input.size()==1) {
    return input.back();
  }
  int mcb;
  mostCommonBitNextGen(bit, mcb, input);
  std::cout << "MCB: " << mcb << " VecSize: " << input.size() 
            << " ZeroSize: " << zero.size()
            << " OneSize: " << one.size() << std::endl;
  if (mcb > 0) {
    return recursevlyCalcOGR(bit + 1, one);
  } else if (mcb < 0) {
    return recursevlyCalcOGR(bit + 1, zero);
  } else {
    return recursevlyCalcOGR(bit + 1, one);
  }
}

char *recursevlyCalcCSR(int bit, std::vector<char *> input) {
  if (bit == SIZE || input.size()==1) {
    return input.back();
  }
  int mcb;
  std::vector<char *> oneList, zeroList;
  mostCommonBitNextGen(bit, mcb, input);
  std::cout << "MCB: " << mcb << std::endl;
  if (mcb > 0) {
    return recursevlyCalcCSR(bit + 1, zero);
  } else if (mcb < 0) {
    return recursevlyCalcCSR(bit + 1, one);
  } else {
    return recursevlyCalcCSR(bit + 1, zero);
  }
}

int main(int argc, char *argv[]) {
  int mcb = 0;
  char bin[SIZE + 1];
  while (std::cin >> bin) {
    mostCommonBit(0, mcb, bin);
  }
  std::cout << "MCB: " << mcb <<  " ZeroSize: " << zero.size()
            << " OneSize: " << one.size() << std::endl;

  std::future<char *> tOGR;
  std::future<char *> tCSR;
  char *csr;
  char *ogr;
  if (mcb > 0) {
    ogr = recursevlyCalcOGR(1, one);
    csr = recursevlyCalcCSR(1, zero);
    // tOGR = std::async(recursevlyCalcOGR,1,oneList);
    // tCSR = std::async(recursevlyCalcCSR,1,zeroList);
  } else if (mcb < 0) {
    ogr = recursevlyCalcOGR(1, zero);
    csr = recursevlyCalcCSR(1, one);
    // tOGR = std::async(recursevlyCalcOGR,1,zeroList);
    // tCSR = std::async(recursevlyCalcCSR,1,oneList);
  } else {
    ogr = recursevlyCalcOGR(1, one);
    csr = recursevlyCalcCSR(1, zero);
    // tOGR = std::async(recursevlyCalcOGR,1,oneList);
    // tCSR = std::async(recursevlyCalcCSR,1,zeroList);
  }
  //csr = tCSR.get();
  //ogr = tOGR.get();
  int i, CSR = 0, OGR = 0;
  for (i = 0; i < SIZE; ++i) {
    CSR += int(csr[i]) << (SIZE - i - 1);
    OGR += int(ogr[i]) << (SIZE - i - 1);
  }

  std::cout << "Solution: " << CSR * OGR << std::endl;
  return 0;
}
