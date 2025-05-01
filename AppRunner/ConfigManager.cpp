#include "ConfigManager.h"
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

std::vector<AppEntry> LoadConfig(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<AppEntry> apps;

    if (file.is_open()) {
        json j;
        file >> j;
        for (const auto& item : j) {
            apps.push_back({ item["name"], item["path"], item["enabled"] });
        }
    }
    return apps;
}

void SaveConfig(const std::string& filename, const std::vector<AppEntry>& apps) {
    json j;
    for (const auto& app : apps) {
        j.push_back({ {"name", app.name}, {"path", app.path}, {"enabled", app.enabled} });
    }
    std::ofstream file(filename);
    file << j.dump(4);
}
