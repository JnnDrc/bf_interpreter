# BFI - BrainFuck Interpreter

bfi is simple interpreter for the brainfuck esolang,
if you don't know what brainfuck is, look [here](https://en.wikipedia.org/wiki/Brainfuck)

## Summary

1. [Use](#Use)
2. [Compile](#Compile)
3. [Repo Contentes](#repo-contents)

## Use

1. put the bin/\[your-architecture-here\]/ directory in your system path \(or
   you can use ./bfi/\[your-architecture-here\]/bfi\).  
   OBS: if your architecture isn't avaible, you can compile it yourself :),
   see the [Compile](#Compile) section.
2. type bfi followed by the brainfuck program you want to run and the optional
   params like this `bfi <bf_program> [--opt_params]`.
   to see the list of optional params, type `bfi --help`.

> pre built binaries might not be the most updated

## Compile

To compile you will need GNU Make and GCC.

```sh
git clone https://github.com/JnnDrc/bf_interpreter
cd bf_interpreter
make
```

if you want to use gdb, type `make debug` and use the 'bfi-g' executable

## Repo contents

.\  
 | bf_programs\ : some example programs  
 | | bf_org : some example programs from brainfuck.org  
 | bin\ : binary files  
 | Makefile : GNU Make build tool  
 | README.md : this file  
 | bfi-g.exe : debug build for windows  
 | bfi.c : source code
