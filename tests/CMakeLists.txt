include(GoogleTest)

find_package(GTest CONFIG REQUIRED)

# Define configuration variables to be used in both INI file and tests
set(APP_NAME "PropertyTreeExample")
set(APP_VERSION "1.0")
set(DEBUG_MODE 0)
set(DISPLAY_WIDTH 1920)
set(DISPLAY_HEIGHT 1080)
set(REFRESH_RATE 60.0)
set(USER_NAME "TestUser")
set(USER_EMAIL "test@example.com")
set(USER_LAST_LOGIN "2023-01-01")
set(CACHE_SIZE 1024)
set(THREADS_COUNT 8)
set(PERFORMANCE_MODE "high")
set(TEST_DATA_DIR "${CMAKE_CURRENT_BINARY_DIR}/data")
set(INI_PATH "${TEST_DATA_DIR}/test-settings.ini")
set(JSON_PATH "${TEST_DATA_DIR}/test-settings.json")

# Generate the test settings header file
configure_file("test-settings.h.in" "include/test-settings.h" @ONLY)

# Generate the test INI file
configure_file("test-settings.ini.in" "data/test-settings.ini" @ONLY)
configure_file("test-settings.json.in" "data/test-settings.json" @ONLY)

add_executable("test-settings"
    "test-settings.h.in"
    "test-settings.ini.in"
    "test-settings.json.in"
    "${CMAKE_CURRENT_BINARY_DIR}/include/test-settings.h"
    "${CMAKE_CURRENT_BINARY_DIR}/data/test-settings.ini"
    "${CMAKE_CURRENT_BINARY_DIR}/data/test-settings.json"
    "test-generic-ini.cpp"
    "test-generic-json.cpp"
    "test-custom-ini.cpp"
    "test-custom-json.cpp"
)
source_group("CMake Templates" FILES
    "test-settings.h.in"
    "test-settings.ini.in"
    "test-settings.json.in"
)
source_group("Test Data" FILES
    "${CMAKE_CURRENT_BINARY_DIR}/data/test-settings.ini"
    "${CMAKE_CURRENT_BINARY_DIR}/data/test-settings.json"
)
target_link_libraries("test-settings" PUBLIC GTest::gtest_main settings)
target_include_directories("test-settings" PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/include")
target_folder("test-settings" "Tests")

gtest_discover_tests("test-settings")
