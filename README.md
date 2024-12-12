![Robot-man](assets/images/Robotman2.jpg)

# Robot-man

In the vastness of the internet, in the deepest recesses of the web, there is a small file called robot.png
The little boy always dreamed of fighting the evil that tormented the github repositories  
Under the nickname Robot-man, the little boy decides to leave his folder seeking to fulfill his objective, destroy the Trojan army that plagued his community.  
Will the little robot-man be able to defeat Error404 and save his friends?

## Systems

The project is developed on MinGW64 using Msys2  
The editor being used is Visual Studio Code

## How to run the game

Install all the dependencies described below and run in a vscode terminal:

> make run'ExecutableName'

For example, to run 'Robotman.cpp' run the command in the vscode terminal:

> make runRobotman


## Required programs

### Visual studio code
Download and install vscode in the following [link.](https://code.visualstudio.com/)

### MSYS2 (Windows)

Install Msys2 using the following [link.](https://github.com/msys2/msys2-installer/releases/download/2023-05-26/msys2-x86_64-20230526.exe)

Do not modify any options at the time of installation or the configurations may change.

Once installed, it is necessary to add directories to the Windows path.

To add directories, it is necessary to open the Windows path  
Go to environment variables  
Path  
Paste the following directories:

> C:\msys64\mingw64\bin

> C:\msys64\usr\bin

Reboot the system

### Github Desktop

Desktop client to clone the repository, download using the following [link.](https://desktop.github.com/).

### Git

In order to commit vscode you need to have Git installed, download it from the following [link.](https://git-scm.com/).

## Libraries used (Msys2)

Run the following commands in the msys2 terminal to install the necessary dependencies 
Copy and paste

### DevTools

Compilers and tools needed for development.

https://code.visualstudio.com/docs/cpp/config-mingw
> pacman -S --needed base-devel mingw-w64-x86_64-toolchain

### SFML

https://packages.msys2.org/package/mingw-w64-x86_64-sfml
> pacman -S mingw-w64-x86_64-sfml

### Box2D physics simulations - C++

https://box2d.org/documentation/
https://packages.msys2.org/package/mingw-w64-x86_64-box2d?repo=mingw64
pacman -S mingw-w64-x86_64-box2d

## VSCode Required Plugins

- Material Icon
- C/C++
- PlantUML
- GitGraph