#include "SemanticVisitor.h"
#include "SpirvAsmLexer.h"

using namespace SpirvAsm;
using namespace std;
using namespace antlr4;
using namespace antlr4::tree;

antlrcpp::Any SemanticVisitor::visitProgram(SpirvAsmParser::ProgramContext* context)
{
  cout << R"(<HTML><HEAD>
<style>
    body {
        font-family: 'Consolas', 'Monaco', 'Droid Sans Mono', monospace;
    }
    tr:hover {
        background-color: #f5f5f5;
    }
    td {
        vertical-align: top;
    }
    td:nth-child(2) {
        text-align: right;
    }
    .token_COMMENT {
        color: #008000;
    }
    .inline-pre {
        display: inline;
    }
</style>
<script>
    window.onload = function() {
        var elements = document.getElementsByTagName('span');

        // Simple hash function
        var hash = function(str) {
            var hash = 0;
            for (var i = 0; i < str.length; i++) {
                hash = ((hash << 5) - hash) + str.charCodeAt(i);
                hash |= 0; // Convert to 32bit integer
            }
            return hash;
        };

        // Function to convert a number to a color
        var numberToColor = function(hash) {
            var r = (hash & 0xFF0000) >> 16;
            var g = (hash & 0x00FF00) >> 8;
            var b = hash & 0x0000FF;
            return 'rgb(' + r + ',' + g + ',' + b + ')';
        };

        var toggleHighlight = function() {
            var className = this.className;
            var styleSheet = document.styleSheets[0];
            var ruleIndex = -1;

            // Check if the rule already exists
            for (var i = 0; i < styleSheet.cssRules.length; i++) {
                if (styleSheet.cssRules[i].selectorText === '.' + className) {
                    ruleIndex = i;
                    break;
                }
            }

            if (ruleIndex === -1) {
                // If the rule does not exist, add it
                var color = numberToColor(hash(className));
                styleSheet.insertRule('.' + className + ' { background-color: ' + color + '; }', styleSheet.cssRules.length);
            } else {
                // If the rule exists, remove it
                styleSheet.deleteRule(ruleIndex);
            }
        };

        for (var i = 0; i < elements.length; i++) {
            elements[i].addEventListener('click', toggleHighlight);
        }
    };
</script></HEAD>
<BODY><TABLE>)" << endl;
  auto result = visitChildren(context);
  cout << "</TABLE></BODY></HTML>" << endl;
  return result;
}

std::any SemanticVisitor::visitTerminal(TerminalNode *node)
{
  size_t symbolType = node->getSymbol()->getType();
  switch (symbolType)
  {
  case SpirvAsmLexer::ID:
    {
      string id = node->getText();
      cout << "<span class=\"id_" << (id.c_str() + 1) << "\">";
      cout << id;
      cout << "</span> ";
    }
    break;
  case SpirvAsmLexer::LITERAL:
    {
      string literal = node->getText();
      if (literal.find("\n") != string::npos) {
        cout << "<pre class=\"inline-pre\">";
        cout << literal;
        cout << "</pre> ";
      } else {
        cout << literal;
      }
    }
    break;
  case SpirvAsmLexer::COMMENT:
    cout << "<span class=\"token_COMMENT\">";
    cout << node->getText();
    cout << "</span> ";
    break;

  default:
    cout << node->getText() << " ";
  }
  return visitChildren(node);
}

antlrcpp::Any SemanticVisitor::visitInstruction(SpirvAsmParser::InstructionContext* context)
{
  cout << "<TR><TD>" << lineNumber << "</TD>";

  std::any result = defaultResult();

  size_t childIndex = 0;
  size_t childCount = context->children.size();

  if (childCount > 2) {
    ParseTree *c = context->children[1];
    if (TerminalNode *term = dynamic_cast<TerminalNode*>(c)) {
      if (Token *token = term->getSymbol()) {
        if (token->getType() == SpirvAsmLexer::EQUALS) {
          for (; childIndex < 2; ++childIndex) {
            cout << "<TD>";
            context->children[childIndex]->accept(this);
            cout << "</TD>";
          }
        }
      }
    }
  }

  if (childIndex == 2)
  {
    cout << "<TD>";
  } else
  {
    //cout << "<TD colspan=\"3\">";
    cout << "<TD></TD><TD></TD><TD>";
  }

  for (; childIndex < childCount; childIndex++) {
    if (!shouldVisitNextChild(context, result)) {
      break;
    }

    std::any childResult = context->children[childIndex]->accept(this);
    result = aggregateResult(std::move(result), std::move(childResult));
  }

  cout << "</TD></TR>" << endl;
  ++lineNumber;
  return result;
}

antlrcpp::Any SemanticVisitor::visitOperand(SpirvAsmParser::OperandContext* context)
{
  return visitChildren(context);
}

antlrcpp::Any SemanticVisitor::visitAddressing_model(SpirvAsmParser::Addressing_modelContext* context)
{
  return visitChildren(context);
}

antlrcpp::Any SemanticVisitor::visitCapability(SpirvAsmParser::CapabilityContext* context)
{
  return visitChildren(context);
}

antlrcpp::Any SemanticVisitor::visitDecoration(SpirvAsmParser::DecorationContext* context)
{
  return visitChildren(context);
}

antlrcpp::Any SemanticVisitor::visitExecution_mode(SpirvAsmParser::Execution_modeContext* context)
{
  return visitChildren(context);
}

antlrcpp::Any SemanticVisitor::visitExecution_model(SpirvAsmParser::Execution_modelContext* context)
{
  return visitChildren(context);
}

antlrcpp::Any SemanticVisitor::visitFunction_control(SpirvAsmParser::Function_controlContext *context) {
  return visitChildren(context);
}

antlrcpp::Any SemanticVisitor::visitMemory_model(SpirvAsmParser::Memory_modelContext* context)
{
  return visitChildren(context);
}

antlrcpp::Any SemanticVisitor::visitMemory_operands(SpirvAsmParser::Memory_operandsContext* context)
{
  return visitChildren(context);
}

antlrcpp::Any SemanticVisitor::visitStorage_class(SpirvAsmParser::Storage_classContext* context)
{
  return visitChildren(context);
}

