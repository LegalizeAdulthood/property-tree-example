#include "settings/settings.h"

#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <tcb/span.hpp>

#include <algorithm>
#include <stdexcept>
#include <string>

namespace settings
{

namespace
{

enum class ValueType
{
    INTEGER,
    FLOATING_POINT,
    TEXT
};

struct ValueDesc
{
    const char *name;
    ValueType type;
};

struct SectionDesc
{
    const char *name;
    tcb::span<const ValueDesc> values;
};

constexpr ValueDesc GENERAL_VALUES[]{
    {"ApplicationName", ValueType::TEXT}, //
    {"Version", ValueType::TEXT},         //
    {"Debug", ValueType::INTEGER},        //
};

constexpr SectionDesc GENERAL{"General", GENERAL_VALUES};

constexpr ValueDesc DISPLAY_VALUES[]{
    {"Width", ValueType::INTEGER},              //
    {"Height", ValueType::INTEGER},             //
    {"RefreshRate", ValueType::FLOATING_POINT}, //
};

constexpr SectionDesc DISPLAY{"Display", DISPLAY_VALUES};

constexpr ValueDesc USER_VALUES[]{
    {"Name", ValueType::TEXT},      //
    {"Email", ValueType::TEXT},     //
    {"LastLogin", ValueType::TEXT}, //
};

constexpr SectionDesc USER{"User", USER_VALUES};

constexpr ValueDesc ADVANCED_VALUES[]{
    {"CacheSize", ValueType::INTEGER},    //
    {"Threads", ValueType::INTEGER},      //
    {"PerformanceMode", ValueType::TEXT}, //
};

constexpr SectionDesc ADVANCED{"Advanced", ADVANCED_VALUES};

constexpr SectionDesc SECTIONS[]{ADVANCED, DISPLAY, GENERAL, USER};

constexpr tcb::span<const SectionDesc> SETTINGS{SECTIONS};

} // namespace

Settings load(const std::filesystem::path &path)
{
    Settings result;
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini(path.string(), pt);
    for (const auto &sec : pt)
    {
        Section section;
        section.name = sec.first;
        const SectionDesc &sec_desc{*std::find_if(
            SETTINGS.begin(), SETTINGS.end(), [&](const SectionDesc &desc) { return desc.name == section.name; })};
        for (const auto &item : sec.second)
        {
            const std::string &key = item.first;
            const std::string &text = item.second.get_value<std::string>();
            const ValueDesc &value_desc{*std::find_if(sec_desc.values.begin(), sec_desc.values.end(),
                [&](const ValueDesc &desc) { return desc.name == key; })};
            size_t pos;
            switch (value_desc.type)
            {
            case ValueType::INTEGER:
                if (const int value = std::stoi(text, &pos); pos == text.length())
                {
                    section.values[key] = value;
                }
                break;
            case ValueType::FLOATING_POINT:
                if (const double value = std::stod(text, &pos); pos == text.length())
                {
                    section.values[key] = value;
                }
                break;
            case ValueType::TEXT:
                section.values[key] = text;
                break;
            }
        }
        result.emplace_back(section);
    }

    return result;
}

void save(const Settings &settings, const std::filesystem::path &path)
{
    boost::property_tree::ptree pt;
    for (const Section &section : settings)
    {
        const SectionDesc &sec_desc{*std::find_if(
            SETTINGS.begin(), SETTINGS.end(), [&](const SectionDesc &desc) { return desc.name == section.name; })};
        boost::property_tree::ptree sec_tree;
        for (const auto &it : section.values)
        {
            const std::string &key{it.first};
            const Value &value{it.second};
            const ValueDesc &value_desc{*std::find_if(sec_desc.values.begin(), sec_desc.values.end(),
                [&](const ValueDesc &desc) { return desc.name == key; })};
            switch (value_desc.type)
            {
            case ValueType::INTEGER:
                sec_tree.put(key, std::get<int>(value));
                break;
            case ValueType::FLOATING_POINT:
                sec_tree.put(key, std::get<double>(value));
                break;
            case ValueType::TEXT:
                sec_tree.put(key, std::get<std::string>(value));
                break;
            }
        }
        pt.add_child(section.name, sec_tree);
    }
    boost::property_tree::ini_parser::write_ini(path.string(), pt);
}

} // namespace settings
