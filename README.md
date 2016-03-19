Falltergeist [![build status](https://secure.travis-ci.org/falltergeist/falltergeist.png)](http://travis-ci.org/falltergeist/falltergeist)
============

Opensource crossplatform Fallout 2™ engine writen in C++ and SDL.
https://falltergeist.org/

Current version: 0.3.0

IRC channel: #falltergeist on [freenode.net](http://webchat.freenode.net/?channels=falltergeist)

Jabber chanel: falltergeist on conference.jabber.ru

##Dependencies

- [SDL2](http://www.libsdl.org) (libsdl2)
- [SDL2\_mixer](http://www.libsdl.org/projects/SDL_mixer/) (libsdl2-mixer)
- [SDL2\_image](http://www.libsdl.org/projects/SDL_image/) (libsdl2-image)
- [GLEW](http://glew.sourceforge.net/)
- [GLM](http://glm.g-truc.net/)
- [Zlib](http://www.zlib.net/) (Zlib)

##Compilation under linux

```
cmake . && make
```

## Running under linux

Put master.dat and critter.dat files into the falltergeist data directory, that is

* `~/.local/share/falltergeist/`  or `/usr/local/share/falltergiest` (for global installs) on Linux,
*  `~/Library/Application Support/falltergeist` on OS X,
* `%APPDATA%/falltergeist` on Windows,

or mount CD-ROM with original game, then run

```
./falltergeist
```
