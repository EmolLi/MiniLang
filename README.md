# MiniLang

A Mini language built with flex/bison. 

project structure:

* `programs`: Test programs, organized by compilation phase and by expected result. 
  * `Scan+parse`: Runs both the scanner and parser phases
  * `Typecheck`: Runs until the end of the typechecker phase
  * `Codegen`: Runs until the compiler outputs the target code (C)
* `src`: Source code for the compiler
* `build.sh`: build script for compiler.
* `run.sh`: Runs the compiler using two arguments (mode - $1 and input file - $2). You should replace the commands here if necessary to invoke your compiler
* `test.sh`: Automatically runs the compiler against test programs in the programs directory and checks the output

