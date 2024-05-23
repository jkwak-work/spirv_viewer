/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */

//
//  main.cpp
//  antlr4-cpp-demo
//
//  Created by Mike Lischke on 13.03.16.
//
#include "SemanticVisitor.h"

#include <iostream>

#include "antlr4-runtime.h"
#include "SpirvAsmLexer.h"
#include "SpirvAsmParser.h"

#include <Windows.h>
#include <string>

#pragma execution_character_set("utf-8")

using namespace SpirvAsm;
using namespace antlr4;
using namespace std;

int main(int argc, const char * argv[]) {

  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <input-file>" << std::endl;
    return 1;
  }

  string path = argv[1];
  ANTLRFileStream input;
  input.loadFromFile(path);

  //ANTLRInputStream input("a = b + \"c\";(((x * d))) * e + f; a + (x * (y ? 0 : 1) + z);");
  SpirvAsmLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  SpirvAsmParser parser(&tokens);
  tree::ParseTree *tree = parser.program();

  SemanticVisitor semanticVisitor;
  semanticVisitor.visit(tree);

  return 0;
}
