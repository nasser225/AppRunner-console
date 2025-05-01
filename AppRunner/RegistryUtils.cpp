#include "RegistryUtils.h"
#include <Windows.h>

bool AddToStartup(const std::string& appName, const std::string& exePath)
{
    HKEY hKey;
    if (RegOpenKeyExA(HKEY_CURRENT_USER,
        "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey) != ERROR_SUCCESS)
        return false;

    LONG result = RegSetValueExA(hKey, appName.c_str(), 0, REG_SZ,
        reinterpret_cast<const BYTE*>(exePath.c_str()), exePath.size() + 1);
    RegCloseKey(hKey);
    return result == ERROR_SUCCESS;
}

bool RemoveFromStartup(const std::string& appName)
{
    HKEY hKey;
    if (RegOpenKeyExA(HKEY_CURRENT_USER,
        "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey) != ERROR_SUCCESS)
        return false;

    LONG result = RegDeleteValueA(hKey, appName.c_str());
    RegCloseKey(hKey);
    return result == ERROR_SUCCESS;
}
