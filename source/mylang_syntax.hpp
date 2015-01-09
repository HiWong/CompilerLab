// generated by MyParser C++ Code Generator

#ifndef MYLANG_SYNTAX_HPP
#define MYLANG_SYNTAX_HPP

#include "parser/myparser.hpp"

namespace myparser {

template<>
class RuleDef<MP_STR("root", 4)>:
public RuleList<MP_STR("root", 4),
    RuleLine<
        RuleItemSpace<>,
        RuleItemRef<MP_STR("program", 7)>,
        RuleItemSpace<>
    >
> {};

template<>
class RuleDef<MP_STR("program", 7)>:
public RuleList<MP_STR("program", 7),
    RuleLine<
        RuleItemKeyword<MP_STR("program", 7)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("proto", 5)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("main body", 9)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("end program", 11)>
    >
> {};

template<>
class RuleDef<MP_STR("function", 8)>:
public RuleList<MP_STR("function", 8),
    RuleLine<
        RuleItemKeyword<MP_STR("function", 8)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("proto", 5)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("main body", 9)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("end function", 12)>
    >
> {};

template<>
class RuleDef<MP_STR("class", 5)>:
public RuleList<MP_STR("class", 5),
    RuleLine<
        RuleItemKeyword<MP_STR("class", 5)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("argument tuple", 14)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("main body", 9)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR("end", 3)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR("class", 5)>
    >
> {};

template<>
class RuleDef<MP_STR("end program", 11)>:
public RuleList<MP_STR("end program", 11),
    RuleLine<
        RuleItemKeyword<MP_STR("end", 3)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR("program", 7)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("id", 2)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("end", 3)>
    >
> {};

template<>
class RuleDef<MP_STR("end function", 12)>:
public RuleList<MP_STR("end function", 12),
    RuleLine<
        RuleItemKeyword<MP_STR("end", 3)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR("function", 8)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("id", 2)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("end", 3)>
    >
> {};

template<>
class RuleDef<MP_STR("main body", 9)>:
public RuleList<MP_STR("main body", 9),
    RuleLine<
        RuleItemRef<MP_STR("public block", 12)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("private block", 13)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("code block", 10)>
    >
> {};

template<>
class RuleDef<MP_STR("public block", 12)>:
public RuleList<MP_STR("public block", 12),
    RuleLine<
        RuleItemRef<MP_STR("definition list", 15)>
    >
> {};

template<>
class RuleDef<MP_STR("private block", 13)>:
public RuleList<MP_STR("private block", 13),
    RuleLine<
        RuleItemKeyword<MP_STR("is", 2)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("definition list", 15)>
    >,
    RuleLine<
        
    >
> {};

template<>
class RuleDef<MP_STR("code block", 10)>:
public RuleList<MP_STR("code block", 10),
    RuleLine<
        RuleItemKeyword<MP_STR("begin", 5)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("statement list", 14)>
    >,
    RuleLine<
        
    >
> {};

template<>
class RuleDef<MP_STR("proto", 5)>:
public RuleList<MP_STR("proto", 5),
    RuleLine<
        RuleItemRef<MP_STR("id", 2)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("argument tuple", 14)>
    >
> {};

template<>
class RuleDef<MP_STR("argument tuple", 14)>:
public RuleList<MP_STR("argument tuple", 14),
    RuleLine<
        RuleItemKeyword<MP_STR("(", 1)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("argument list", 13)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR(")", 1)>
    >,
    RuleLine<
        
    >
> {};

template<>
class RuleDef<MP_STR("argument list", 13)>:
public RuleList<MP_STR("argument list", 13),
    RuleLine<
        RuleItemRef<MP_STR("argument", 8)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR(",", 1)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("argument list", 13)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("argument", 8)>
    >,
    RuleLine<
        
