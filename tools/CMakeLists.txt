find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(property-tree main.cpp)
target_link_libraries(property-tree PUBLIC Boost::program_options settings)
target_folder(property-tree "Tools")
