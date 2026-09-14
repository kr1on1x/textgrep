#include "utils.hpp"
#include <iostream>

void print_results(const std::vector<SearchResult>& results, bool show_line_numbers) {
    for (const auto& result : results) {
        std::cout << result.file;
        if (show_line_numbers) std::cout << ':' << result.line_number;
        std::cout << ": " << result.line << '\n';
    }
}

void print_statistics(const SearchStats& stats) {
    std::cout << '\n' << stats.matches << " matches in " << stats.files_matched << " files\n"
              << "Files scanned: " << stats.files_scanned << '\n'
              << "Errors: " << stats.errors << '\n';
}
