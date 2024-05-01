include(GoogleTest)

find_package(GTest CONFIG REQUIRED)

add_executable(test-settings test-settings.cpp)
target_link_libraries(test-settings PUBLIC GTest::gtest_main settings)
target_folder(test-settings "Tests")

gtest_discover_tests(test-settings)
