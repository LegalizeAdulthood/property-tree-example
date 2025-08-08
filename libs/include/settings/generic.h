#pragma once

#include <filesystem>
#include <map>
#include <string>
#include <variant>
#include <vector>

namespace settings::generic
{

using Value = std::variant<int, double, std::string>;
struct Section
{
    std::string name;
    std::map<std::string, Value> values;
};
using Settings = std::vector<Section>;

namespace ini
{

Settings load(const std::filesystem::path &path);
void save(const Settings &settings, const std::filesystem::path &path);

} // namespace ini

namespace json
{

Settings load(const std::filesystem::path &path);
void save(const Settings &settings, const std::filesystem::path &path);

} // namespace json

} // namespace settings
