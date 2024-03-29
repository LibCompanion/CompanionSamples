#
# This program is an usage example for Companion.
# Copyright (C) 2016-2018 Andreas Sekulski, Dimitri Kotlovsky
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

find_package(OpenCV REQUIRED COMPONENTS core highgui)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

# Add generic source files
set(SOURCE_UTIL ../util.cpp ../util.h)

# Setup CPUHashMatchingVideo
set(SOURCE1 CPUHashMatchingVideo.cpp ${SOURCE_UTIL})
add_executable(CPUHashMatchingVideo ${SOURCE1})
target_link_libraries(CPUHashMatchingVideo Companion ${OpenCV_LIBS})

# Combine all sources and targets
set(ALL_SOURCES ${SOURCE1} ${SOURCE_UTIL})
set(ALL_TARGETS CPUHashMatchingVideo)

# Add target properties
set_property(TARGET ${ALL_TARGETS} PROPERTY FOLDER "CompanionSamples")

# Add install instructions (also add debug postfix for differentiation)
set_property(TARGET ${ALL_TARGETS} PROPERTY DEBUG_POSTFIX "D")
install(TARGETS ${ALL_TARGETS} DESTINATION "${PROJECT_BINARY_DIR}/install/bin" OPTIONAL)

# Create MSVC filter
if(MSVC)
    foreach(source IN LISTS ALL_SOURCES)
        get_filename_component(source_path "${source}" PATH)
        string(REPLACE "/" "\\" source_path_msvc "${source_path}")
        source_group("${source_path_msvc}" FILES "${source}")
    endforeach()
endif()

# Ressource files
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)
