cmake_minimum_required( VERSION 3.5 )

project( xora )

IF (WIN32)
  # Statically link standard libraries on Windows. TODO: make compatible with msvc
  set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
ENDIF()

set (OpenGL_GL_PREFERENCE GLVND)

find_package( OpenGL REQUIRED )

include_directories( ${OPENGL_INCLUDE_DIRS} ./src ./include )

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_BUILD_WAYLAND OFF)
# set( GLAD_GL "" )

add_subdirectory( glfw )
add_subdirectory( libbullet3-cmake )
add_subdirectory( glm )

option( XORA-USE-GLFW-GLAD "Use GLAD from GLFW" ON )

if( XORA-USE-GLFW-GLAD )
    include_directories("${GLFW_SOURCE_DIR}/deps")
    set( GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h" )
endif()

if( MSVC )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

set( XORA-EXTERN
    ./include/miniaudio.c
    ./include/stb_image.c
    ./include/stb_image_write.c
    ./include/glad/glad.c
    ./include/pocketpy.c
)

set( XORA-UTILS
    src/utils/fs.cpp
    src/utils/path.cpp
    src/utils/time.cpp
    src/utils/tiny_obj_loader.cc
)

set( XORA-ENGINE
    src/engine/engine.cpp
    src/engine/module.cpp
)

set( XORA-INPUT
    src/input/vinput.cpp
    src/input/vbutton.cpp
    src/input/vaxis.cpp
    src/input/vaxis2d.cpp
)

set( XORA-GRAPHICS 
    src/graphics/graphics.cpp
    src/graphics/texture.cpp
    src/graphics/shader.cpp
    src/graphics/mesh.cpp
)

set( XORA-VM
    src/vm/vm.cpp
    src/vm/vm_engine.cpp
    src/vm/vm_system.cpp
    src/vm/vm_window.cpp
    src/vm/vm_input.cpp
    src/vm/vm_graphics.cpp
)

# set( XORA-GAME 
#     src/game/game.cpp
#     src/game/box.cpp
#     src/game/globals.cpp
#     src/game/camera.cpp
# )

set( XORA-SRC ${XORA-EXTERN} ${XORA-UTILS} ${XORA-ENGINE} ${XORA-INPUT} ${XORA-GRAPHICS} ${XORA-VM} src/main.cpp )

add_executable( xora ${XORA-SRC} ${GLAD_GL} )
# add_executable( xora WIN32 ${XORA-SRC} ${GLAD_GL} )
# Set warning levels
# if(MSVC)
#   target_compile_options(xora PRIVATE /W4 /WX)
# else()
#   target_compile_options(xora PRIVATE -Wall -Wextra -Wpedantic -Werror)
# endif()
target_link_libraries( xora ${OPENGL_LIBRARIES} glfw libbullet3 glm )
if( MSVC )
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0")
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'GLFW-CMake-starter' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT xora )
    endif()
endif()
