#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  int num, position = 0, depth = 0;
  std::string direction;
  while (std::cin >> direction >> num) {
    switch (direction[0]) {
    case 'f':
      position += num;
      break;
    case 'd':
      depth += num;
      break;
    case 'u':
      depth -= num;
      break;
    }
  }

  std::cout << "Pos: " << position << "; Depth: " << depth
            << "; Product: " << position * depth << std::endl;

  return 0;
}
