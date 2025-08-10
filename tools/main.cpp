#include <settings/custom.h>
#include <settings/generic.h>

#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

namespace
{

int generic(const po::variables_map &vm)
{
    settings::generic::Settings settings = vm.count("json")
        ? settings::generic::json::load(vm["json"].as<std::string>())
        : settings::generic::ini::load(vm["ini"].as<std::string>());
    return 0;
}

int custom(const po::variables_map &vm)
{
    settings::custom::Settings settings = vm.count("json")
        ? settings::custom::json::load(vm["json"].as<std::string>())
        : settings::custom::ini::load(vm["ini"].as<std::string>());
    return 0;
}

} // namespace

int main(int argc, char *argv[])
{
    po::options_description desc("Allowed options");
    desc.add_options()                                                     //
        ("help,h", "Show help message")                                    //
        ("generic,g", "Use generic settings")                              //
        ("custom,c", "Use custom settings")                                //
        ("ini,i", po::value<std::string>(), "Path to INI settings file")   //
        ("json,j", po::value<std::string>(), "Path to JSON settings file") //
        ;
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    if (vm.count("help") || (vm.count("ini") && vm.count("json")))
    {
        std::cout << desc << '\n';
        return 0;
    }
    return vm.count("generic") ? generic(vm) : custom(vm);
}
