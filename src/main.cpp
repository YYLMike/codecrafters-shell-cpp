#include <iostream>
#include <string>

constexpr char EXIT_CMD[] = "exit";
int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // Print prompt
  while (true) {
    std::cout << "$ ";
    std::string command;
    std::cin >> command;
    if (command == "exit") {
        return 0;
    }
    std::cout << command << ": command not found\n";
  }
  return 0;
}
