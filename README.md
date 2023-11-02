# QuantumEngine

> **NOTE**
>
> Under Early Stage of Development

Game Engine that is fast as f***

## Builds on 

- Windows
    - MinGW GCC
    - Clang
    - MSVC VS 2022
- GNU/Linux
    - GCC
    - Clang

## Setting up build enviroment for linux

- Ubuntu

    ```bash
    sudo apt install gcc g++ make cmake ninja clang
    ```

- Fedora

    ```bash
    sudo dnf install gcc gcc-c++ make cmake ninja-build clang
    ```

- Arch Linux

    ```bash
    sudo pacman -S gcc make cmake ninja clang
    ```

## How to Build & Run

> **NOTE**
>
> Output file will be located in bin folder inside your build folder
> 
> So to run the engine just go to \<build folder\>/bin and double click the QuantumEngine.exe file or for linux just double click the QuantumEngine file

### For GCC

- Windows (Powershell)

```bash
    git clone https://github.com/Sherry65-code/QuantumEngine --depth 1
    cd QuantumEngine
    mkdir build
    cd build
    cmake .. -G "Unix Makefiles"
    make
```

> **PREREQUISETS**
>
> make, cmake, gcc compiler, git

- Linux 

```bash
    git clone https://github.com/Sherry65-code/QuantumEngine --depth 1
    cd QuantumEngine
    mkdir build
    cd build
    cmake .. -G "Unix Makefiles"
    make
```

### For Clang

- Windows (Powershell)

```bash
    git clone https://github.com/Sherry65-code/QuantumEngine --depth 1
    cd QuantumEngine
    mkdir build
    cd build
    cmake .. -G "Ninja"
    ninja
```

> **PREREQUISETS**
>
> ninja, cmake, Clang compiler, git

- Linux 

```bash
    git clone https://github.com/Sherry65-code/QuantumEngine --depth 1
    cd QuantumEngine
    mkdir build
    cd build
    cmake .. -G "Ninja"
    ninja
```

### For Visual Studio

- Windows (Powershell or cmd)

```bash
    git clone https://github.com/Sherry65-code/QuantumEngine --depth 1
    cd QuantumEngine
    mkdir build
    cd build
    cmake .. -G "Visual Studio 17 2022"
```

- then open the `QuantumEngine.sln` file in visual studio which is located in your  `<build folder>`
- click on `Local Windows Debugger` button's dropdown icon and select the last option `Configure Startup Projects`
- then in the dropdown menu of `Single Startup Project` select `QuantumEngine` and click `OK`
- Then right-click on `QuantumEngine` in the solution explorer and click `Properties`
- Then on the top in `Configurations` select `All Configurations`
- Then on the left click `Debugging` in the `Configuration Properties Menu`
- Then on the right in the `Working Directory` change the option argument to `$(ProjectDir)\bin`
- Then click `OK`
- Now you are ready to go by pressing the `play` button on the top

> **PREREQUISETS**
>
> cmake, Visual Studio, git

## Directorty Structure

| Folder Name | Use of the folder |
|-------------|-------------------|
| src         | Hold the source code for the engine |
| assets      | Contains all the extra code assets used |
| src/external | Contains the externally used C or C++ files which are some file written by others |
| lib         | contains the libraries compiled format in .a or .lib format |
| include     | contains the source code for included headers |
| [build folder]/bin | contains the files that can be exported outside and can be shared without any garbage |

## File with main() functions

`src/Binary.cpp`

## License 

MIT License

## Contributors & Developers

- [skpijack](https://github.com/skpijack)
- [Sherry65-code](https://github.com/Sherry65-code)

## Without these wonderful projects this project would not have been possible

- [GLFW](https://github.com/glfw/glfw)
- [Glad](https://github.com/Dav1dde/glad)
- [Cmake](https://github.com/Kitware/CMake)
- And yet all the compilers and git and github itself

## Troubleshooting

- Shaders failed to compile without editing
    - Check for assets folder if it is missing from the bin folder
- Build failing due to `-glfw` not found in linux
    - Fix it by installing glfw package for your respective package managers
        - Distros using apt

        ```bash
        sudo apt install libglfw3 libglfw3-dev
        ```

        - Distros using dnf

        ```bash
        sudo dnf install glfw-devel glfw-x11
        ```

        - Distros using pacman

        ```bash
        sudo pacman -S glfw-x11
        ```
    - For Wayland use these
        - Distros using apt

        ```bash
        sudo apt install libglfw3-wayland libglfw3-dev
        ```

        - Distros using dnf

        ```bash
        sudo dnf install glfw-devel glfw-wayland
        ```

        - Distros using pacman

        ```bash
        sudo pacman -S glfw-wayland
        ```

## For contacting me mail here
- sparambir65@gmail.com
