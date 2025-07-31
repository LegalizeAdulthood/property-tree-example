#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <variant>

namespace settings
{

using Value = std::variant<int, double, std::string>;

using Settings = std::map<std::string, Value>;

Settings load(const std::filesystem::path &filename);
void save(const Settings &settings, const std::filesystem::path &filename);

} // namespace settings