    >
> {};

template<>
class RuleDef<MP_STR("argument", 8)>:
public RuleList<MP_STR("argument", 8),
    RuleLine<
        RuleItemKeyword<MP_STR("type", 4)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("id", 2)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("in", 2)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("id", 2)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("out", 3)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("id", 2)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("var", 3)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("id", 2)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("id", 2)>
    >
> {};

template<>
class RuleDef<MP_STR("definition list", 15)>:
public RuleList<MP_STR("definition list", 15),
    RuleLine<
        RuleItemRef<MP_STR("definition", 10)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("definition list", 15)>
    >,
    RuleLine<
        
    >
> {};

template<>
class RuleDef<MP_STR("definition", 10)>:
public RuleList<MP_STR("definition", 10),
    RuleLine<
        RuleItemRef<MP_STR("field definition", 16)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("function", 8)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR(";", 1)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR(";", 1)>
    >
> {};

template<>
class RuleDef<MP_STR("field definition", 16)>:
public RuleList<MP_STR("field definition", 16),
    RuleLine<
        RuleItemKeyword<MP_STR("type", 4)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("field name", 10)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("expression", 10)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("expr", 4)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("field name", 10)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("expression", 10)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("var", 3)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("field name", 10)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("expression", 10)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("static", 6)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("field name", 10)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("expression", 10)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("fast", 4)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("field name", 10)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("expression", 10)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("field name", 10)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("expression", 10)>
    >
> {};

template<>
class RuleDef<MP_STR("field name", 10)>:
public RuleList<MP_STR("field name", 10),
    RuleLine<
        RuleItemKeyword<MP_STR("extends", 7)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("refers", 6)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("receive", 7)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("return", 6)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("id", 2)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR("imports", 7)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("id", 2)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR("is", 2)>
    >
> {};

template<>
class RuleDef<MP_STR("statement list", 14)>:
public RuleList<MP_STR("statement list", 14),
    RuleLine<
        RuleItemRef<MP_STR("statement", 9)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("statement list", 14)>
    >,
    RuleLine<
        
    >
> {};

template<>
class RuleDef<MP_STR("statement", 9)>:
public RuleList<MP_STR("statement", 9),
    RuleLine<
        RuleItemRef<MP_STR("expression", 10)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR(";", 1)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("jump", 4)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR(";", 1)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("structure", 9)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("repeat", 6)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR(";", 1)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR(";", 1)>
    >
> {};

template<>
class RuleDef<MP_STR("jump", 4)>:
public RuleList<MP_STR("jump", 4),
    RuleLine<
        RuleItemRef<MP_STR("receive", 7)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("restart", 7)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("return", 6)>
    >
> {};

template<>
class RuleDef<MP_STR("receive", 7)>:
public RuleList<MP_STR("receive", 7),
    RuleLine<
        RuleItemKeyword<MP_STR("receive", 7)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("expression", 10)>
    >
> {};

template<>
class RuleDef<MP_STR("restart", 7)>:
public RuleList<MP_STR("restart", 7),
    RuleLine<
        RuleItemKeyword<MP_STR("restart", 7)>
    >
> {};

template<>
class RuleDef<MP_STR("return", 6)>:
public RuleList<MP_STR("return", 6),
    RuleLine<
        RuleItemKeyword<MP_STR("return", 6)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("expression", 10)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("return", 6)>
    >
> {};

template<>
class RuleDef<MP_STR("structure", 9)>:
public RuleList<MP_STR("structure", 9),
    RuleLine<
        RuleItemRef<MP_STR("if structure", 12)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("for structure", 13)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("foreach structure", 17)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("while structure", 15)>
    >
> {};

template<>
class RuleDef<MP_STR("if structure", 12)>:
public RuleList<MP_STR("if structure", 12),
    RuleLine<
        RuleItemKeyword<MP_STR("if", 2)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("expression", 10)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR("then", 4)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("statement list", 14)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("condition chain", 15)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR("end", 3)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR("if", 2)>
    >
> {};

template<>
class RuleDef<MP_STR("for structure", 13)>:
public RuleList<MP_STR("for structure", 13),
    RuleLine<
        RuleItemKeyword<MP_STR("for", 3)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("id", 2)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR("in", 2)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("expression", 10)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("to step", 7)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("expression", 10)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR("do", 2)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("statement list", 14)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR("end", 3)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR("for", 3)>
    >
> {};

template<>
class RuleDef<MP_STR("foreach structure", 17)>:
public RuleList<MP_STR("foreach structure", 17),
    RuleLine<
        RuleItemKeyword<MP_STR("foreach", 7)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("id", 2)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR("in", 2)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("expression", 10)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR("do", 2)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("statement list", 14)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR("end", 3)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR("foreach", 7)>
    >
> {};

template<>
class RuleDef<MP_STR("while structure", 15)>:
public RuleList<MP_STR("while structure", 15),
    RuleLine<
        RuleItemKeyword<MP_STR("while", 5)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("expression", 10)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR("do", 2)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("statement list", 14)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR("end", 3)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR("while", 5)>
    >
> {};

template<>
class RuleDef<MP_STR("condition chain", 15)>:
public RuleList<MP_STR("condition chain", 15),
    RuleLine<
        RuleItemKeyword<MP_STR("elif", 4)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("expression", 10)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR("then", 4)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("statement list", 14)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("condition chain", 15)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("else", 4)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("statement list", 14)>
    >,
    RuleLine<
        
