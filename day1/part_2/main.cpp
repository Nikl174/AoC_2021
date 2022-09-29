#include <iostream>

int main(int argc, char *argv[]) {
  int i = 1;
  int bigger = 0;
  int current =
      std::atoi(argv[i]) + std::atoi(argv[i+1]) + std::atoi(argv[i+2]);
  while (argv[i+3]) {
      std::cout << "Current: "<< current << std::endl;
    int next =
      std::atoi(argv[++i]) + std::atoi(argv[i+1]) + std::atoi(argv[i+2]);
    if (next > current) {
	bigger++;
    }
    current=next;
  }
  std::cout << bigger << std::endl;
  return 0;
}
