# Requirements
  * A Super Metroid rom (Make sure to rename it to `sm.smc`)
  * libsdl2-dev
  * Super Metroid repo `git clone --recursive https://github.com/snesrev/sm`
  
 For Linux/MacOS you must install these for your desired OS:
 * Ubuntu/Debian: `sudo apt install libsdl2-dev`
 * Fedora Linux: `sudo dnf in sdl2-devel`
 * Arch Linux: `sudo pacman -S sdl2`
 * macOS: `brew install sdl2`

# Windows

## Building with MSYS2

Dependencies and requirements:

  * The `libsdl2-dev` library
  * [MSYS2](https://www.msys2.org)
  
Note: *Make sure you're using MINGW64 and you're in `sm` folder in the terminal.*

1. Install MSYS2 on your machine.
2. Place the copy of your rom in the main directory.
3. Install the necessary dependencies by inputting this command in the terminal.

```sh
pacman -S mingw-w64-x86_64-SDL2 && pacman -S make && pacman -S mingw-w64-x86_64-gcc
```
4. Type `sdl2-config --cflags`, it should output:
```sh
-IC:/msys64/mingw64/include/SDL2 -Dmain=SDL_main
```
5. After that type `sdl2-config --libs`, should output:
```sh
-LC:/msys64/mingw64/lib -lmingw32 -mwindows -lSDL2main -lSDL2
```

After you've done installing everything, cd to `sm` folder. Type `make`
In order to speed up the compilation, type `make -j16`

## Building with Visual Studio

Dependencies and requirements:
 * The `libsdl2-dev` library, which is automatically installed with NuGet.
 * [Visual Studio Community 2022](https://visualstudio.microsoft.com)

Download VS installer. On installer prompt, make sure you're on "Workloads" and check `Desktop Development with C++` this will install the necessary deps for compilation.

1. Open `sm.sln` solution.
2. Change the build target from `Debug` to `Release`
3. Build the solution.

## Building with Tiny C Compiler

 Dependencies and requirements:
 * You'll need [TCC](https://github.com/FitzRoyX/tinycc/releases/download/tcc_20221020/tcc_20221020.zip) and [SDL2](https://github.com/libsdl-org/SDL/releases/download/release-2.24.1/SDL2-devel-2.24.1-VC.zip) in order to compile using TCC.

1. Unzip both TCC and SDL and place them in `third_party` folder.
2. Double click `run_with_tcc.bat`
3. Wait for it to compile and the game will automatically boot-up.

# Linux/MacOS

CD to your SM root folder and open the terminal and type:
```sh
make
```

For more advanced usage:
```sh
make -j$(nproc) # run on all core
make clean all  # clear gen+obj and rebuild
CC=clang make   # specify compiler
```

# Nintendo Switch

Dependencies and requirements:

  * The `switch-sdl2` library
  * [DevKitPro](https://github.com/devkitPro/installer)
  * [Atmosphere](https://github.com/Atmosphere-NX/Atmosphere)
  
1. Make sure you've installed Atmosphere on your Switch.
2. Please download the DevKitPro version of MSYS2 through their installer, as the default MSYS2 causes issues with windows compiling.
3. Now that you've installed DevKitPro, open up the location you've installed DevKitPro to, then find `mingw64.exe` inside `msys2` located in `devkitPro` folder.
4. Type `pacman -S git switch-dev switch-sdl2 switch-tools` in the terminal to install the `switch-sdl2` library.
5. CD to `switch` folder by typing `cd src/platfrom/switch` in the terminal on the `sm` root folder.
6. type `make` to compile the Switch Port.
7. Transfer the `.ini`, `nro`, `ncap` and your rom file to the Switch.

**OPTIONAL STEP**

```sh
make -j$(nproc) # To build using all cores
```

# Playstation Vita

Dependencies and requirements:

* [VitaSDK](https://vitasdk.org/)

1. Install VitaSDK and SDL2 (included automatically in the standard installation of VitaSDK)
2. CD to `vita` folder by typing `cd src/platform/vita` in the terminal on the `sm` root folder.
3. Create a build folder and enter it `mkdir -p build && cd build`
4. type `cmake ..` to create the makefile for Vita adapted to your development configuration.
5. type `make` to compile the Vita version.
6. Transfer the `sm.vpk` to your Vita and install it with VitaShell or your favorite installer.
