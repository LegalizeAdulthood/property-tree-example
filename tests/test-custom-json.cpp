#include <settings/custom.h>

#include "test-settings.h"

#include <filesystem>

#include <gtest/gtest.h>

TEST(TestSettingsCustomJson, loadFirstSection)
{
    const std::filesystem::path json_path{test::settings::JSON_PATH};

    const settings::custom::Settings settings{settings::custom::json::load(json_path)};

    EXPECT_EQ(test::settings::APP_NAME, settings.general.application_name);
    EXPECT_EQ(test::settings::APP_VERSION, settings.general.version);
    EXPECT_EQ(test::settings::DEBUG_MODE, settings.general.debug);
}

TEST(TestSettingsCustomJson, loadAllSections)
{
    const std::filesystem::path json_path{test::settings::JSON_PATH};

    const settings::custom::Settings settings{settings::custom::json::load(json_path)};

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

TEST(TestSettingsCustomJson, save)
{
    std::filesystem::path json_path{test::settings::INI_PATH};
    json_path.replace_filename("custom.json");
    std::filesystem::remove(json_path);
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
            test::settings::USER_NAME,
            test::settings::USER_EMAIL,
            test::settings::USER_LAST_LOGIN,
        },
        {
            test::settings::CACHE_SIZE,
            test::settings::THREADS_COUNT,
            test::settings::PERFORMANCE_MODE,
        },
    };
    // clang-format on

    settings::custom::json::save(testSettings, json_path);

    EXPECT_TRUE(std::filesystem::exists(json_path)) << json_path << " does not exist";
}
