# Generated by CMake

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.8)
   message(FATAL_ERROR "CMake >= 2.8.0 required")
endif()
if(CMAKE_VERSION VERSION_LESS "2.8.3")
   message(FATAL_ERROR "CMake >= 2.8.3 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 2.8.3...3.22)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

if(CMAKE_VERSION VERSION_LESS 3.0.0)
  message(FATAL_ERROR "This file relies on consumers using CMake 3.0.0 or greater.")
endif()

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_cmake_targets_defined "")
set(_cmake_targets_not_defined "")
set(_cmake_expected_targets "")
foreach(_cmake_expected_target IN ITEMS SFML::System SFML::Window X11 OpenGL UDev SFML::Network SFML::Graphics Freetype OpenAL VORBIS FLAC SFML::Audio)
  list(APPEND _cmake_expected_targets "${_cmake_expected_target}")
  if(TARGET "${_cmake_expected_target}")
    list(APPEND _cmake_targets_defined "${_cmake_expected_target}")
  else()
    list(APPEND _cmake_targets_not_defined "${_cmake_expected_target}")
  endif()
endforeach()
unset(_cmake_expected_target)
if(_cmake_targets_defined STREQUAL _cmake_expected_targets)
  unset(_cmake_targets_defined)
  unset(_cmake_targets_not_defined)
  unset(_cmake_expected_targets)
  unset(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT _cmake_targets_defined STREQUAL "")
  string(REPLACE ";" ", " _cmake_targets_defined_text "${_cmake_targets_defined}")
  string(REPLACE ";" ", " _cmake_targets_not_defined_text "${_cmake_targets_not_defined}")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_cmake_targets_defined_text}\nTargets not yet defined: ${_cmake_targets_not_defined_text}\n")
endif()
unset(_cmake_targets_defined)
unset(_cmake_targets_not_defined)
unset(_cmake_expected_targets)


# Create imported target SFML::System
add_library(SFML::System SHARED IMPORTED)

set_target_properties(SFML::System PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_std_17"
  INTERFACE_INCLUDE_DIRECTORIES "/home/Edouard/TEK3/C++/B-CPP-500-PAR-5-1-rtype-pierre.tran/buid/_deps/sfml-src/include"
)

# Create imported target SFML::Window
add_library(SFML::Window SHARED IMPORTED)

set_target_properties(SFML::Window PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_std_17"
  INTERFACE_INCLUDE_DIRECTORIES "/home/Edouard/TEK3/C++/B-CPP-500-PAR-5-1-rtype-pierre.tran/buid/_deps/sfml-src/include"
  INTERFACE_LINK_LIBRARIES "SFML::System"
)

# Create imported target X11
add_library(X11 INTERFACE IMPORTED)

set_target_properties(X11 PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
  INTERFACE_LINK_LIBRARIES "/usr/lib64/libX11.so;/usr/lib64/libXrandr.so;/usr/lib64/libXcursor.so"
)

# Create imported target OpenGL
add_library(OpenGL INTERFACE IMPORTED)

set_target_properties(OpenGL PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
  INTERFACE_LINK_LIBRARIES "/usr/lib64/libGL.so"
)

# Create imported target UDev
add_library(UDev INTERFACE IMPORTED)

set_target_properties(UDev PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
  INTERFACE_LINK_LIBRARIES "/usr/lib64/libudev.so"
)

# Create imported target SFML::Network
add_library(SFML::Network SHARED IMPORTED)

set_target_properties(SFML::Network PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_std_17"
  INTERFACE_INCLUDE_DIRECTORIES "/home/Edouard/TEK3/C++/B-CPP-500-PAR-5-1-rtype-pierre.tran/buid/_deps/sfml-src/include"
  INTERFACE_LINK_LIBRARIES "SFML::System"
)

# Create imported target SFML::Graphics
add_library(SFML::Graphics SHARED IMPORTED)

set_target_properties(SFML::Graphics PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_std_17"
  INTERFACE_INCLUDE_DIRECTORIES "/home/Edouard/TEK3/C++/B-CPP-500-PAR-5-1-rtype-pierre.tran/buid/_deps/sfml-src/include"
  INTERFACE_LINK_LIBRARIES "SFML::Window"
)

# Create imported target Freetype
add_library(Freetype INTERFACE IMPORTED)

