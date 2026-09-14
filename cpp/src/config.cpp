#include "config.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace {
bool is_option(const std::string& argument) { return !argument.empty() && argument[0] == '-'; }
std::string normalize_extension(std::string extension) { if (!extension.empty() && extension.front() == '.') extension.erase(extension.begin()); return extension; }
}

void print_help() {
    std::cout << "textgrep - search text recursively inside files\n\n"
              << "Usage:\n  textgrep <query> <path> [options]\n\n"
              << "Options:\n"
              << "  -i, --ignore-case       ignore case when searching\n"
              << "  -n, --line-number      show line numbers\n"
              << "      --hidden           include hidden files and directories\n"
              << "      --ext <extension>  search only files with this extension\n"
              << "  -h, --help             show this help message\n";
}

Config parse_arguments(int argc, char* argv[]) {
    if (argc == 1) { print_help(); std::exit(0); }
    if (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h") { print_help(); std::exit(0); }
    if (argc < 3) throw std::runtime_error("Usage: textgrep <query> <path> [options]");
    Config config;
    int index = 1;
    config.query = argv[index++];
    config.path = argv[index++];
    while (index < argc) {
        std::string argument = argv[index++];
        if (argument == "-i" || argument == "--ignore-case") config.ignore_case = true;
        else if (argument == "-n" || argument == "--line-number") config.line_number = true;
        else if (argument == "--hidden") config.include_hidden = true;
        else if (argument == "--ext") {
            if (index >= argc) throw std::runtime_error("--ext requires an extension");
            config.extension = normalize_extension(argv[index++]);
        } else if (argument == "-h" || argument == "--help") { print_help(); std::exit(0); }
        else if (is_option(argument)) throw std::runtime_error("Unknown option: " + argument);
        else throw std::runtime_error("Unexpected argument: " + argument);
    }
    return config;
}
