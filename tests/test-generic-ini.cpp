#include <settings/generic.h>

#include "test-settings.h"

#include <filesystem>

#include <gtest/gtest.h>

TEST(TestSettings, loadIniFirstSection)
{
    const std::filesystem::path ini_path{test::settings::INI_PATH};

    const settings::generic::Settings settings{settings::generic::ini::load(ini_path)};

    const settings::generic::Section &section = settings.at(0);
    EXPECT_EQ("General", section.name);
    EXPECT_EQ(std::get<std::string>(section.values.at("ApplicationName")), test::settings::APP_NAME);
    EXPECT_EQ(std::get<std::string>(section.values.at("Version")), test::settings::APP_VERSION);
    EXPECT_EQ(std::get<int>(section.values.at("Debug")), test::settings::DEBUG_MODE);
}

TEST(TestSettings, loadIniAllSections)
{
    const std::filesystem::path ini_path{test::settings::INI_PATH};

    const settings::generic::Settings settings{settings::generic::ini::load(ini_path)};

    EXPECT_EQ(4U, settings.size());
    EXPECT_EQ("General", settings.at(0).name);
    EXPECT_EQ("Display", settings.at(1).name);
    EXPECT_EQ("User", settings.at(2).name);
    EXPECT_EQ("Advanced", settings.at(3).name);
}

TEST(TestSettings, saveIni)
{
    std::filesystem::path ini_path{test::settings::TEST_DATA_DIR};
    ini_path /= "output.ini";
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
