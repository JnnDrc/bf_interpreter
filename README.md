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

## Compile

There's two build modes:

- debug : for for testing features
- release : for release builds

just type make <build_mode> to compile
you can use clean-w or clean-u for cleanig the
object generated, -w stands for windows and -u for unix-like

if you want to make a build to distribute in the bin folder, i recommend
using release mode

## Repo contents

.\  
 | bf_programs\ : some example programs  
 | | bf_org : some example programs from brainfuck.org  
 | bin\ : binary files  
 | Makefile : GNU Make build tool  
 | README.md : this file  
 | bfi-g.exe : debug build for windows  
 | bfi.c : source code
