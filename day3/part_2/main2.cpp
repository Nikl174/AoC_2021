#include <iostream>
#include <string>
#include <vector>
#define SIZE 12

void mostCommonBit(int bit, std::vector<std::string> bin, int &mcb,
                   std::vector<std::string> &zero,
                   std::vector<std::string> &one) {
  for (auto i : bin) {
      std::cout << "Bin: "<<i << std::endl;
    switch (i.at(bit)) {
    case '1':
      mcb += 1;
      one.push_back(i);
      break;
    case '0':
      mcb -= 1;
      zero.push_back(i);
      break;
    default:
      std::cout << "FEHLER!" << std::endl;
      return;
    }
  }
}

std::string recCalcOGR(int bit, std::vector<std::string> input) {

  if (bit == SIZE || input.size() == 1) {
    std::cout << "VecSize: " << input.size() << std::endl;
    return input.back();
  }

  int mcb = 0;
  std::vector<std::string> one, zero;
  one.clear();
  zero.clear();
  mostCommonBit(bit, input, mcb, zero, one);
  std::cout << "OGR;  Bit:" << bit << " MCB: " << mcb << " VecSize: " << input.size()
            << " ZeroSize: " << zero.size() << " OneSize: " << one.size()
            << std::endl;
  if (one.size() != 0 && zero.size() != 0) {
    if (mcb > 0) {
      return recCalcOGR(bit + 1, one);
    } else if (mcb < 0) {
      return recCalcOGR(bit + 1, zero);
    } else {
      return recCalcOGR(bit + 1, one);
    }
  } else {
    if (one.size() == 0) {
      return recCalcOGR(bit + 1, zero);
    } else {
      return recCalcOGR(bit + 1, one);
    }
  }
}

std::string recCalcCSR(int bit, std::vector<std::string> input) {

  if (bit == SIZE || input.size() == 1) {
    std::cout << "VecSize: " << input.size() << std::endl;
    return input.back();
  }

  int mcb = 0;
  std::vector<std::string> one, zero;
  one.clear();
  zero.clear();
  mostCommonBit(bit, input, mcb, zero, one);
  std::cout << "CSR; Bit:" << bit << " MCB: " << mcb
            << " VecSize: " << input.size() << " ZeroSize: " << zero.size()
            << " OneSize: " << one.size() << std::endl;
  if (one.size() != 0 && zero.size() != 0) {
    if (mcb > 0) {
      return recCalcCSR(bit + 1, zero);
    } else if (mcb < 0) {
      return recCalcCSR(bit + 1, one);
    } else {
      return recCalcCSR(bit + 1, zero);
    }
  } else {
    if (one.size() == 0) {
      return recCalcCSR(bit + 1, zero);
    } else {
      return recCalcCSR(bit + 1, one);
    }
  }
}

int main(int argc, char *argv[]) {
  std::string bin, ogr, csr;
  std::vector<std::string> original;
  while (std::cin >> bin) {
    original.push_back(bin);
  }
  std::cout << "OriginalSize: " << original.size() << std::endl;
  ogr = recCalcOGR(0, original);
  csr = recCalcCSR(0, original);
  std::cout << "csr: " << csr << " ogr: " << ogr << std::endl;
  int i, CSR = 0, OGR = 0;
  for (i = 0; i < SIZE; ++i) {
    CSR += (int(csr[i]) - 48) << (SIZE - i - 1);
    OGR += (int(ogr[i]) - 48) << (SIZE - i - 1);
  }
  std::cout << "CSR: " << CSR << " OGR: " << OGR << std::endl;
  std::cout << "Solution: " << CSR * OGR << std::endl;

  return 0;
}
