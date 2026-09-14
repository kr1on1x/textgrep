#include "config.hpp"
#include "search.hpp"
#include "utils.hpp"
#include <exception>
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        const Config config = parse_arguments(argc, argv);
        SearchStats stats;
        const auto results = search(config, stats);
        print_results(results, config.line_number);
        print_statistics(stats);
        return stats.errors == 0 ? 0 : 1;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
