#
# This program is an image recognition library written with OpenCV.
# Copyright (C) 2016-2018 Andreas Sekulski
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

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

# Add generic source files
set(SOURCE_UTIL ../util.cpp ../util.h)

# Setup CPUFeatureMatchingVideo
set(SOURCE1 CPUFeatureMatchingVideo.cpp ${SOURCE_UTIL})
add_executable(CPUFeatureMatchingVideo ${SOURCE1})
target_link_libraries(CPUFeatureMatchingVideo Companion)

# Setup CPUFeatureMatchingRealtime
set(SOURCE2 CPUFeatureMatchingRealtime.cpp ${SOURCE_UTIL})
add_executable(CPUFeatureMatchingRealtime ${SOURCE2})
target_link_libraries(CPUFeatureMatchingRealtime Companion)

# Setup CPUFeatureMatchingImageStream
set(SOURCE3 CPUFeatureMatchingImageStream.cpp ${SOURCE_UTIL})
add_executable(CPUFeatureMatchingImageStream ${SOURCE3})
target_link_libraries(CPUFeatureMatchingImageStream Companion)

# Setup CudaFeatureMatchingVideo
if(Companion_USE_CUDA)
    set(SOURCE4 CudaFeatureMatchingVideo.cpp ${SOURCE_UTIL})
    set(CUDA_TARGET CudaFeatureMatchingVideo)
    add_executable(CudaFeatureMatchingVideo ${SOURCE4})
    target_link_libraries(CudaFeatureMatchingVideo Companion)
endif()

# Combine all sources and targets
set(ALL_SOURCES ${SOURCE1} ${SOURCE2} ${SOURCE3} ${SOURCE4} ${SOURCE_UTIL})
set(ALL_TARGETS CPUFeatureMatchingVideo CPUFeatureMatchingRealtime CPUFeatureMatchingImageStream ${CUDA_TARGET})

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
