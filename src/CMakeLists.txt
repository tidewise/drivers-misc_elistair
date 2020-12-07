rock_library(misc_elistair
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(misc_elistair_bin Main.cpp
    DEPS misc_elistair)

