Falltergeist [![Build Status](https://travis-ci.org/falltergeist/falltergeist.svg?branch=develop)](https://travis-ci.org/falltergeist/falltergeist) [![Version](https://img.shields.io/github/release/falltergeist/falltergeist.svg)](https://github.com/falltergeist/falltergeist/releases/latest) [![Discord](https://img.shields.io/discord/401990446747877376.svg)](https://discord.gg/jxs6WRq)
============

Opensource crossplatform Fallout 2™ engine writen in C++ and SDL.
https://falltergeist.org/

## Dependencies

- [SDL2](http://www.libsdl.org)
- [SDL2\_mixer](http://www.libsdl.org/projects/SDL_mixer/)
- [SDL2\_image](http://www.libsdl.org/projects/SDL_image/)
- [GLEW](http://glew.sourceforge.net/)
- [GLM](http://glm.g-truc.net/)
- [Zlib](http://www.zlib.net/)

## Compilation under linux

```
cmake . && make
```
To build the Snap version:

* checkout the `snap` branch in git
* `sudo apt install snapcraft` (this command may vary according to your distro)
* Execute the `snapcraft` command

## Running under linux

Put master.dat and critter.dat files into the falltergeist data directory, that is

* `~/.local/share/falltergeist/`  or `/usr/local/share/falltergeist` (for global installs) on Linux,
*  `~/Library/Application Support/falltergeist` on OS X,
* `%APPDATA%/falltergeist` on Windows,
* For Snap packages, the data must be stored locally in `~/snap/falltergeist/current/.local/share/falltergeist/` at the moment
* To install a freshly built snap version, type `snap install --devmode --dangerous ./falltergeist_0.3.1_amd64.snap`, press enter and type your password when prompted

or mount CD-ROM with original game, then run

```
./falltergeist
```
