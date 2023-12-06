# Sling

A small car game developed in C using Raylib

## Compiling

### Raylib

#### Compilation

The first step is cloning the Raylib git repository.
Preferably this should be done through in a seperate directory.

```shell
git clone https://github.com/raysan5/raylib.git
cd raylib/src
```

This project uses the dynamic shared version of Raylib.

```shell
make PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=SHARED # To make the dynamic shared version.
```

The shared object files will then be created in the `raylib/src` directory.

#### Installation

This project expects these files to be installed to its own `./deps` directory
but the files can alternatively be installed to a standard path.

##### Local

Following commands should be executed from the project root directory.

```shell
mkdir deps
cp --update -d /path/to/raylib/src/*.so* deps
cp --update /path/to/raylib/src/raylib.h deps
cp --update /path/to/raylib/src/raymath.h deps
cp --update /path/to/raylib/src/rlgl.h deps
```

##### Global

```shell
sudo make install RAYLIB_LIBTYPE=SHARED # Dynamic shared version.
```

Please refer to [Raylib](https://www.raylib.com/) for further instructions.

### Sling

Compile the project from scratch.

```
make all
```

## Playing

The game can be started with:

```
make run
```
or
```
./bin/main
```

### Controls

Drive the car with <kbd>WASD</kbd> and use <kbd>Space</kbd> to sling yourself around the closest hook connector.

The game can be exited with <kbd>ESC</kbd>

### Aim

The aim of the game is to be as fast as possible from start to finish. Properly using your hook is a key to this,
but make sure to stay on the track as well since the car drives much faster when it's on a good surface!