    >
> {};

template<>
class RuleDef<MP_STR("to step", 7)>:
public RuleList<MP_STR("to step", 7),
    RuleLine<
        RuleItemKeyword<MP_STR("to", 2)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("downto", 6)>
    >
> {};

template<>
class RuleDef<MP_STR("repeat", 6)>:
public RuleList<MP_STR("repeat", 6),
    RuleLine<
        RuleItemKeyword<MP_STR("repeat", 6)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("statement list", 14)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR("until", 5)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("expression", 10)>
    >
> {};

template<>
class RuleDef<MP_STR("expression list", 15)>:
public RuleList<MP_STR("expression list", 15),
    RuleLine<
        RuleItemRef<MP_STR("expression", 10)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR(",", 1)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("expression list", 15)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("expression", 10)>
    >,
    RuleLine<
        
    >
> {};

template<>
class RuleDef<MP_STR("expression", 10)>:
public RuleList<MP_STR("expression", 10),
    RuleLine<
        RuleItemRef<MP_STR("assign expression", 17)>
    >
> {};

template<>
class RuleDef<MP_STR("assign expression", 17)>:
public RuleList<MP_STR("assign expression", 17),
    RuleLine<
        RuleItemRef<MP_STR("relative expression", 19)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("assign operation", 16)>
    >
> {};

template<>
class RuleDef<MP_STR("assign operation", 16)>:
public RuleList<MP_STR("assign operation", 16),
    RuleLine<
        RuleItemRef<MP_STR("assignment", 10)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("assign expression", 17)>
    >,
    RuleLine<
        
    >
> {};

template<>
class RuleDef<MP_STR("relative expression", 19)>:
public RuleList<MP_STR("relative expression", 19),
    RuleLine<
        RuleItemRef<MP_STR("additive expression", 19)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("relative operation", 18)>
    >
> {};

template<>
class RuleDef<MP_STR("relative operation", 18)>:
public RuleList<MP_STR("relative operation", 18),
    RuleLine<
        RuleItemRef<MP_STR("relation", 8)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("additive expression", 19)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("relative operation", 18)>
    >,
    RuleLine<
        
