#include <settings/custom.h>

#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <stdexcept>

namespace settings::custom
{

namespace
{

Settings ptree_to_settings(const boost::property_tree::ptree &pt)
{
    Settings result{};
    for (const auto &section : pt)
    {
        if (section.first == "General")
        {
            for (const auto &item : section.second)
            {
                if (item.first == "ApplicationName")
                {
                    result.general.application_name = item.second.get_value<std::string>();
                }
                else if (item.first == "Version")
                {
                    result.general.version = item.second.get_value<std::string>();
                }
                else if (item.first == "Debug")
                {
                    result.general.debug = item.second.get_value<int>();
                }
            }
        }
        else if (section.first == "Display")
        {
            for (const auto &item : section.second)
            {
                if (item.first == "Width")
                {
                    result.display.width = item.second.get_value<int>();
                }
                else if (item.first == "Height")
                {
                    result.display.height = item.second.get_value<int>();
                }
                else if (item.first == "RefreshRate")
                {
                    result.display.refresh_rate = item.second.get_value<double>();
                }
            }
        }
        else if (section.first == "User")
        {
            for (const auto &item : section.second)
            {
                if (item.first == "Name")
                {
                    result.user.name = item.second.get_value<std::string>();
                }
                else if (item.first == "Email")
                {
                    result.user.email = item.second.get_value<std::string>();
                }
                else if (item.first == "LastLogin")
                {
                    result.user.last_login = item.second.get_value<std::string>();
                }
            }
        }
        else if (section.first == "Advanced")
        {
            for (const auto &item : section.second)
            {
                if (item.first == "CacheSize")
                {
                    result.advanced.cache_size = item.second.get_value<int>();
                }
                else if (item.first == "Threads")
                {
                    result.advanced.threads = item.second.get_value<int>();
                }
                else if (item.first == "PerformanceMode")
                {
                    result.advanced.performance_mode = item.second.get_value<std::string>();
                }
            }
        }
    }
    return result;
}

boost::property_tree::ptree settings_to_ptree(const Settings &settings)
{
    boost::property_tree::ptree pt;

    pt.put("General.ApplicationName", settings.general.application_name);
    pt.put("General.Version", settings.general.version);
    pt.put("General.Debug", settings.general.debug);

    pt.put("Display.Width", settings.display.width);
    pt.put("Display.Height", settings.display.height);
    pt.put("Display.RefreshRate", settings.display.refresh_rate);

    pt.put("User.Name", settings.user.name);
    pt.put("User.Email", settings.user.email);
    pt.put("User.LastLogin", settings.user.last_login);

    pt.put("Advanced.CacheSize", settings.advanced.cache_size);
    pt.put("Advanced.Threads", settings.advanced.threads);
    pt.put("Advanced.PerformanceMode", settings.advanced.performance_mode);

    return pt;
}

} // namespace

namespace ini
{

Settings load(const std::filesystem::path &path)
{
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini(path.string(), pt);
    return ptree_to_settings(pt);
}

void save(const Settings &settings, const std::filesystem::path &path)
{
    boost::property_tree::ini_parser::write_ini(path.string(), settings_to_ptree(settings));
}

} // namespace ini

namespace json
{
Settings load(const std::filesystem::path &path)
{
    boost::property_tree::ptree pt;
    boost::property_tree::json_parser::read_json(path.string(), pt);
    return ptree_to_settings(pt);
}

void save(const Settings &settings, const std::filesystem::path &path)
{
    boost::property_tree::json_parser::write_json(path.string(), settings_to_ptree(settings));
}

} // namespace json

} // namespace settings::custom
