# bouncy ball
little funny ncurses test

compiling with regular ncurses:

```sh
g++ main.cpp -lncurses -o bouncyball
```

compiling with pdcurses SDL2 backend:

```sh
cd pdcurses/sdl2/
WIDE=Y make -j6
cd ../../

g++ main.cpp pdcurses/sdl2/pdcurses.a -lSDL2 -lSDL2_ttf -o bouncyball_sdl
```
