Falltergeist
============

Opensource crossplatform Fallout 2™ engine writen in C++ and SDL.
https://falltergeist.org/

Current version: 0.1.6

IRC channel: #falltergeist on [freenode.net](http://webchat.freenode.net/?channels=falltergeist)


##Compilation under linux

First of all you need to compile libfalltergeist library:

```
git submodule init
git submodule update
cd lib/libfalltergeist && cmake . && make && cd -

```

Now you can compile Falltergeist:

```
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
