cmake_minimum_required(VERSION 3.10)

# Définir le nom du projet à partir du nom du dossier courant
get_filename_component(PROJ_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJ_NAME} C)

# Spécifier la version du standard C
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Inclure les headers personnalisés
include_directories(include)


# === Choix des fichiers source ===

# Utiliser automatiquement tous les fichiers .c dans src/ sinon changer ON par OFF
option(USE_AUTO_SOURCES "Compiler automatiquement tous les fichiers .c dans src/" ON)

if(USE_AUTO_SOURCES)
    message(STATUS "Compilation automatique des fichiers sources (.c)")
    file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.c)
    add_executable(${PROJECT_NAME} ${SRC_FILES})
else()
    message(STATUS "Compilation manuelle des fichiers sources")
    add_executable(${PROJECT_NAME}
        src/main.c
        src/player.c
        src/utils.c
    )
endif()


# === Configuration de Raylib ===

# Si Raylib a été installé dans un répertoire non standard sur Windows
if(WIN32)
    # Spécifiez le chemin de Raylib si installé via CMake install/modifier si besoin
    set(RAYLIB_PATH "C:/raylib")
    set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${RAYLIB_PATH}")
endif()

# Détection automatique de Raylib
find_package(raylib QUIET)

if(raylib_FOUND)
    message(STATUS "Raylib trouvé via find_package()")
    target_link_libraries(${PROJECT_NAME} raylib)
else()
    message(STATUS "Raylib non trouvé via find_package() - fallback manuel")

    if(WIN32)
        message(STATUS "Lien manuel avec Raylib pour MinGW")
        target_link_libraries(${PROJECT_NAME} raylib)
    else()
        message(SEND_ERROR "Raylib non trouvé et aucun fallback disponible (non-Windows)")
    endif()
endif()


# === Lien avec bibliothèques système selon l'OS ===

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