set_target_properties(Freetype PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "/usr/include/freetype2"
  INTERFACE_LINK_LIBRARIES "/usr/lib64/libfreetype.so"
)

# Create imported target OpenAL
add_library(OpenAL INTERFACE IMPORTED)

set_target_properties(OpenAL PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "/usr/include/AL"
  INTERFACE_LINK_LIBRARIES "/usr/lib64/libopenal.so"
)

# Create imported target VORBIS
add_library(VORBIS INTERFACE IMPORTED)

set_target_properties(VORBIS PROPERTIES
  INTERFACE_COMPILE_DEFINITIONS "OV_EXCLUDE_STATIC_CALLBACKS"
  INTERFACE_INCLUDE_DIRECTORIES "/usr/include;/usr/include"
  INTERFACE_LINK_LIBRARIES "/usr/lib64/libvorbisenc.so;/usr/lib64/libvorbisfile.so;/usr/lib64/libvorbis.so;/usr/lib64/libogg.so"
)

# Create imported target FLAC
add_library(FLAC INTERFACE IMPORTED)

set_target_properties(FLAC PROPERTIES
  INTERFACE_COMPILE_DEFINITIONS "FLAC__NO_DLL"
  INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
  INTERFACE_LINK_LIBRARIES "/usr/lib64/libFLAC.so"
)

# Create imported target SFML::Audio
add_library(SFML::Audio SHARED IMPORTED)

set_target_properties(SFML::Audio PROPERTIES
  INTERFACE_COMPILE_FEATURES "cxx_std_17"
  INTERFACE_INCLUDE_DIRECTORIES "/home/Edouard/TEK3/C++/B-CPP-500-PAR-5-1-rtype-pierre.tran/buid/_deps/sfml-src/include"
  INTERFACE_LINK_LIBRARIES "SFML::System"
)

# Import target "SFML::System" for configuration "Release"
set_property(TARGET SFML::System APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SFML::System PROPERTIES
  IMPORTED_LOCATION_RELEASE "/home/Edouard/TEK3/C++/B-CPP-500-PAR-5-1-rtype-pierre.tran/buid/_deps/sfml-build/lib/libsfml-system.so.3.0.0"
  IMPORTED_SONAME_RELEASE "libsfml-system.so.3.0"
  )

# Import target "SFML::Window" for configuration "Release"
set_property(TARGET SFML::Window APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SFML::Window PROPERTIES
  IMPORTED_LOCATION_RELEASE "/home/Edouard/TEK3/C++/B-CPP-500-PAR-5-1-rtype-pierre.tran/buid/_deps/sfml-build/lib/libsfml-window.so.3.0.0"
  IMPORTED_SONAME_RELEASE "libsfml-window.so.3.0"
  )

# Import target "SFML::Network" for configuration "Release"
set_property(TARGET SFML::Network APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SFML::Network PROPERTIES
  IMPORTED_LOCATION_RELEASE "/home/Edouard/TEK3/C++/B-CPP-500-PAR-5-1-rtype-pierre.tran/buid/_deps/sfml-build/lib/libsfml-network.so.3.0.0"
  IMPORTED_SONAME_RELEASE "libsfml-network.so.3.0"
  )

# Import target "SFML::Graphics" for configuration "Release"
set_property(TARGET SFML::Graphics APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SFML::Graphics PROPERTIES
  IMPORTED_LOCATION_RELEASE "/home/Edouard/TEK3/C++/B-CPP-500-PAR-5-1-rtype-pierre.tran/buid/_deps/sfml-build/lib/libsfml-graphics.so.3.0.0"
  IMPORTED_SONAME_RELEASE "libsfml-graphics.so.3.0"
  )

# Import target "SFML::Audio" for configuration "Release"
set_property(TARGET SFML::Audio APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(SFML::Audio PROPERTIES
  IMPORTED_LOCATION_RELEASE "/home/Edouard/TEK3/C++/B-CPP-500-PAR-5-1-rtype-pierre.tran/buid/_deps/sfml-build/lib/libsfml-audio.so.3.0.0"
  IMPORTED_SONAME_RELEASE "libsfml-audio.so.3.0"
  )

# This file does not depend on other imported targets which have
# been exported from the same project but in a separate export set.

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)
