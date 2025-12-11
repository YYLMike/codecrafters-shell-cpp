#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // Print prompt
  std::cout << "$ ";
  std::string command;
  std::cin >> command;
  std::cout << command << "\n";
}