    >
> {};

template<>
class RuleDef<MP_STR("additive expression", 19)>:
public RuleList<MP_STR("additive expression", 19),
    RuleLine<
        RuleItemRef<MP_STR("multiplicative expression", 25)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("additive operation", 18)>
    >
> {};

template<>
class RuleDef<MP_STR("additive operation", 18)>:
public RuleList<MP_STR("additive operation", 18),
    RuleLine<
        RuleItemRef<MP_STR("addition", 8)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("multiplicative expression", 25)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("additive operation", 18)>
    >,
    RuleLine<
        
    >
> {};

template<>
class RuleDef<MP_STR("multiplicative expression", 25)>:
public RuleList<MP_STR("multiplicative expression", 25),
    RuleLine<
        RuleItemRef<MP_STR("unary expression", 16)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("multiplicative operation", 24)>
    >
> {};

template<>
class RuleDef<MP_STR("multiplicative operation", 24)>:
public RuleList<MP_STR("multiplicative operation", 24),
    RuleLine<
        RuleItemRef<MP_STR("multiplication", 14)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("unary expression", 16)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("multiplicative operation", 24)>
    >,
    RuleLine<
        
    >
> {};

template<>
class RuleDef<MP_STR("unary expression", 16)>:
public RuleList<MP_STR("unary expression", 16),
    RuleLine<
        RuleItemRef<MP_STR("unary operator", 14)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("unary expression", 16)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("call expression", 15)>
    >
> {};

template<>
class RuleDef<MP_STR("call expression", 15)>:
public RuleList<MP_STR("call expression", 15),
    RuleLine<
        RuleItemRef<MP_STR("access expression", 17)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("call operation", 14)>
    >
> {};

template<>
class RuleDef<MP_STR("call operation", 14)>:
public RuleList<MP_STR("call operation", 14),
    RuleLine<
        RuleItemRef<MP_STR("call expression", 15)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("of", 2)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("call expression", 15)>
    >,
    RuleLine<
        
    >
> {};

template<>
class RuleDef<MP_STR("access expression", 17)>:
public RuleList<MP_STR("access expression", 17),
    RuleLine<
        RuleItemRef<MP_STR("value", 5)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("access operation", 16)>
    >
> {};

template<>
class RuleDef<MP_STR("access operation", 16)>:
public RuleList<MP_STR("access operation", 16),
    RuleLine<
        RuleItemKeyword<MP_STR(".", 1)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("value", 5)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("access operation", 16)>
    >,
    RuleLine<
        
