#include <settings/custom.h>
#include <settings/generic.h>

#include <boost/program_options.hpp>

#include <algorithm>
#include <iostream>
#include <stdexcept>

namespace po = boost::program_options;

namespace
{

settings::generic::Section &get_section( settings::generic::Settings &settings, const std::string &name )
{
    const auto it{std::find_if(settings.begin(), settings.end(),
        [&name](settings::generic::Section &section) { return section.name == name; })};
    if (it != settings.end())
    {
        return *it;
    }
    throw std::runtime_error("Section not found: " + name);
}

void generic_update(settings::generic::Settings &settings ,const po::variables_map &vm)
{
    if (vm.count("application-name"))
    {
        get_section(settings, "General").values["ApplicationName"] = vm["application-name"].as<std::string>();
    }
    if (vm.count("application-version"))
    {
        get_section(settings, "General").values["Version"] = vm["application-version"].as<std::string>();
    }
    if (vm.count("application-debug"))
    {
        get_section(settings, "General").values["Debug"] = vm["application-debug"].as<int>();
    }
}

int generic_ini(const std::string & file, const po::variables_map & vm)
{
    settings::generic::Settings settings = settings::generic::ini::load(file);
    generic_update(settings, vm);
    settings::generic::ini::save(settings, file);
    return 0;
}

int generic_json(const std::string &file, const po::variables_map &vm)
{
    settings::generic::Settings settings = settings::generic::json::load(file);
    generic_update(settings, vm);
    settings::generic::json::save(settings, file);
    return 0;
}

int generic(bool json, const std::string file, const po::variables_map &vm)
{
    return json ? generic_json(file, vm) : generic_ini(file, vm);
}

void custom_update(settings::custom::Settings &settings ,const po::variables_map &vm)
{
    if (vm.count("application-name"))
    {
        settings.general.application_name = vm["application-name"].as<std::string>();
    }
    if (vm.count("application-version"))
    {
        settings.general.version = vm["application-version"].as<std::string>();
    }
    if (vm.count("application-debug"))
    {
        settings.general.debug = vm["application-debug"].as<int>();
    }
}

int custom_ini(const std::string &file, const po::variables_map &vm)
{
    settings::custom::Settings settings = settings::custom::ini::load(file);
    custom_update(settings, vm);
    settings::custom::ini::save(settings, file);
    return 0;
}

int custom_json(const std::string &file, const po::variables_map &vm)
{
    settings::custom::Settings settings = settings::custom::json::load(file);
    custom_update(settings, vm);
    settings::custom::json::save(settings, file);
    return 0;
}

int custom(bool json, const std::string &file, const po::variables_map &vm)
{
    return json ? custom_json(file, vm) : custom_ini(file, vm);
}
} // namespace

int main(int argc, char *argv[])
{
    po::options_description desc("Allowed options");
    desc.add_options()                                                                  //
        ("help,h", "Show help message")                                                 //
        ("generic,g", "Use generic settings")                                           //
        ("custom,c", "Use custom settings")                                             //
        ("ini,i", po::value<std::string>(), "Path to INI settings file")                //
        ("json,j", po::value<std::string>(), "Path to JSON settings file")              //
        ("application-name", po::value<std::string>(), "Name of the application")       //
        ("application-version", po::value<std::string>(), "Version of the application") //
        ("application-debug", po::value<int>(), "Debug level")                          //
        ("display-width", po::value<int>(), "Width of the display")                     //
        ("display-height", po::value<int>(), "Height of the display")                   //
        ("display-refresh-rate", po::value<double>(), "Refresh rate")                   //
        ("user-name", po::value<std::string>(), "Username")                             //
        ("user-email", po::value<std::string>(), "User email")                          //
        ("user-last-login", po::value<std::string>(), "Last login time")                //
        ("advanced-cache-size", po::value<int>(), "Cache size")                         //
        ("advanced-threads", po::value<int>(), "Number of threads")                     //
        ("advanced-performance-mode", po::value<std::string>(), "Performance mode");    //
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    if (vm.count("help") || (vm.count("ini") && vm.count("json")))
    {
        std::cout << desc << '\n';
        return 0;
    }
    const bool json{vm.count("json") != 0};
    const std::string file{json ? vm["json"].as<std::string>() : vm["ini"].as<std::string>()};
    return vm.count("generic") ? generic(json, file, vm) : custom(json, file, vm);
}
