#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <variant>
#include <vector>

namespace settings
{

using Value = std::variant<int, double, std::string>;
struct Section
{
    std::string name;
    std::map<std::string, Value> values;
};
using Settings = std::vector<Section>;

Settings load(const std::filesystem::path &path);
void save(const Settings &settings, const std::filesystem::path &path);

} // namespace settings
