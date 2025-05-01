// AppRunner.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <vector>
#include <string>
#include "RegistryUtils.h"
#include "ConfigManager.h"

int main()
{
    const std::string configFile = "apps.json";
    auto apps = LoadConfig(configFile);

    int choice;
    while (true) {
        std::cout << "\n--- Startup App Manager ---\n";
        std::cout << "1. List Apps\n2. Add App\n3. Toggle Startup\n4. Save & Apply\n5. Exit\nChoice: ";
        std::cin >> choice;

        if (choice == 1) {
            for (size_t i = 0; i < apps.size(); ++i) {
                std::cout << i << ": " << apps[i].name
                    << " [" << (apps[i].enabled ? "Enabled" : "Disabled") << "]\n";
            }
        }
        else if (choice == 2) {
            AppEntry newApp;
            std::cout << "App name: ";
            std::cin.ignore();
            std::getline(std::cin, newApp.name);
            std::cout << "App path (.exe): ";
            std::getline(std::cin, newApp.path);
            newApp.enabled = true;
            apps.push_back(newApp);
        }
        else if (choice == 3) {
            int idx;
            std::cout << "App index to toggle: ";
            std::cin >> idx;
            if (idx >= 0 && idx < (int)apps.size()) {
                apps[idx].enabled = !apps[idx].enabled;
                std::cout << "Toggled " << apps[idx].name << " to "
                    << (apps[idx].enabled ? "Enabled" : "Disabled") << "\n";
            }
        }
        else if (choice == 4) {
            for (const auto& app : apps) {
                if (app.enabled) AddToStartup(app.name, app.path);
                else RemoveFromStartup(app.name);
            }
            SaveConfig(configFile, apps);
            std::cout << "Config saved and registry updated.\n";
        }
        else if (choice == 5) {
            break;
        }
    }

    return 0;
}