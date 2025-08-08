find_package(Boost REQUIRED COMPONENTS property_tree)
find_package(TcbSpan REQUIRED)

add_library(settings
    include/settings/generic.h
    generic.cpp
)
target_include_directories(settings PUBLIC include)
target_link_libraries(settings PRIVATE Boost::property_tree Tcb::Span)
target_folder(settings "Libraries")
