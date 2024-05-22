#!/bin/bash
antlr4 -Dlanguage=Cpp -listener -visitor -o generated/ -package SpirvAsm SpirvAsmLexer.g4 SpirvAsmParser.g4
