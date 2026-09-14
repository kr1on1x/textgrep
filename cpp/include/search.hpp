#pragma once
#include "config.hpp"
#include <cstddef>
#include <filesystem>
#include <string>
#include <vector>

struct SearchResult { std::filesystem::path file; std::size_t line_number; std::string line; };
struct SearchStats { std::size_t files_scanned = 0; std::size_t files_matched = 0; std::size_t matches = 0; std::size_t errors = 0; };
std::vector<SearchResult> search(const Config& config, SearchStats& stats);
