# uSH: a small shell
## Written by Noah Brecht

[![Build status](https://img.shields.io/travis/noahb01/ush.svg)](https://travis-ci.org/noahb01/ush)
[![Downloads](https://img.shields.io/github/downloads/noahb01/ush/total.svg)](https://github.com/noahb01/ush/releases)

*Pronounced micro-shell!*  

A micro-shell for the Linux OS. It supports I/O piping and has a few builtins. It is considerably smaller that bash, zsh, etc.
It also has no dependencies, making it extremely portable.  
  
The build process is extremely simple:  
`make all` to build.  
`./ush` to run.  
`make clean` to clean the source tree and remove binaries/objects.  

# Syntax

Run a single command:  
`:? <command> <arguments>`  
Pipe multiple commands together:  
`:? <command1> <arg1> | <command2> <arg2>`  
Run a system command with the same name as a builtin command:  
`:? <command>^ <arguments>`  
Use a shell variable as a command:  
`> $var <arguments>`  
Use a shell variable as an argument:  
`:? <command> $var`  
