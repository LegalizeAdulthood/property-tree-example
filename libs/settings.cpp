#include "settings/settings.h"

#include <stdexcept>

namespace settings
{
Settings load(const std::filesystem::path &filename)
{
    throw std::runtime_error("Not implemented: load settings from file");
}

void save(const Settings &settings, const std::filesystem::path &filename)
{
    throw std::runtime_error("Not implemented: save settings to file");
}

} // namespace settings
