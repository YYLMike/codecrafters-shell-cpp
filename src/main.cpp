#include <iostream>
#include <string>

constexpr char EXIT_CMD[] = "exit";
constexpr char ECHO_CMD[] = "echo";
constexpr char TYPE_CMD[] = "type";
constexpr char ISBUILTIN_MSG[] = " is a shell builtin";
constexpr char NOTFOUND_MSG[] = ": not found";
constexpr char COMMANDNOTFOUND_MSG[] = ": command not found";

bool is_builtin (const std::string_view arg) {
    return  arg == EXIT_CMD || arg == ECHO_CMD || arg == TYPE_CMD;
}

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
    std::string arg = user_in.length() > command.length() ? user_in.substr(command.length()+1) : "";

    if (command == EXIT_CMD) {
        return 0;
    } else if (command == ECHO_CMD) {
        std::cout << arg << "\n";
    } else if (command == TYPE_CMD) {
        if (is_builtin(arg)) {
            std::cout << arg << ISBUILTIN_MSG << "\n";
        } else {
            std::cout << arg << NOTFOUND_MSG << "\n";
        }
    } else {
        std::cout << user_in << COMMANDNOTFOUND_MSG << "\n";
    }
  }
  return 0;
}
