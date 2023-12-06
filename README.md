# Sling

A small car game developed in C using Raylib

## Installation

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

