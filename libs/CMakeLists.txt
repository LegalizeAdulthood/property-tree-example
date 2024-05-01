add_library(settings
    include/settings/settings.h
    settings.cpp
)
target_include_directories(settings PUBLIC include)
target_folder(settings "Libraries")
