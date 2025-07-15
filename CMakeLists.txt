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

# Active la détection automatique des fichiers .c dans src/ (OFF = sélection manuelle)
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

# Si l'utilisateur n'a pas déjà défini CMAKE_PREFIX_PATH, on fournit un chemin par défaut (optionnel)
if(WIN32 AND NOT DEFINED CMAKE_PREFIX_PATH)
    set(CMAKE_PREFIX_PATH "C:/raylib")
    message(STATUS "CMAKE_PREFIX_PATH non défini, utilisation du chemin par défaut : C:/raylib")
endif()

# Détection automatique de Raylib
find_package(raylib QUIET)

message(STATUS "Raylib trouvé via find_package()")
target_link_libraries(${PROJECT_NAME} raylib)


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
