cmake_minimum_required(VERSION 3.10) 
 
# Définir le nom du projet à partir du nom du dossier courant
get_filename_component(PROJ_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME) 
project(${PROJ_NAME} C) 

# Spécifier la version du standard C 
set(CMAKE_C_STANDARD 99) 
set(CMAKE_C_STANDARD_REQUIRED ON) 
 
# Inclure les headers personnalisés
include_directories(include) 
 
# ========================= 
# Sources 
# ========================= 
 
option(USE_AUTO_SOURCES 
       "Compiler automatiquement tous les fichiers .c de src/" 
       ON) 
 
if(USE_AUTO_SOURCES) 
    file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.c) 
    add_executable(${PROJECT_NAME} ${SRC_FILES}) 
else() 
    add_executable(${PROJECT_NAME} 
        src/main.c 
        src/player.c 
        src/utils.c 
    ) 
endif() 
 
# ========================= 
# Raylib 
# ========================= 
 
if(WIN32 AND NOT DEFINED CMAKE_PREFIX_PATH) 
    set(CMAKE_PREFIX_PATH "C:/raylib") 
endif() 
 
find_package(raylib QUIET) 
 
if(raylib_FOUND) 
 
    message(STATUS "Raylib trouvé via find_package()") 
 
    # Cas moderne : package CMake Raylib 
    target_link_libraries(${PROJECT_NAME} raylib) 
 
else() 
 
    message(STATUS 
        "Package Raylib non trouvé, tentative de liaison via GCC/MinGW") 
 
    # Cas MinGW : GCC trouve lui-même libraylib.a 
    target_link_libraries(${PROJECT_NAME} raylib) 
 
endif() 
 
# ========================= 
# Bibliothèques système 
# ========================= 
 
if(WIN32) 
 
    target_link_libraries(${PROJECT_NAME} 
        winmm 
        gdi32 
        opengl32 
    ) 
 
elseif(APPLE) 
 
    find_library(COCOA_LIBRARY Cocoa) 
    find_library(IOKIT_LIBRARY IOKit) 
    find_library(COREVIDEO_LIBRARY CoreVideo) 
    find_library(OPENGL_LIBRARY OpenGL) 
 
    target_link_libraries(${PROJECT_NAME} 
        ${COCOA_LIBRARY} 
        ${IOKIT_LIBRARY} 
        ${COREVIDEO_LIBRARY} 
        ${OPENGL_LIBRARY} 
    ) 
 
elseif(UNIX AND NOT APPLE) 
 
    target_link_libraries(${PROJECT_NAME} 
        m 
        pthread 
        dl 
        X11 
        GL 
    ) 
 
endif() 
