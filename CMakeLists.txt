cmake_minimum_required(VERSION 3.19)
project(slinty_bindy LANGUAGES CXX)

find_package(Slint QUIET)
if (NOT Slint_FOUND)
  message("Slint could not be located in the CMake module search path. Downloading it from Git and building it locally")
  include(FetchContent)
  FetchContent_Declare(
    Slint
    GIT_REPOSITORY https://github.com/slint-ui/slint.git
    GIT_TAG v0.2.0
    SOURCE_SUBDIR api/cpp
  )
  FetchContent_MakeAvailable(Slint)
endif (NOT Slint_FOUND)

find_package(KDBindings QUIET)
if (NOT KDBindings_FOUND)
  message("KDBindings could not be located in the CMake module search path. Downloading it from Git and building it locally")
  include(FetchContent)
  FetchContent_Declare(
    KDBindings
    GIT_REPOSITORY https://github.com/KDAB/KDBindings
    GIT_TAG main
  )
  FetchContent_MakeAvailable(KDBindings)
endif (NOT KDBindings_FOUND)



add_executable(slinty_bindy 
src/main.cpp
src/backend_controller.cpp
src/backend_controller.h
src/undostack_model.cpp
src/undostack_model.h
)
target_link_libraries(slinty_bindy PRIVATE Slint::Slint KDAB::KDBindings)
slint_target_sources(slinty_bindy ui/appwindow.slint)
