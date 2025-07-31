#include <settings/settings.h>

#include "test-settings.h"

#include <filesystem>

#include <gtest/gtest.h>

TEST(TestSettings, load)
{
    const std::filesystem::path ini_path{test::settings::INI_PATH};

    const settings::Settings settings = settings::load(ini_path);

    // Test values using constants from our generated header
    EXPECT_EQ(std::get<std::string>(settings.at("ApplicationName")), test::settings::APP_NAME);
    EXPECT_EQ(std::get<int>(settings.at("Width")), test::settings::DISPLAY_WIDTH);
    EXPECT_EQ(std::get<double>(settings.at("RefreshRate")), test::settings::REFRESH_RATE);
}

TEST(TestSettings, save)
{
    std::filesystem::path ini_path{test::settings::TEST_DATA_DIR};
    ini_path /= "output.ini";

    const settings::Settings testSettings = {
        {"ApplicationName", test::settings::APP_NAME}, //
        {"Version", test::settings::APP_VERSION},      //
        {"Width", test::settings::DISPLAY_WIDTH},      //
        {"Height", test::settings::DISPLAY_HEIGHT},    //
        {"RefreshRate", test::settings::REFRESH_RATE}  //
    };

    settings::save(testSettings, ini_path);

    EXPECT_TRUE(std::filesystem::exists(ini_path));
}
