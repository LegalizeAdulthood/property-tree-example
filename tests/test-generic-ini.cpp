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
    const settings::generic::Section &display{settings.at(1)};
    EXPECT_EQ("Display", display.name);
    EXPECT_EQ(test::settings::DISPLAY_WIDTH, std::get<int>(display.values.at("Width")));
    EXPECT_EQ(test::settings::DISPLAY_HEIGHT, std::get<int>(display.values.at("Height")));
    EXPECT_NEAR(test::settings::REFRESH_RATE, std::get<double>(display.values.at("RefreshRate")), 1e-6);
    const settings::generic::Section &user{settings.at(2)};
    EXPECT_EQ("User", user.name);
    EXPECT_EQ(test::settings::USER_NAME, std::get<std::string>(user.values.at("Name")));
    EXPECT_EQ(test::settings::USER_EMAIL, std::get<std::string>(user.values.at("Email")));
    EXPECT_EQ(test::settings::USER_LAST_LOGIN, std::get<std::string>(user.values.at("LastLogin")));
    const settings::generic::Section &advanced{settings.at(3)};
    EXPECT_EQ("Advanced", advanced.name);
    EXPECT_EQ(test::settings::CACHE_SIZE, std::get<int>(advanced.values.at("CacheSize")));
    EXPECT_EQ(test::settings::THREADS_COUNT, std::get<int>(advanced.values.at("Threads")));
    EXPECT_EQ(test::settings::PERFORMANCE_MODE, std::get<std::string>(advanced.values.at("PerformanceMode")));
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
