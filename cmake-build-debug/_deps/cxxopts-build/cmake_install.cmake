# Install script for directory: /Users/xiahuahui/go/src/github.com/tendermint/tendermint/abci/example/smallbank/gc_wvcp_mcts/cmake-build-debug/_deps/cxxopts-src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/cxxopts" TYPE FILE FILES
    "/Users/xiahuahui/go/src/github.com/tendermint/tendermint/abci/example/smallbank/gc_wvcp_mcts/cmake-build-debug/_deps/cxxopts-build/cxxopts-config.cmake"
    "/Users/xiahuahui/go/src/github.com/tendermint/tendermint/abci/example/smallbank/gc_wvcp_mcts/cmake-build-debug/_deps/cxxopts-build/cxxopts-config-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/cxxopts/cxxopts-targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/cxxopts/cxxopts-targets.cmake"
         "/Users/xiahuahui/go/src/github.com/tendermint/tendermint/abci/example/smallbank/gc_wvcp_mcts/cmake-build-debug/_deps/cxxopts-build/CMakeFiles/Export/lib/cmake/cxxopts/cxxopts-targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/cxxopts/cxxopts-targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/cxxopts/cxxopts-targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/cxxopts" TYPE FILE FILES "/Users/xiahuahui/go/src/github.com/tendermint/tendermint/abci/example/smallbank/gc_wvcp_mcts/cmake-build-debug/_deps/cxxopts-build/CMakeFiles/Export/lib/cmake/cxxopts/cxxopts-targets.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "/Users/xiahuahui/go/src/github.com/tendermint/tendermint/abci/example/smallbank/gc_wvcp_mcts/cmake-build-debug/_deps/cxxopts-src/include/cxxopts.hpp")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/xiahuahui/go/src/github.com/tendermint/tendermint/abci/example/smallbank/gc_wvcp_mcts/cmake-build-debug/_deps/cxxopts-build/src/cmake_install.cmake")
  include("/Users/xiahuahui/go/src/github.com/tendermint/tendermint/abci/example/smallbank/gc_wvcp_mcts/cmake-build-debug/_deps/cxxopts-build/test/cmake_install.cmake")

endif()

