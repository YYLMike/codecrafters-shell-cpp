#include <iostream>
#include <filesystem>
#include <string>
#include <sstream>
#include <system_error>

constexpr char EXIT_CMD[] = "exit";
constexpr char ECHO_CMD[] = "echo";
constexpr char TYPE_CMD[] = "type";
constexpr char ISBUILTIN_MSG[] = " is a shell builtin";
constexpr char NOTFOUND_MSG[] = ": not found";
constexpr char COMMANDNOTFOUND_MSG[] = ": command not found";

bool is_builtin (const std::string_view arg) {
    return  arg == EXIT_CMD || arg == ECHO_CMD || arg == TYPE_CMD;
}

bool is_executable(const std::string& path) {
    std::error_code ec;
    std::filesystem::file_status s = std::filesystem::status(path, ec);
    if (ec) {
        // file not exist
        return false;
    }
    if (!std::filesystem::is_regular_file(s)) {
        // not regular file, maybe directory or symlink
        return false;
    }
    std::filesystem::perms prms = s.permissions();
    bool executable = (prms & std::filesystem::perms::owner_exec) != std::filesystem::perms::none ||
        (prms & std::filesystem::perms::group_exec) != std::filesystem::perms::none ||
        (prms & std::filesystem::perms::others_exec) != std::filesystem::perms::none;
    return executable;
}

bool is_path(const std::string_view arg, std::string& fullpath) {
    const std::string paths = getenv("PATH");
    if (paths == "" || paths == "\n" || paths.empty()) {
        return false;
    }
    std::stringstream ss(paths);
    std::string path{};
    while (std::getline(ss, path, ':')) {
        path += "/";
        path += arg;
        if (is_executable(path)) {
            fullpath = path;
            return true;
        }
    }
    return false;
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

  std::string user_in;
  std::string command;
  std::string arg;
  std::string fullpath;
  while (true) {
    // Read
    std::cout << "$ ";
    std::getline(std::cin, user_in);
    command = get_command(user_in);
    arg = user_in.length() > command.length() ? user_in.substr(command.length()+1) : "";

    // Evaluate
    if (command == EXIT_CMD) {
        return 0;
    } else if (command == ECHO_CMD) {
        std::cout << arg << "\n";
    } else if (command == TYPE_CMD) {
        if (is_builtin(arg)) {
            std::cout << arg << ISBUILTIN_MSG << "\n";
        } else if (is_path(arg, fullpath)){
            std::cout << arg << " is " << fullpath << "\n";
        } else {
            std::cout << arg << NOTFOUND_MSG << "\n";
        }
    } else {
        std::cout << user_in << COMMANDNOTFOUND_MSG << "\n";
    }
  } // Loop
  return 0;
}
