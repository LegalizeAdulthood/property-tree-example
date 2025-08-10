#pragma once

#include <filesystem>
#include <string>

namespace settings::custom
{

struct General
{
    std::string application_name;
    std::string version;
    int debug{};
};

struct Display
{
    int width{};
    int height{};
    double refresh_rate{};
};

struct User
{
    std::string name;
    std::string email;
    std::string last_login;
};

struct Advanced
{
    int cache_size{};
    int threads{};
    std::string performance_mode;
};

struct Settings
{
    General general;
    Display display;
    User user;
    Advanced advanced;
};

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

} // namespace settings::custom
