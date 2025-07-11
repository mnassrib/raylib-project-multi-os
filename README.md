# 🎮 Raylib Project (Multi-OS)

Ce projet montre comment structurer un projet C avec la bibliothèque [Raylib](https://www.raylib.com/), en utilisant **CMake**, avec une prise en charge complète sur **Windows**, **macOS** et **Linux**.

Il s’appuie sur un workflow GitHub Actions **multiplateforme** pour compiler automatiquement le projet à chaque mise à jour.

---

## 📁 Structure du projet

```
raylib-project-multi-os/
├── CMakeLists.txt                 # Configuration CMake
├── src/                           # Fichiers source (.c)
│   ├── main.c
│   ├── player.c
│   └── utils.c
├── include/                       # Fichiers d'en-tête (.h)
│   ├── player.h
│   └── utils.h
├── build/                         # Répertoire généré lors de la compilation
└── .github/
    └── workflows/
        └── ci-cross-platform.yml  # GitHub Actions (Windows + Linux + macOS)
```

---

## ⚙️ Compilation locale

### 🔧 Prérequis communs

* [CMake](https://cmake.org/download/)
* [Raylib](https://www.raylib.com/)
* Compilateur compatible C99 (`gcc`, `clang`, `MinGW`...)

---

### 🪟 Windows

#### 📦 Installation de Chocolatey

PowerShell (en mode administrateur) :
```powershell
Set-ExecutionPolicy Bypass -Scope Process -Force
iwr https://chocolatey.org/install.ps1 -UseBasicParsing | iex
```

#### 📦 Installation de MinGW et CMake

```powershell
choco install mingw -y
choco install cmake -y --installargs 'ADD_CMAKE_TO_PATH=System'
```

#### 📥 Installer Raylib

```cmd
git clone https://github.com/raysan5/raylib.git
cd raylib
mkdir build && cd build
cmake -G "MinGW Makefiles" -DBUILD_EXAMPLES=OFF ..
mingw32-make
cmake --install . --prefix "C:/raylib"
```

#### 🛠️ Compiler le projet

```cmd
git clone https://github.com/mnassrib/raylib-project-multi-os.git
cd raylib-project-multi-os
mkdir build && cd build
cmake -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH="C:/raylib" ..
mingw32-make
.\raylib-project-multi-os.exe
```

---

### 🍎 macOS

#### 📦 Installation via Homebrew

```bash
brew install cmake raylib
```

#### 🛠️ Compiler le projet

```bash
git clone https://github.com/mnassrib/raylib-project-multi-os.git
cd raylib-project-multi-os
mkdir build && cd build
cmake ..
make
./raylib-project-multi-os
```

---

### 🐧 Linux (Ubuntu/WSL)

#### 📦 Installer les dépendances

```bash
sudo apt update
sudo apt install -y cmake build-essential \
libasound2-dev libx11-dev libxcursor-dev \
libxrandr-dev libxi-dev libgl1-mesa-dev \
libxinerama-dev libxss-dev libwayland-dev \
libpulse-dev libxext-dev git
```

#### 📥 Compiler Raylib

```bash
git clone https://github.com/raysan5/raylib.git
cd raylib
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_EXAMPLES=OFF ..
make
sudo make install
```

#### 🛠️ Compiler le projet

```bash
git clone https://github.com/mnassrib/raylib-project-multi-os.git
cd raylib-project-multi-os
mkdir build && cd build
cmake ..
make
./raylib-project-multi-os
```

---

## ✅ Intégration Continue (GitHub Actions)

Ce dépôt est compilé automatiquement à chaque `push` ou `pull request` sur :

* 🪟 **Windows**
* 🍎 **macOS**
* 🐧 **Linux**

| Plateforme | Statut                                                                                                                        |
| ---------- | ----------------------------------------------------------------------------------------------------------------------------- |
| 🪟 Windows | ![Windows](https://github.com/mnassrib/raylib-project-multi-os/actions/workflows/ci-cross-platform.yml/badge.svg?branch=main) |
| 🍎 macOS   | ![macOS](https://github.com/mnassrib/raylib-project-multi-os/actions/workflows/ci-cross-platform.yml/badge.svg?branch=main)   |
| 🐧 Linux   | ![Linux](https://github.com/mnassrib/raylib-project-multi-os/actions/workflows/ci-cross-platform.yml/badge.svg?branch=main)   |

---

## 🚀 Télécharger l'exécutable précompilé

Une release est générée automatiquement à chaque **tag Git** (ex. : `v1.2.0`).

1. Rendez-vous sur la page [Releases](https://github.com/mnassrib/raylib-project-multi-os/releases)
2. Téléchargez le fichier `.exe`, `.app`, ou exécutable selon votre OS
3. Lancez-le directement sans recompiler

---

## 🧠 Ressources utiles

* [Raylib — Site officiel](https://www.raylib.com/)
* [MinGW-w64](https://www.mingw-w64.org/)
* [Homebrew pour macOS](https://brew.sh)
* [CMake — Documentation](https://cmake.org/documentation/)
* [GitHub Actions](https://docs.github.com/en/actions)

---

## 📜 Licence

Ce projet est librement réutilisable à des fins pédagogiques et d’apprentissage.
