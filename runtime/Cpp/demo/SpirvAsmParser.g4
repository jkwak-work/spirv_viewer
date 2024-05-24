parser grammar SpirvAsmParser;

options {
    tokenVocab = SpirvAsmLexer;
}

// These are all supported parser sections:

// Parser file header. Appears at the top in all parser related files. Use e.g. for copyrights.
@parser::header {/* parser/listener/visitor header section */}

// Appears before any #include in h + cpp files.
@parser::preinclude {/* parser precinclude section */}

// Follows directly after the standard #includes in h + cpp files.
@parser::postinclude {
/* parser postinclude section */
#ifndef _WIN32
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
}

// Directly preceeds the parser class declaration in the h file (e.g. for additional types etc.).
@parser::context {/* parser context section */}

// Appears in the private part of the parser in the h file.
// The function bodies could also appear in the definitions section, but I want to maximize
// Java compatibility, so we can also create a Java parser from this grammar.
// Still, some tweaking is necessary after the Java file generation (e.g. bool -> boolean).
@parser::members {
/* public parser declarations/members section */
bool myAction() { return true; }
bool doesItBlend() { return true; }
void cleanUp() {}
void doInit() {}
void doAfter() {}
}

// Appears in the public part of the parser in the h file.
@parser::declarations {/* private parser declarations section */}

// Appears in line with the other class member definitions in the cpp file.
@parser::definitions {/* parser definitions section */}

// Additionally there are similar sections for (base)listener and (base)visitor files.
@parser::listenerpreinclude {/* listener preinclude section */}
@parser::listenerpostinclude {/* listener postinclude section */}
@parser::listenerdeclarations {/* listener public declarations/members section */}
@parser::listenermembers {/* listener private declarations/members section */}
@parser::listenerdefinitions {/* listener definitions section */}

@parser::baselistenerpreinclude {/* base listener preinclude section */}
@parser::baselistenerpostinclude {/* base listener postinclude section */}
@parser::baselistenerdeclarations {/* base listener public declarations/members section */}
@parser::baselistenermembers {/* base listener private declarations/members section */}
@parser::baselistenerdefinitions {/* base listener definitions section */}

@parser::visitorpreinclude {/* visitor preinclude section */}
@parser::visitorpostinclude {/* visitor postinclude section */}
@parser::visitordeclarations {/* visitor public declarations/members section */}
@parser::visitormembers {/* visitor private declarations/members section */}
@parser::visitordefinitions {/* visitor definitions section */}

@parser::basevisitorpreinclude {/* base visitor preinclude section */}
@parser::basevisitorpostinclude {/* base visitor postinclude section */}
@parser::basevisitordeclarations {/* base visitor public declarations/members section */}
@parser::basevisitormembers {/* base visitor private declarations/members section */}
@parser::basevisitordefinitions {/* base visitor definitions section */}

// Actual grammar start.
program: instruction* EOF;

addressing_model: ADDRESSING_MODEL
    ;

capability: CAPABILITY
    | CONFLICT_GEOMETRY
    | CONFLICT_KERNEL
    | CONFLICT_DENORM_PRESERVE
    | CONFLICT_DENORM_FLUSH_TO_ZERO
    | CONFLICT_SIGNED_ZERO_INF_NAN_PRESERVE
    | CONFLICT_ROUNDING_MODE_RTE
    | CONFLICT_ROUNDING_MODE_RTZ
    | CONFLICT_OPT_NONE_INTEL
    | CONFLICT_SHADER_INVOCATION_REORDER_NV
    | CONFLICT_CLIPDISTANCE
    | CONFLICT_CULLDISTANCE
    ;

decoration: DECORATION
    | CONFLICT_UNIFORM
    | CONFLICT_VOLATILE
    ;

decoration_builtin: DECORATION_BUILTIN
    | CONFLICT_CLIPDISTANCE
    | CONFLICT_CULLDISTANCE
    | CONFLICT_SUBGROUPSIZE
    | CONFLICT_SHADERINDEXAMDX
    ;

execution_mode: EXECUTION_MODE
    | CONFLICT_DENORM_PRESERVE
    | CONFLICT_DENORM_FLUSH_TO_ZERO
    | CONFLICT_SIGNED_ZERO_INF_NAN_PRESERVE
    | CONFLICT_ROUNDING_MODE_RTE
    | CONFLICT_ROUNDING_MODE_RTZ
    | CONFLICT_SUBGROUPSIZE
    | CONFLICT_SHADERINDEXAMDX
    ;

execution_model: EXECUTION_MODEL
    | CONFLICT_GEOMETRY
    | CONFLICT_KERNEL
    ;

function_control: FUNCTION_CONTROL
    | CONFLICT_NONE
    | CONFLICT_OPT_NONE_INTEL
    ;

memory_model: MEMORY_MODEL
    ;

memory_operands: MEMORY_OPERANDS
    | CONFLICT_NONE
    | CONFLICT_VOLATILE
    ;

storage_class: STORAGE_CLASS
    | CONFLICT_UNIFORM
    | CONFLICT_SHADER_INVOCATION_REORDER_NV
    ;

instruction: COMMENT
    | OP_RETURN
    | OP_FUNCTIONEND
    | (OP_CAPABILITY capability)
    | (OP_DECORATE ID CONFLICT_BUILTIN decoration_builtin)
    | (OP_DECORATE ID decoration LITERAL*)
    | (OP_ENTRYPOINT execution_model ID LITERAL ID*)
    | (OP_EXECUTIONMODE ID execution_mode LITERAL*)
    | (OP_EXTENSION LITERAL)
    | (OP_LINE ID LITERAL LITERAL)
    | (OP_MEMBERDECORATE ID LITERAL decoration LITERAL*)
    | (OP_MEMBERNAME ID LITERAL LITERAL)
    | (OP_MEMORYMODEL addressing_model memory_model)
    | (OP_NAME ID LITERAL COMMENT?)
    | (OP_SOURCE SOURCE_LANGUAGE LITERAL ID? LITERAL?)
    | (OP_SOURCEEXTENSION LITERAL)
    | (OP_STORE ID ID memory_operands?)
    | (OP_TYPEFORWARDPOINTER ID storage_class)
    | (ID EQUALS OP_TYPEPOINTER storage_class ID)
    | (ID EQUALS OP_VARIABLE ID storage_class ID?)
    | (ID EQUALS OP_EXTINST ID ID (LITERAL | DEBUGINFO_INSTRUCTION) ID*)
    | (ID EQUALS OP_FUNCTION ID function_control ID)
    | (ID EQUALS OP_LOAD ID ID memory_operands*)
    | (ID EQUALS OP_CODE operand*)
    ;

operand: ID | LITERAL;

