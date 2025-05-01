#pragma once
#include <string>

bool AddToStartup(const std::string& appName, const std::string& exePath);

bool RemoveFromStartup(const std::string& appName);
