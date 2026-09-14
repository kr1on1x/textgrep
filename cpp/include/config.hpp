#pragma once
#include <filesystem>
#include <optional>
#include <string>

struct Config {
    std::string query;
    std::filesystem::path path;
    bool ignore_case = false;
    bool line_number = false;
    bool include_hidden = false;
    std::optional<std::string> extension;
};

Config parse_arguments(int argc, char* argv[]);
void print_help();
