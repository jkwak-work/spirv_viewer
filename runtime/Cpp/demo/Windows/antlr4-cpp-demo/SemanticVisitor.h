#pragma once
#include "SpirvAsmParserBaseVisitor.h"
using namespace SpirvAsm;

class SemanticVisitor : public SpirvAsmParserBaseVisitor {
  int lineNumber = 1;

public:
  virtual std::any visitTerminal(antlr4::tree::TerminalNode *node) override;
  virtual antlrcpp::Any visitProgram(SpirvAsmParser::ProgramContext *context) override;
  virtual antlrcpp::Any visitInstruction(SpirvAsmParser::InstructionContext *context) override;
  virtual antlrcpp::Any visitOperand(SpirvAsmParser::OperandContext *context) override;
  virtual antlrcpp::Any visitAddressing_model(SpirvAsmParser::Addressing_modelContext *context) override;
  virtual antlrcpp::Any visitCapability(SpirvAsmParser::CapabilityContext *context) override;
  virtual antlrcpp::Any visitDecoration(SpirvAsmParser::DecorationContext *context) override;
  virtual antlrcpp::Any visitExecution_mode(SpirvAsmParser::Execution_modeContext *context) override;
  virtual antlrcpp::Any visitExecution_model(SpirvAsmParser::Execution_modelContext *context) override;
  virtual antlrcpp::Any visitFunction_control(SpirvAsmParser::Function_controlContext *context) override;
  virtual antlrcpp::Any visitMemory_model(SpirvAsmParser::Memory_modelContext *context) override;
  virtual antlrcpp::Any visitMemory_operands(SpirvAsmParser::Memory_operandsContext *context) override;
  virtual antlrcpp::Any visitStorage_class(SpirvAsmParser::Storage_classContext *context) override;
};
