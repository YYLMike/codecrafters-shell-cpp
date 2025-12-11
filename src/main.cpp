#include <iostream>
#include <string>

constexpr char EXIT_CMD[] = "exit";
constexpr char ECHO_CMD[] = "echo";

std::string get_command(const std::string_view arg) {
    std::string command{};
    if (auto first_space = arg.find(' '); first_space != std::string::npos) {
        command = arg.substr(0, first_space);
    } else {
        command = arg;
    }
    return command;
}

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // Print prompt
  while (true) {
    std::cout << "$ ";
    std::string user_in;

    std::getline(std::cin, user_in);
    std::string command = get_command(user_in);

    if (command == EXIT_CMD) {
        return 0;
    } else if (command == ECHO_CMD) {
        std::string arg = user_in.substr(command.length()+1);
        std::cout << arg << "\n";
    } else {
        std::cout << user_in << ": command not found\n";
    }
  }
  return 0;
}
