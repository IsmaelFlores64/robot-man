![Robot-man](assets/images/Robotman2.jpg)

# Robot-man

En la inmensidad del internet en lo mas recondito de la web existe un pequeño archivo llamado robot.png
El pequeño siempre soñó con combatir el mal que atormentaba los repositorios de github  
Bajo el sobrenombre Robot-man el pequeño decidio salir de su carpeta buscando cumplir su objetivo, destruir el ejercito troyano que azotaba su comunidad  
Será que el pequeño robot-man lograra derrotar al Error404 y salvar a sus amigos?

## Sistemas

El proyecto esta desarrollado sobre MinGW64 utilizando Msys2
El editor que se esta utilizando Visual Studio Code

## Como ejecutar los ejemplos

Instalar todas las dependencias descritas abajo y dentro de una terminal de vscode ejecutar:

> make run'NombreEjecutable'

Por ejemplo para ejecutar '00_Ventana.cpp' correr el comando en la terminal de vscode:

> make run00_Ventana


## Programas necesarios

### Visual estudio code
Descargar e instalar vscode en el siguiente [Enlace.](https://code.visualstudio.com/)

### MSYS2 (Windows)

Instalar Msys2 usando el siguiente [Enlace.](https://github.com/msys2/msys2-installer/releases/download/2023-05-26/msys2-x86_64-20230526.exe)

No modificar ningua opcion al momento de intalacion o podrian variar las configuraciones.

Una vez instalado es necesario agregar directorios al path de windows.

Para agregar directorios es necesario abrir el path de windows  
Ir a variables de entorno  
Path  
Pegar los siguientes directorios: 

> C:\msys64\mingw64\bin

> C:\msys64\usr\bin

Reiniciar el sistema

### Github Desktop
Cliente de escritorio para clonar el repositorio, descargar usando el siguiente [enlace](https://desktop.github.com/).

### Git
Para poder realizar commits de vscode es necesario tener instalado Git, descargarlo del siguiente [enlace](https://git-scm.com/).


## Librerias utilizadas (Msys2)

Ejecutar los siguientes comandos en la terminal de msys2 para instalar las dependencias necesarias  
Copiar y pegar

### DevTools

Compiladores y herramientas necesarias para el desarrollo.

https://code.visualstudio.com/docs/cpp/config-mingw
> pacman -S --needed base-devel mingw-w64-x86_64-toolchain

### SFML
https://packages.msys2.org/package/mingw-w64-x86_64-sfml
> pacman -S mingw-w64-x86_64-sfml

### Box2D simulaciones de fisica - C++
https://box2d.org/documentation/
https://packages.msys2.org/package/mingw-w64-x86_64-box2d?repo=mingw64
pacman -S mingw-w64-x86_64-box2d

## Complementos necesarios VSCode

- Material Icon
- C/C++
- PlantUML
- GitGraph