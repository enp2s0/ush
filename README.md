# uSH: a small shell
## Written by Noah Brecht

*Pronounced micro-shell!*  

A micro-shell for the Linux OS. It supports I/O piping and has a few builtins. It is considerably smaller that bash, zsh, etc.
It also has no dependencies, making it extremely portable.  
  
The build process is extremely simple:    
Clean the source tree: `make clean`    
Compile uSH:           `make`    
Install:               `sudo make install`   
  
The Makefile installs uSH as /bin/ush by default. Change the value of $INSTALLDIR and $INSTBIN to change that location.  
  
# Syntax  
  
Run a single command:  
`:? <command> <arguments>`  
Pipe multiple commands together:  
`:? <command1> <arg1> | <command2> <arg2>`  
Run a system command with the same name as a builtin command:  
`:? <command>^ <arguments>`  
Variables can be used on the command line:  
`:? $I_Am_A_Command $I_Am_An_Argument`  
Variables can be assigned on the command line:  
`:? $var = value`  
