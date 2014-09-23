Falltergeist
============

Opensource crossplatform Fallout 2™ engine writen in C++ and SDL.
https://falltergeist.org/

Current version: 0.1.4

IRC chanel: #falltergeist on [freenode.net](http://webchat.freenode.net/?channels=falltergeist)


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

Put master.dat and critter.dat files into the falltergeist data directory:

* Linux: `~/.local/share/falltergeist/`,
* OS X: `~/Library/Application Support/falltergeist`,
* Windows: `%APPDATA%/falltergeist`,

or mount CD-ROM with original game, then run

```
./falltergeist
```
