cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(TiledParser)

find_package(raylib 2.0 QUIET) # Let CMake search for a raylib-config.cmake

# You could change the QUIET above to REQUIRED and remove this if() clause
# This part downloads raylib and builds it if it's not installed on your system
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)

  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/master.tar.gz
  )

  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

    # build raylib
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

  endif()

endif()

# This is the main part:
include_directories(
  ./lib/tinyxml2/
  ./TiledParser/
  ./SceneDirector/
  ./SceneDirector/Scenes
  )

add_library(SceneDirector
  STATIC
    ./SceneDirector/SceneDirector.cpp
  )
set_target_properties(SceneDirector
  PROPERTIES
    CXX_STANDARD 17
  )

add_library(Scene
  STATIC
    ./SceneDirector/Scenes/GameScene/GameScene.cpp
    ./SceneDirector/Scenes/GameOverScene/GameOverScene.cpp
    ./SceneDirector/Scenes/StartScene/StartScene.cpp
    # ./SceneDirector.cpp
  )
set_target_properties(SceneDirector
  PROPERTIES
    CXX_STANDARD 17
  )

add_library(TiledAdapter
  STATIC
    ./TiledParser/TiledMap.cpp
    ./TiledParser/TiledParser.cpp
    ./lib/tinyxml2/tinyxml2.cpp
  )
set_target_properties(TiledAdapter
  PROPERTIES
    CXX_STANDARD 17
  )

target_link_libraries(SceneDirector TiledAdapter Scene)

add_executable(${PROJECT_NAME} main.cpp)
set_target_properties(${PROJECT_NAME}
  PROPERTIES
    CXX_STANDARD 17
  )
#set(raylib_VERBOSE )
target_link_libraries(${PROJECT_NAME} raylib TiledAdapter SceneDirector)

# That's it! You should have an example executable that you can run. Have fun!
