# Conway's Game Of Life

## Overview

This is SDL2 implementation of the Conway's game of life

![image](https://github.com/C010UR/sdl2-conways-game-of-life/assets/95462776/e9896ef7-bf68-46e3-be99-48167885a880)

https://github.com/C010UR/sdl2-conways-game-of-life/assets/95462776/27a651f3-d1c1-4214-99f8-61cbb33f2903

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