    >
> {};

template<>
class RuleDef<MP_STR("assignment", 10)>:
public RuleList<MP_STR("assignment", 10),
    RuleLine<
        RuleItemKeyword<MP_STR(":=", 2)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("+=", 2)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("-=", 2)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("*=", 2)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("/=", 2)>
    >
> {};

template<>
class RuleDef<MP_STR("relation", 8)>:
public RuleList<MP_STR("relation", 8),
    RuleLine<
        RuleItemRef<MP_STR("comparison", 10)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("in", 2)>
    >
> {};

template<>
class RuleDef<MP_STR("addition", 8)>:
public RuleList<MP_STR("addition", 8),
    RuleLine<
        RuleItemRef<MP_STR("addsub", 6)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("or", 2)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("xor", 3)>
    >
> {};

template<>
class RuleDef<MP_STR("multiplication", 14)>:
public RuleList<MP_STR("multiplication", 14),
    RuleLine<
        RuleItemRef<MP_STR("muldivmod", 9)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("div", 3)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("mod", 3)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("and", 3)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("shl", 3)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("shr", 3)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("rol", 3)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("ror", 3)>
    >
> {};

template<>
class RuleDef<MP_STR("unary operator", 14)>:
public RuleList<MP_STR("unary operator", 14),
    RuleLine<
        RuleItemRef<MP_STR("addsub", 6)>
    >,
    RuleLine<
        RuleItemKeyword<MP_STR("not", 3)>
    >
> {};

template<>
class RuleDef<MP_STR("comparison", 10)>:
public RuleRegex<MP_STR("comparison", 10),
    MP_STR("==|<=|=<|>=|=>|!=|<|>", 21)
> {};

template<>
class RuleDef<MP_STR("addsub", 6)>:
public RuleRegex<MP_STR("addsub", 6),
    MP_STR("\\+|-", 4)
> {};

template<>
class RuleDef<MP_STR("muldivmod", 9)>:
public RuleRegex<MP_STR("muldivmod", 9),
    MP_STR("\\*|\\/|%", 7)
> {};

template<>
class RuleDef<MP_STR("value", 5)>:
public RuleList<MP_STR("value", 5),
    RuleLine<
        RuleItemRef<MP_STR("id", 2)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("real", 4)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("integer", 7)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("byte", 4)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("string", 6)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("tuple", 5)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("list", 4)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("class", 5)>
    >
> {};

template<>
class RuleDef<MP_STR("real", 4)>:
public RuleRegex<MP_STR("real", 4),
    MP_STR("[0-9]*\\.[0-9]+([Ee][\\+-]?[0-9]+)?", 33)
> {};

template<>
class RuleDef<MP_STR("integer", 7)>:
public RuleRegex<MP_STR("integer", 7),
    MP_STR("[0-9]+", 6)
> {};

template<>
class RuleDef<MP_STR("byte", 4)>:
public RuleRegex<MP_STR("byte", 4),
    MP_STR("\'([^\"\'\\\\]|\\\\[Xx][0-9A-Fa-f][0-9A-Fa-f]|\\\\[^Xx])\'", 48)
> {};

template<>
class RuleDef<MP_STR("string", 6)>:
public RuleRegex<MP_STR("string", 6),
    MP_STR("\"([^\"\'\\\\]|\\\\[Xx][0-9A-Fa-f][0-9A-Fa-f]|\\\\[^Xx])*\"", 49)
> {};

template<>
class RuleDef<MP_STR("tuple", 5)>:
public RuleList<MP_STR("tuple", 5),
    RuleLine<
        RuleItemKeyword<MP_STR("(", 1)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("expression list", 15)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR(")", 1)>
    >
> {};

template<>
class RuleDef<MP_STR("list", 4)>:
public RuleList<MP_STR("list", 4),
    RuleLine<
        RuleItemKeyword<MP_STR("[", 1)>,
        RuleItemSpace<>,
        RuleItemRef<MP_STR("expression list", 15)>,
        RuleItemSpace<>,
        RuleItemKeyword<MP_STR("]", 1)>
    >
> {};

template<>
class RuleDef<MP_STR("space", 5)>:
public RuleList<MP_STR("space", 5),
    RuleLine<
        RuleItemRef<MP_STR("ignored", 7)>
    >
> {};

template<>
class RuleDef<MP_STR("keyword", 7)>:
public RuleList<MP_STR("keyword", 7),
    RuleLine<
        RuleItemRef<MP_STR("reserved id", 11)>
    >,
    RuleLine<
        RuleItemRef<MP_STR("sign", 4)>
    >
> {};

template<>
class RuleDef<MP_STR("id", 2)>:
public RuleRegex<MP_STR("id", 2),
    MP_STR("[A-Za-z_][A-Za-z0-9_]*", 22)
> {};

template<>
class RuleDef<MP_STR("reserved id", 11)>:
public RuleRegex<MP_STR("reserved id", 11),
    MP_STR("[A-Za-z_][A-Za-z0-9_]*", 22)
> {};

template<>
class RuleDef<MP_STR("sign", 4)>:
public RuleRegex<MP_STR("sign", 4),
    MP_STR("[\\(\\)\\[\\],.;]|[\\:\\+\\-\\*\\/]\\=", 28)
> {};

template<>
class RuleDef<MP_STR("ignored", 7)>:
public RuleRegex<MP_STR("ignored", 7),
    MP_STR("(\\/\\/[^\\n]*|[ \\t\\r\\n])*", 23)
> {};


}

#endif
