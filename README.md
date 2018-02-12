# uSH: a small shell
## Written by Noah Brecht

[![Build status](https://img.shields.io/travis/noahb01/ush.svg)](https://travis-ci.org/noahb01/ush)
[![Downloads](https://img.shields.io/github/downloads/noahb01/ush/total.svg)](https://github.com/noahb01/ush/releases)
[![Latest stable release](https://img.shields.io/github/release/noahb01/ush.svg?maxAge=3600)](https://github.com/noahb01/ush/releases)

A micro-shell for the Linux. It supports piping and redirection and has a few builtins. It is considerably smaller that bash, zsh, etc.
It also has no dependencies, making it extremely portable.  
  
The build process is extremely simple:  
`make all` to build.  
`./ush` to run.  
`make clean` to clean the source tree and remove binaries/objects.  
