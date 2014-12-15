#ifndef MYLANG_ANALYSIS_HPP
#define MYLANG_ANALYSIS_HPP

#include "mylang_syntax_spec.hpp"
#include "semantic/block.hpp"

namespace myparser {

enum {
    PASS_ANALYSIS = PASS_USER
};

template <>
class Pass<PASS_ANALYSIS>: public PassProto<PASS_ANALYSIS> {
private:
    // in status
    libblock::Block *in_block;
    libblock::Name::Visibility *in_visibility;

    // out status
    enum ModeAssign {
        MA_E, MA_ADD, MA_SUB, MA_MUL, MA_DIV
    } *out_assign;
    enum ModeOperator {
        MO_E, MO_LE, MO_GE, MO_NE, MO_L, MO_G,
        MO_ADD, MO_SUB,
        MO_MUL, MO_DIV, MO_MOD
    } *out_operator;
    double *out_double;
    long *out_long;
    char *out_byte;
    std::string *out_string;
    libblock::Name *out_id;

    inline void go(const NodeList<> *node) {
        for (const Node<> *child: node->getChildren()) {
            child->runPass(this);
        }
    }

    inline void enterBlock() {
        libblock::Block *current = new libblock::Block(in_block);
        in_block->putChild(current);
        in_block = current;
    }

    inline void exitBlock() {
        in_block = in_block->getParent();
    }

public:
    inline Pass(libblock::Block &base): in_block{&base} {}

    // virtual ~Pass() {}

    #define MYLANG_ANALYSIS_LIST(name, namelen) \
        template <size_t I>\
        void run(const NodeTypedList<MP_STR(name, namelen), I> *node)

    #define MYLANG_ANALYSIS_TEXT(name, namelen) \
        template <class TX = void> /* actually not a template */\
        void run(const NodeTypedText<MP_STR(name, namelen)> *node)

    MYLANG_ANALYSIS_LIST("root", 4) {
        go(node);
    }

    MYLANG_ANALYSIS_LIST("main structure", 14) {
        go(node);
    }

    MYLANG_ANALYSIS_LIST("program", 7) {
        // TODO: proto?
        enterBlock();
        go(node);
        exitBlock();
    }

    MYLANG_ANALYSIS_LIST("function", 8) {
        // TODO: proto?
        enterBlock();
        go(node);
        exitBlock();
    }

    MYLANG_ANALYSIS_LIST("class", 5) {
        enterBlock();
        go(node);
        exitBlock();
    }

    MYLANG_ANALYSIS_LIST("end program", 11) {
        if (I == 0) {
            // TODO: check ID
            go(node);
        }
    }

    MYLANG_ANALYSIS_LIST("end function", 12) {
        if (I == 0) {
            // TODO: check ID
            go(node);
        }
    }

    MYLANG_ANALYSIS_LIST("main body", 9) {
        go(node);
    }

    MYLANG_ANALYSIS_LIST("public block", 12) {
        auto visibility = libblock::Name::V_PUBLIC;

        in_visibility = &visibility;
        // TODO: pass1 - create name; pass2 - compile
        go(node);
        in_visibility = nullptr;
    }

    MYLANG_ANALYSIS_LIST("private block", 13) {
        auto visibility = libblock::Name::V_PRIVATE;

        in_visibility = &visibility;
        // TODO: pass1 - create name; pass2 - compile
        go(node);
        in_visibility = nullptr;
    }

    MYLANG_ANALYSIS_LIST("code block", 10) {
        // TODO: entry = code_main
        go(node);
    }

    MYLANG_ANALYSIS_LIST("function proto", 14) {
        // TODO: get name & arg list
        go(node);
    }

    MYLANG_ANALYSIS_LIST("argument list", 13) {
        go(node);
    }

    MYLANG_ANALYSIS_LIST("argument", 8) {
        // TODO
    }

    MYLANG_ANALYSIS_LIST("definition list", 15) {
        go(node);
    }

    MYLANG_ANALYSIS_LIST("definition", 10) {
        go(node);
    }

    MYLANG_ANALYSIS_LIST("type definition", 15) {
        // TODO
    }

    MYLANG_ANALYSIS_LIST("field definition", 16) {
        // TODO
    }

    MYLANG_ANALYSIS_LIST("field deletion", 14) {
        // TODO: get id, delete
    }

