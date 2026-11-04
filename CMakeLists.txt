cmake_minimum_required(VERSION 3.20)
project(Demi3D VERSION 0.0.4 LANGUAGES CXX)

find_package(SDL2 CONFIG QUIET)
if(NOT SDL2_FOUND)
    if(MSVC AND CMAKE_CXX_COMPILER_ARCHITECTURE_ID STREQUAL "x64")
        find_package(SDL2 CONFIG REQUIRED
            PATHS "C:/vcpkg/installed/x64-windows/share/sdl2")
    else()
        find_package(SDL2 CONFIG REQUIRED)
    endif()
endif()
find_package(OpenGL REQUIRED)
if(NOT TARGET OpenGL::GLU)
    message(FATAL_ERROR "GLU development libraries are required")
endif()

add_library(${PROJECT_NAME} STATIC
    src/Demi3D.cpp src/DmBloomEffect.cpp src/DmCameraEntity.cpp
    src/DmCubeEntity.cpp src/DmDevice.cpp src/DmEffects.cpp
    src/DmEntity.cpp src/DmFileIO.cpp src/DmGLExtensions.cpp
    src/DmLightEntity.cpp src/DmMaterial.cpp src/DmMaterialManager.cpp
    src/DmMaterialScript.cpp src/DmMeshEntity.cpp src/DmResource.cpp
    src/DmRoot.cpp src/DmSMesh.cpp src/DmSMeshGroup.cpp
    src/DmScene.cpp src/DmShaderARB.cpp src/DmShaderManager.cpp
    src/DmShaderVertex.cpp src/DmSystem.cpp src/DmTexture.cpp)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_compile_definitions(${PROJECT_NAME} PRIVATE SDL_MAIN_HANDLED)
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PUBLIC NOMINMAX WIN32_LEAN_AND_MEAN)
endif()
target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL OpenGL::GLU PRIVATE SDL2::SDL2)

set(demo_dir "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
set(demo_assets
    box.obj scene.gem script.d3s shader.vert shader.vsh sphere.gem sphere.mts tex.bmp)
list(TRANSFORM demo_assets PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/bin/")
add_custom_target(Demi3D_demo_assets
    COMMAND ${CMAKE_COMMAND} -E make_directory "${demo_dir}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${demo_assets} "${demo_dir}"
    VERBATIM)

if(WIN32)
    get_target_property(sdl_type SDL2::SDL2 TYPE)
    if(sdl_type STREQUAL "SHARED_LIBRARY")
        add_custom_command(TARGET Demi3D_demo_assets POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL2::SDL2>" "${demo_dir}" VERBATIM)
    endif()
endif()

foreach(demo IN ITEMS Example Tutorial1)
    add_executable(${demo} example/${demo}/main.cpp)
    target_link_libraries(${demo} PRIVATE ${PROJECT_NAME})
    set_target_properties(${demo} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${demo_dir}")
    add_dependencies(${demo} Demi3D_demo_assets)
endforeach()
