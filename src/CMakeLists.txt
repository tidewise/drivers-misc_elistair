rock_library(misc_elistair
    SOURCES Driver.cpp
    HEADERS Driver.hpp Status.hpp Command.hpp
    DEPS_PKGCONFIG iodrivers_base
)

rock_executable(misc_elistair_bin Main.cpp
    DEPS misc_elistair)