    MYLANG_ANALYSIS_LIST("field type", 10) {
        // TODO
    }

    MYLANG_ANALYSIS_LIST("id bind", 7) {}

    MYLANG_ANALYSIS_LIST("default", 7) {}

    MYLANG_ANALYSIS_LIST("type", 4) {}

    MYLANG_ANALYSIS_LIST("type of", 7) {}

    MYLANG_ANALYSIS_LIST("statement list", 14) {}

    MYLANG_ANALYSIS_LIST("statement", 9) {}

    MYLANG_ANALYSIS_LIST("assignment", 10) {}

    MYLANG_ANALYSIS_TEXT("assign sign", 11) {}

    MYLANG_ANALYSIS_LIST("receive", 7) {}

    MYLANG_ANALYSIS_LIST("pause", 5) {}

    MYLANG_ANALYSIS_LIST("return", 6) {}

    MYLANG_ANALYSIS_LIST("structure", 9) {}

    MYLANG_ANALYSIS_LIST("if structure", 12) {}

    MYLANG_ANALYSIS_LIST("for structure", 13) {}

    MYLANG_ANALYSIS_LIST("foreach structure", 17) {}

    MYLANG_ANALYSIS_LIST("while structure", 15) {}

    MYLANG_ANALYSIS_LIST("condition chain", 15) {}

    MYLANG_ANALYSIS_LIST("to range", 8) {}

    MYLANG_ANALYSIS_LIST("repeat", 6) {}

    MYLANG_ANALYSIS_LIST("expression list", 15) {}

    MYLANG_ANALYSIS_LIST("expression", 10) {}

    MYLANG_ANALYSIS_LIST("relative expression", 19) {}

    MYLANG_ANALYSIS_LIST("relative operation", 18) {}

    MYLANG_ANALYSIS_LIST("additive expression", 19) {}

    MYLANG_ANALYSIS_LIST("additive operation", 18) {}

    MYLANG_ANALYSIS_LIST("multiplicative expression", 25) {}

    MYLANG_ANALYSIS_LIST("multiplicative operation", 24) {}

    MYLANG_ANALYSIS_LIST("unary expression", 16) {}

    MYLANG_ANALYSIS_LIST("access operation", 16) {}

    MYLANG_ANALYSIS_LIST("relation", 8) {}

    MYLANG_ANALYSIS_LIST("addition", 8) {}

    MYLANG_ANALYSIS_LIST("multiplication", 14) {}

    MYLANG_ANALYSIS_LIST("unary operator", 14) {}

    MYLANG_ANALYSIS_TEXT("comparison", 10) {}

    MYLANG_ANALYSIS_TEXT("addsub", 6) {}

    MYLANG_ANALYSIS_TEXT("muldivmod", 9) {}

    MYLANG_ANALYSIS_LIST("value list", 10) {}

    MYLANG_ANALYSIS_LIST("value", 5) {}

    MYLANG_ANALYSIS_LIST("literal", 7) {}

    MYLANG_ANALYSIS_TEXT("real", 4) {}

    MYLANG_ANALYSIS_TEXT("integer", 7) {}

    MYLANG_ANALYSIS_TEXT("byte", 4) {}

    MYLANG_ANALYSIS_TEXT("string", 6) {}

    MYLANG_ANALYSIS_LIST("instant array", 13) {}

    MYLANG_ANALYSIS_LIST("space", 5) {}

    MYLANG_ANALYSIS_LIST("keyword", 7) {}

    MYLANG_ANALYSIS_TEXT("id", 2) {}

    MYLANG_ANALYSIS_TEXT("reserved id", 11) {}

    MYLANG_ANALYSIS_TEXT("sign", 4) {}

    MYLANG_ANALYSIS_TEXT("ignored", 7) {}

    #undef MYLANG_ANALYSIS_LIST
    #undef MYLANG_ANALYSIS_TEXT

    // misc

    template <class NT, class KW>
    void run(const NodeTypedKeyword<NT, KW> *node) {
        // TODO: never reach
    }

    template <class NT, class E>
    void run(const NodeTypedError<NT, E> *node) {
        // TODO: never reach
    }

    void run(const Node<> *node) {
        // TODO: ???
    }
};

}

#endif
