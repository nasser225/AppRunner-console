#pragma once

#include <string>
#include <vector>

struct AppEntry {
    std::string name;
    std::string path;
    bool enabled;
};

std::vector<AppEntry> LoadConfig(const std::string& filename);
void SaveConfig(const std::string& filename, const std::vector<AppEntry>& apps);

