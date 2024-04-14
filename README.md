# Conway's Game Of Life

## Overview

This is SDL2 implementation of the Conway's game of life

This project is built with
<img src="https://mesonbuild.com/assets/images/meson_logo.png" height="16px">
[Meson](https://mesonbuild.com/). To install meson you can visit their [GitHub page](https://github.com/mesonbuild/meson/tree/master/docs).

## Dependencies

- [SDL2](https://github.com/libsdl-org/SDL)
- [SDL2_ttf](https://github.com/libsdl-org/SDL_ttf)
- [SDL2_gfx](https://github.com/mupfdev/SDL2_gfx)

## Compilation

To compile the project, first you need to build it using

```console
meson setup {{ build directory }}
```

You can compile the project using

```console
meson compile -C {{ build directory }}
```

## Warning

This project uses a bad implementation of installing shared libraries, if you have suggestions on how to fix it please write it in github issues