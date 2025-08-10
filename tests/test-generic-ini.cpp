#include <settings/generic.h>

#include "test-settings.h"

#include <filesystem>

#include <gtest/gtest.h>

TEST(TestSettingsGenericIni, loadFirstSection)
{
    const std::filesystem::path ini_path{test::settings::INI_PATH};

    const settings::generic::Settings settings{settings::generic::ini::load(ini_path)};

    const settings::generic::Section &section = settings.at(0);
    EXPECT_EQ("General", section.name);
    EXPECT_EQ(test::settings::APP_NAME, std::get<std::string>(section.values.at("ApplicationName")));
    EXPECT_EQ(test::settings::APP_VERSION, std::get<std::string>(section.values.at("Version")));
    EXPECT_EQ(test::settings::DEBUG_MODE, std::get<int>(section.values.at("Debug")));
}

TEST(TestSettingsGenericIni, loadAllSections)
{
    const std::filesystem::path ini_path{test::settings::INI_PATH};

    const settings::generic::Settings settings{settings::generic::ini::load(ini_path)};

    EXPECT_EQ(4U, settings.size());
    const settings::generic::Section &general{settings.at(0)};
    EXPECT_EQ("General", general.name);
    EXPECT_EQ("Display", settings.at(1).name);
    EXPECT_EQ("User", settings.at(2).name);
    EXPECT_EQ("Advanced", settings.at(3).name);
}

TEST(TestSettingsGenericIni, save)
{
    std::filesystem::path ini_path{test::settings::INI_PATH};
    ini_path.replace_filename("generic.ini");
    std::filesystem::remove(ini_path);
    // clang-format off
    const settings::generic::Settings testSettings{
        {
            "General",
            {
                {"ApplicationName", test::settings::APP_NAME},
                {"Version", test::settings::APP_VERSION},
                {"Debug", test::settings::DEBUG_MODE},
            }
        },
        {
            "Display",
            {
                {"Width", test::settings::DISPLAY_WIDTH},
                {"Height", test::settings::DISPLAY_HEIGHT},
                {"RefreshRate", test::settings::REFRESH_RATE},
            },
        },
        {
            "User",
            {
                {"Name", "TestUser"},
                {"Email", "test@example.com"},
                {"LastLogin", "2023-01-01"},
            }
        },
        {
            "Advanced",
            {
                {"CacheSize", test::settings::CACHE_SIZE},
                {"Threads", test::settings::THREADS_COUNT},
                {"PerformanceMode", test::settings::PERFORMANCE_MODE},
            }
        },
    };
    // clang-format on

    settings::generic::ini::save(testSettings, ini_path);

    EXPECT_TRUE(std::filesystem::exists(ini_path)) << ini_path << " does not exist";
}
