#include <settings/custom.h>

#include "test-settings.h"

#include <filesystem>

#include <gtest/gtest.h>

TEST(TestSettingsCustomIni, loadFirstSection)
{
    const std::filesystem::path ini_path{test::settings::INI_PATH};

    const settings::custom::Settings settings{settings::custom::ini::load(ini_path)};

    EXPECT_EQ(test::settings::APP_NAME, settings.general.application_name);
    EXPECT_EQ(test::settings::APP_VERSION, settings.general.version);
    EXPECT_EQ(test::settings::DEBUG_MODE, settings.general.debug);
}

TEST(TestSettingsCustomIni, loadAllSections)
{
    const std::filesystem::path ini_path{test::settings::INI_PATH};

    const settings::custom::Settings settings{settings::custom::ini::load(ini_path)};

    EXPECT_EQ(test::settings::DISPLAY_WIDTH, settings.display.width);
    EXPECT_EQ(test::settings::DISPLAY_HEIGHT, settings.display.height);
    EXPECT_NEAR(test::settings::REFRESH_RATE, settings.display.refresh_rate, 1e-6);
    EXPECT_EQ(test::settings::USER_NAME, settings.user.name);
    EXPECT_EQ(test::settings::USER_EMAIL, settings.user.email);
    EXPECT_EQ(test::settings::USER_LAST_LOGIN, settings.user.last_login);
    EXPECT_EQ(test::settings::CACHE_SIZE, settings.advanced.cache_size);
    EXPECT_EQ(test::settings::THREADS_COUNT, settings.advanced.threads);
    EXPECT_EQ(test::settings::PERFORMANCE_MODE, settings.advanced.performance_mode);
}

TEST(TestSettingsCustomIni, save)
{
    std::filesystem::path ini_path{test::settings::INI_PATH};
    ini_path.replace_filename("custom.ini");
    std::filesystem::remove(ini_path);
    // clang-format off
    const settings::custom::Settings testSettings{
        {
            test::settings::APP_NAME,
            test::settings::APP_VERSION,
            test::settings::DEBUG_MODE,
        },
        {
            test::settings::DISPLAY_WIDTH,
            test::settings::DISPLAY_HEIGHT,
            test::settings::REFRESH_RATE,
        },
        {
            "TestUser",
            "test@example.com",
            "2023-01-01",
        },
        {
            test::settings::CACHE_SIZE,
            test::settings::THREADS_COUNT,
            test::settings::PERFORMANCE_MODE,
        },
    };
    // clang-format on

    settings::custom::ini::save(testSettings, ini_path);

    EXPECT_TRUE(std::filesystem::exists(ini_path)) << ini_path << " does not exist";
}
