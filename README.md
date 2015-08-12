Falltergeist [![build status](https://secure.travis-ci.org/falltergeist/falltergeist.png)](http://travis-ci.org/falltergeist/falltergeist)
============

Opensource crossplatform Fallout 2™ engine writen in C++ and SDL.
https://falltergeist.org/

Current version: 0.2.0

IRC channel: #falltergeist on [freenode.net](http://webchat.freenode.net/?channels=falltergeist)

Jabber chanel: falltergeist on conference.jabber.ru

##Dependencies

- [SDL](http://www.libsdl.org) (libsdl2)
- [SDL\_mixer](http://www.libsdl.org/projects/SDL_mixer/) (libsdl2-mixer)
- [SDL\_image](http://www.libsdl.org/projects/SDL_image/) (libsdl2-image)
- [Lua](http://www.lua.org/) (liblua)

##Compilation under linux

```
git submodule update --init
cmake . && make
```

## Running under linux

Put master.dat and critter.dat files into the falltergeist data directory, that is

* `~/.local/share/falltergeist/` on Linux,
*  `~/Library/Application Support/falltergeist` on OS X,
* `%APPDATA%/falltergeist` on Windows,

or mount CD-ROM with original game, then run

```
./falltergeist
```
