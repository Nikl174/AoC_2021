#include <bitset>
#include <iostream>

#define SIZE 12

void mostCommonBit(char bin[SIZE + 1], int mcb[SIZE]) {
  for (int i = 0; i < SIZE; i++) {
    switch (bin[i]) {
    case '1':
      mcb[i] += 1;
      break;
    case '0':
      mcb[i] -= 1;
      break;
    default:
      std::cout << "FEHLER!" << std::endl;
      return;
    }
  }
}

int main(int argc, char *argv[]) {
  int length = 0, mcb[SIZE] = {0};
  char bin[SIZE + 1];
  while (std::cin >> bin) {
    mostCommonBit(bin, mcb);
    length++;
  }
  unsigned int i, gamma = 0, epsilon=0;
  for (i = 0; i < SIZE; ++i) {
    bool binI = !( mcb[i] & (0x80000000) );
    std::cout << "binI="<<binI<<"; mcb="<<mcb[i] << std::endl;
    gamma += (binI << (SIZE - i-1));
    epsilon +=(!binI << (SIZE - i-1));
  }
  //wrong because of th first bits -> 32bit integer value..
  //unsigned int epsilon = ~gamma;
  std::cout << gamma << "; " << std::bitset<12>(gamma) << std::endl;
  std::cout << epsilon << "; " << std::bitset<12>(epsilon)<< std::endl;

  std::cout << "Solution gamma*epsilon="<<gamma*epsilon << std::endl;
  return 0;
}
