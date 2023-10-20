cmake_minimum_required(VERSION 3.20)

# MAIN PROGRAM
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME PROJECT_ID)
project(${PROJECT_ID})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Release)
set(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE "src/")

# MAIN PROGRAM COMPILE OPTIONS
target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

# TESTS
option(USING_TESTS "Enable testing with Catch2" ON)
option(EXTERNAL_GIT "Add all external repos automatically" ON)
option(CATCH_LOCAL "Configure Installation for a local Catch2 dependency" OFF)

if(USING_TESTS)
  add_executable(tests_app tests/velocity_t.cpp)
  target_include_directories(tests_app PRIVATE "src/")

  if(CATCH_LOCAL)
    find_package(Catch2 3 REQUIRED)
    target_link_libraries(tests_app PRIVATE Catch2::Catch2WithMain)
  elseif (EXTERNAL_GIT)
    set(catch2_install_dir ${CMAKE_BINARY_DIR}/catch2)
    include(ExternalProject)
    ExternalProject_Add(
      Catch2
      GIT_REPOSITORY https://github.com/catchorg/Catch2.git
      GIT_TAG devel
      CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${catch2_install_dir}
      PREFIX ${catch2_install_dir}
    )
    add_dependencies(tests_app Catch2)
    target_link_libraries(tests_app ${catch2_install_dir}/lib/libCatch2Main.a ${catch2_install_dir}/lib/libCatch2.a)
  else()
    add_subdirectory(vendor/Catch2)
    add_dependencies(tests_app Catch2)
    target_link_libraries(tests_app PRIVATE Catch2WithMain)
  endif()
endif()



