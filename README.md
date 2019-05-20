# Bake
<b>Authors:</b> Bruce How ([22242664](https://github.com/brucehow/)) & Vincent Tian ([22262122](https://github.com/vtian72))

Bake is a small program supporting a small subset of the features of the standard Unix-based utility make.

It is apart of the 2018 CITS2002 Systems Programming Project.

## Installation
Use the provided `Makefile` to compile the program which will create an executable `Bake` program.
```bash
make Bake
```

## Usage
The program can be ran with optional parameters. There are 6 optional parameters which can be defined.

* `-C directoryname` before opening and reading the specification file, bake is to change directory to the indicated directory.
* `-f filename` instead of reading its specification from the default Bakefile or bakefile, bake reads its specification from the indicated file.
* `-i` ignore the unsuccessful termination of actions; continue executing a target's actions even if any fail.
* `-n` print (to stdout) each shell-command-sequence before it is to be executed, but do not actually execute the commands. Assume that each shell-command-sequence executes successfully. This option enables bake to simply report what it would do, without doing it.
* `-p` after reading in the specification file, print its information (from bake's internal representation) to stdout with all variable expansions performed. Then simply exit with success. 
Only the targets, dependencies, and actions need be printed (though you may wish to also print the variables (names and values).
* `-s` execute silently, do not print each shell-command-sequence before it is executed.

**Example**
```bash
bake -in -f fileToBake -C ../bakedir
```
