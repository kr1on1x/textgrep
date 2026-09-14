#include "search.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <system_error>

namespace {
bool is_hidden(const std::filesystem::path& path) { auto name = path.filename().string(); return !name.empty() && name.front() == '.'; }
bool has_extension(const std::filesystem::path& path, const std::optional<std::string>& ext) {
    if (!ext) return true;
    auto value = path.extension().string();
    return !value.empty() && value.substr(1) == *ext;
}
bool is_binary(const std::filesystem::path& path) {
    std::ifstream file(path, std::ios::binary); if (!file) return false;
    char buffer[4096]; file.read(buffer, sizeof(buffer));
    for (std::streamsize i = 0; i < file.gcount(); ++i) if (buffer[i] == '\0') return true;
    return false;
}
std::string lower(std::string text) { std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c){ return static_cast<char>(std::tolower(c)); }); return text; }
bool contains(const std::string& line, const std::string& query, bool ignore_case) { return ignore_case ? lower(line).find(lower(query)) != std::string::npos : line.find(query) != std::string::npos; }
void search_file(const std::filesystem::path& path, const Config& config, SearchStats& stats, std::vector<SearchResult>& results) {
    ++stats.files_scanned;
    if (is_binary(path)) return;
    std::ifstream file(path);
    if (!file) { ++stats.errors; std::cerr << "Warning: cannot read " << path << '\n'; return; }
    std::string line; std::size_t number = 0; bool matched = false;
    while (std::getline(file, line)) { ++number; if (!contains(line, config.query, config.ignore_case)) continue; results.push_back({path, number, line}); ++stats.matches; matched = true; }
    if (matched) ++stats.files_matched;
}
void search_directory(const std::filesystem::path& dir, const Config& config, SearchStats& stats, std::vector<SearchResult>& results) {
    std::error_code error;
    std::filesystem::directory_iterator it(dir, std::filesystem::directory_options::skip_permission_denied, error);
    if (error) { ++stats.errors; std::cerr << "Warning: cannot access " << dir << '\n'; return; }
    for (const auto& entry : it) {
        auto path = entry.path();
        if (!config.include_hidden && is_hidden(path)) continue;
        std::error_code status_error; auto status = entry.symlink_status(status_error);
        if (status_error) { ++stats.errors; continue; }
        if (std::filesystem::is_directory(status)) { search_directory(path, config, stats, results); continue; }
        if (!std::filesystem::is_regular_file(status) || !has_extension(path, config.extension)) continue;
        search_file(path, config, stats, results);
    }
}
}

std::vector<SearchResult> search(const Config& config, SearchStats& stats) {
    std::vector<SearchResult> results; std::error_code error;
    if (!std::filesystem::exists(config.path, error)) { ++stats.errors; std::cerr << "Error: path does not exist: " << config.path << '\n'; return results; }
    if (std::filesystem::is_regular_file(config.path, error)) { if (has_extension(config.path, config.extension)) search_file(config.path, config, stats, results); return results; }
    if (!std::filesystem::is_directory(config.path, error)) { ++stats.errors; std::cerr << "Error: path is not a regular file or directory: " << config.path << '\n'; return results; }
    search_directory(config.path, config, stats, results);
    return results;
}
