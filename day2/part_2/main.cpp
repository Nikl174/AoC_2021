#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  int num, position = 0, depth = 0, aim = 0;
  std::string direction;
  while (std::cin >> direction >> num) {
    switch (direction[0]) {
    case 'f':
      position += num;
      depth += aim * num;
      break;
    case 'd':
      aim += num;
      break;
    case 'u':
      aim -= num;
      break;
    }
  }

  std::cout << "Pos: " << position << "; Depth: " << depth
            << "; Product: " << position * depth << std::endl;

  return 0;
}
