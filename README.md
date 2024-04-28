# Burning Star

For now just a basic game I'm trying to make for absolutely no reason other
than "just because" (and to also learn C).

For future (hopefully) features see [todo](todo) file

## Installation
### Configuration
Read through the [config](./src/config.h) file, and comment/uncomment the
options you want, only then can you proceed

### Linux
#### download the source code
```sh
git clone https://github.com/vodam46/burning-star.git
```
#### compilation
```sh
make
```
#### run
```sh
make run
```
or (after compilation)
```sh
./bin/burning-star
```
#### Debug version
Runs the entire program inside gdb
```sh
make debug
```
#### Unit tests
```sh
make test
```

### Windows
- install [MSYS2](https://www.msys2.org/)
- open the MSYS2 commandline
- install gcc, make, ncurses
    `pacman -S gcc make ncurses-devel`
- navigate to the directory where you downloaded this project
    `cd DIRECTORY`

to compile and run the game, make sure youre in the MSYS2 terminal, then follow
the linux instructions
