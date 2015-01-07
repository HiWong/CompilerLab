#ifndef MYLANG_CONST_HPP
#define MYLANG_CONST_HPP

#include <string>

namespace mylang {

// type

class LangSpec {
private:
    inline LangSpec() = delete; // force static

    // virtual ~LangSpec() = delete;

public:
    using real = double;
    using integer = long;
    using byte = char;
};

// operators

const std::string name_assign = "__assign";
const std::string name_assign_add = "__assign_add";
const std::string name_assign_sub = "__assign_sub";
const std::string name_assign_mul = "__assign_mul";
const std::string name_assign_div = "__assign_div";

const std::string name_equal = "__equal";
const std::string name_less_equal = "__less_equal";
const std::string name_greater_equal = "__greater_equal";
const std::string name_not_equal = "__not_equal";
const std::string name_less = "__less";
const std::string name_greater = "__greater";
const std::string name_in = "__in";

const std::string name_add = "__add";
const std::string name_sub = "__sub";
const std::string name_or = "__or";
const std::string name_xor = "__xor";

const std::string name_mul = "__mul";
const std::string name_div = "__div";
const std::string name_mod = "__mod";
const std::string name_and = "__and";
const std::string name_shl = "__shl";
const std::string name_shr = "__shr";
const std::string name_rol = "__rol";
const std::string name_ror = "__ror";

const std::string name_pos = "__pos";
const std::string name_neg = "__neg";
const std::string name_not = "__not";

const std::string name_prev = "__prev";
const std::string name_next = "__next";

// builtin interfaces

const std::string name_list = "__list"; // arg: (...)
const std::string name_label = "__label"; // arg: (lbl)
const std::string name_goto = "__goto"; // arg: (lbl)
const std::string name_branch = "__branch"; // arg: (lbl, cond) // if !cond then goto(lbl)
const std::string name_call = "__call"; // arg: (obj)
const std::string name_self = "__self"; // arg: () // get self env

// builtin values

const std::string name_code = "__code";

const std::string name_base = "__base"; // extends
const std::string name_parent = "__parent"; // refers
const std::string name_input = "__input"; // receive // "left/get" call
const std::string name_result = "__result"; // return // "right/set" call

const std::string name_caller = "__caller";

const std::string name_void = "void";
const std::string name_real = "real";
const std::string name_integer = "integer";
const std::string name_cardinal = "cardinal";
const std::string name_byte = "byte";
const std::string name_string = "string";
const std::string name_typeid = "typeid";
const std::string name_array = "array"; // array of <integer> <expression>
const std::string name_pointer = "pointer"; // pointer of <expression>
const std::string name_link = "link"; // link of <expression>

}

#endif
