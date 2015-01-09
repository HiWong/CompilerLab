#ifndef MYLANG_ANALYSIS_PASS_HPP
#define MYLANG_ANALYSIS_PASS_HPP

#include "semantic/block.hpp"
#include "mylang_syntax_spec.hpp"
#include "mylang_analysis_call.hpp"

namespace myparser {

enum {
    PASS_ANALYSIS = PASS_USER
};

template <>
class Pass<PASS_ANALYSIS>: public PassProto<PASS_ANALYSIS> {
private:
    libblock::Block *nowenv;

    size_t unique;
    std::vector<size_t> id_begin;
    std::vector<size_t> id_end;

    inline size_t getUnique() {
        return unique++; // return then add
    }

    inline void enterZone() {
        id_begin.push_back(getUnique());
        id_end.push_back(getUnique());
    }

    inline void leaveZone() {
        id_begin.pop_back();
        id_end.pop_back();
    }

    inline void go(const NodeList<> *node) {
        for (const Node<> *child: node->getChildren()) {
            child->runPass(this);
        }
    }

    using NodeIter = std::vector<Node<> *>::const_iterator;

    inline NodeIter scanBegin(const NodeList<> *node) {
        return node->getChildren().cbegin();
    }

    template <class T>
    inline void scanFill(NodeIter &iter, T &target) {
        for (; !target; ++iter) {
            (*iter)->runPass(this);
        }
    }

    template <class T>
    static inline libblock::Code *makeGet(T name) {
        return new libblock::CodeGet(
            libblock::name_t(std::forward<T>(name))
        );
    }

    template <class T>
    static inline libblock::Code *makeCall(
        T name,
        libblock::Code *arg
    ) {
        return new libblock::CodeCall(
            makeGet(std::forward<T>(name)), arg, true
        );
    }

    template <class T>
    static inline libblock::Code *makeCall2(
        T name,
        libblock::Code *left,
        libblock::Code *right
    ) {
        if (!left || !right) {
            throw libblock::error_t("tuple is not allowed in binary-operator");
        } else if (left->getNext() || right->getNext()) {
            throw libblock::error_t("tuple is not allowed in binary-operator");
        } else {
            return makeCall(
                std::forward<T>(name),
                libblock::Code::pack(left, right)
            );
        }
    }

    template <class... ARG>
    static inline libblock::Code *makeChain(
        libblock::Code *first,
        ARG... rest
    ) {
        return libblock::Code::pack(
            first,
            makeChain(rest...)
        );
    }

    template <std::nullptr_t P = nullptr> // iteration finished
    static inline libblock::Code *makeChain() {
        return nullptr;
    }

    static inline libblock::Code *makeCallLocate(
        size_t id
    ) {
        return makeCall(
            mylang::name_locate,
            new libblock::CodeLabel(id)
        );
    }

    static inline libblock::Code *makeCallGoto(
        size_t id
    ) {
        return makeCall(
            mylang::name_goto,
            new libblock::CodeLabel(id)
        );
    }

    static inline libblock::Code *makeCallBranch(
        size_t id, libblock::Code *cond
    ) {
        return makeCall(
            mylang::name_branch,
            makeChain(
                new libblock::CodeLabel(id),
                cond
            )
        );
    }

    static inline libblock::Block *makeBlock() {
        libblock::Block *inner = new libblock::Block();

        return inner;
    }

    static inline void finishBlock(libblock::Block *inner) {
        // add parent (ref by default)
        // TODO: add __parent to proto
        // TODO: bind parent if __parent is at the first of arguments
        // auto query = nowenv->queryAll(mylang::name_parent);
        // if (query.first == query.second) {
        //     // if __parent not defined
        //     nowenv->addField(libblock::field_t(
        //         libblock::field_t::M_VAR, true, false,
        //         libblock::name_t(mylang::name_parent),
        //         new libblock::CodeCall(
        //             makeGet(mylang::name_link),
        //             makeGet(mylang::name_parent),
        //             false
        //         )
        //     ));
        // }

        inner->finish();
    }

public:
    inline Pass(libblock::Block *env): nowenv(env), unique(0) {}

    // virtual ~Pass() {}

    using IdCall =
        mylang::DelayedCall<libblock::name_t ()>;
    using IdCheckCall =
        mylang::DelayedCall<void (libblock::name_t &)>;
    using BodyCall =
        mylang::DelayedCall<void ()>;
    using FieldCall =
        mylang::DelayedCall<std::pair<
            libblock::name_t, bool
        > ()>;
    using DefinitionCall =
        mylang::DelayedCall<void (bool)>;
    using ExpressionCall =
        mylang::DelayedCall<libblock::Code * ()>;
    using OperationCall =
        mylang::DelayedCall<libblock::Code * (libblock::Code *)>;

    #define MYLANG_ANALYSIS_LIST(name, namelen) \
        template <size_t I>\
        void run(const NodeTypedList<MP_STR(name, namelen), I> *node)

    #define MYLANG_ANALYSIS_TEXT(name, namelen) \
        template <class TX = void> /* actually not a template */\
        void run(const NodeTypedText<MP_STR(name, namelen)> *node)

    MYLANG_ANALYSIS_LIST("root", 4) {
        DefinitionCall def;
        go(node);

        def(true); // notice: modules are public by default
    }

    MYLANG_ANALYSIS_LIST("program", 7) {
        DefinitionCall::put([=](bool hidden) {
            // new block
            libblock::Block *inner = makeBlock();

            IdCall id;
            BodyCall body;
            IdCheckCall checking;

            // analysis AST with a new Pass object
            Pass<PASS_ANALYSIS> pass(inner);
            pass.go(node);

            libblock::name_t name = id();
            body();
            checking(name);

            finishBlock(inner);

            nowenv->addField(libblock::field_t(
                libblock::field_t::M_TYPE, false, hidden,
                std::move(name),
                new libblock::CodeBlock(inner, true)
            ));
        });
    }

    MYLANG_ANALYSIS_LIST("function", 8) {
        DefinitionCall::put([=](bool hidden) {
            // new block
            libblock::Block *inner = makeBlock();

            IdCall id;
            BodyCall body;
            IdCheckCall checking;

            // analysis AST with a new Pass object
            Pass<PASS_ANALYSIS> pass(inner);
            pass.go(node);

            libblock::name_t name = id();
            body();
            checking(name);

            finishBlock(inner);

            nowenv->addField(libblock::field_t(
                libblock::field_t::M_TYPE, false, hidden,
                std::move(name),
                new libblock::CodeBlock(inner, true)
            ));
        });
    }

    MYLANG_ANALYSIS_LIST("class", 5) {
        go(node);
    }

    MYLANG_ANALYSIS_LIST("end program", 11) {
        IdCheckCall::put([=](libblock::name_t &name) {
            if (I == 0) {
                IdCall chk;
                go(node);

                if (name.id != chk().id) {
                    throw libblock::error_t("bad program id");
                }
            } else {
                // nothing
            }
        });
    }

    MYLANG_ANALYSIS_LIST("end function", 12) {
        IdCheckCall::put([=](libblock::name_t &name) {
            if (I == 0) {
                IdCall chk;
                go(node);

                if (name.id != chk().id) {
                    throw libblock::error_t("bad function id");
                }
            } else {
                // nothing
            }
        });
    }

    MYLANG_ANALYSIS_LIST("main body", 9) {
        BodyCall::put([=]() {
            go(node);
        });
    }

    MYLANG_ANALYSIS_LIST("public block", 12) {
        // no delayed call
        DefinitionCall def;
        go(node);

        def(true);
    }

    MYLANG_ANALYSIS_LIST("private block", 13) {
        if (I == 0) {
            // no delayed call

            DefinitionCall def;
            go(node);

            def(false);
        } else {
            // nothing
        }
    }

    MYLANG_ANALYSIS_LIST("code block", 10) {
        if (I == 0) {
            // no delayed call

            ExpressionCall body;
            go(node);

            enterZone();

            libblock::Code *begin = makeCallLocate(id_begin.front());
            libblock::Code *end = makeCallLocate(id_end.front());

            nowenv->addField(libblock::field_t(
                libblock::field_t::M_EXPR, false, true,
                libblock::name_t(mylang::name_code),
                makeChain(
                    begin, body(), end
                )
            ));

            leaveZone();
        } else {
            // nothing
        }
    }

    MYLANG_ANALYSIS_LIST("proto", 5) {
        IdCall::put([=]() {
            IdCall id;
            go(node);

            return id();
        });
    }

    MYLANG_ANALYSIS_LIST("argument tuple", 14) {
        go(node);
    }

    MYLANG_ANALYSIS_LIST("argument list", 13) {
        go(node);
    }

    MYLANG_ANALYSIS_LIST("argument", 8) {
        IdCall id;
        go(node);

        // assert I < 4
        libblock::argument_t::Mode mode[] = {
            libblock::argument_t::M_TYPE,
            libblock::argument_t::M_IN,
            libblock::argument_t::M_OUT,
            libblock::argument_t::M_VAR,
            libblock::argument_t::M_IN
        };

        nowenv->addArgument(libblock::argument_t(mode[I], id()));
    }

    MYLANG_ANALYSIS_LIST("definition list", 15) {
        DefinitionCall::put([=](bool hidden) {
            if (I == 0) {
                // member:
                DefinitionCall left;
                node->getChildren().front()->runPass(this);

                // next:
                DefinitionCall right;
                node->getChildren().back()->runPass(this);

                left(hidden);
                right(hidden);
            } else {
                // nothing
            }
        });
    }

    MYLANG_ANALYSIS_LIST("definition", 10) {
        if (I != 2) {
            go(node); // no delayed call
        } else {
            DefinitionCall::put([=](bool hidden) {
                (void) hidden;

                return;
            });
        }
    }

    MYLANG_ANALYSIS_LIST("field definition", 16) {
        DefinitionCall::put([=](bool hidden) {
            FieldCall info;
            ExpressionCall body;
            go(node);

            std::pair<libblock::name_t, bool> infopair = info();

            // assert I < 6
            libblock::field_t::Mode mode[] = {
                libblock::field_t::M_TYPE,
                libblock::field_t::M_EXPR,
                libblock::field_t::M_VAR,
                libblock::field_t::M_STATIC,
                libblock::field_t::M_FAST,
                libblock::field_t::M_VAR
            };

            nowenv->addField(libblock::field_t(
                mode[I], infopair.second, hidden,
                std::move(infopair.first), body()
            ));
        });
    }

    MYLANG_ANALYSIS_LIST("field name", 10) {
        FieldCall::put([=]() -> std::pair<
            libblock::name_t, bool
        > {
            switch (I) {
            case 0:
                // extends
                return {mylang::name_base, true};
            case 1:
                // refers
                return {mylang::name_parent, true};
            case 2:
                // receive
                return {mylang::name_input, false};
            case 3:
                // return
                return {mylang::name_result, false};
            case 4:
                // <id> imports
                {
                    IdCall id;
                    go(node);

                    return {id(), true};
                }
            case 5:
                // <id> is
                {
                    IdCall id;
                    go(node);

                    return {id(), false};
                }
            default:
                // never reach
                throw libblock::error_t("internal error");
            }
        });
    }

    MYLANG_ANALYSIS_LIST("statement list", 14) {
        ExpressionCall::put([=]() -> libblock::Code * {
            if (I == 0) {
                // member:
                ExpressionCall left;
                node->getChildren().front()->runPass(this);

                // next:
                ExpressionCall right;
                node->getChildren().back()->runPass(this);

                return makeChain(left(), right());
            } else {
                return nullptr;
            }
        });
    }

    MYLANG_ANALYSIS_LIST("statement", 9) {
        if (I != 4) {
            go(node); // no delayed call
        } else {
            ExpressionCall::put([=]() -> libblock::Code * {
                return nullptr;
            });
        }
    }

    MYLANG_ANALYSIS_LIST("jump", 4) {
        go(node);
    }

    MYLANG_ANALYSIS_LIST("receive", 7) {
        ExpressionCall::put([=]() -> libblock::Code * {
            ExpressionCall left;
            go(node);

            return makeCall2(
                mylang::name_assign,
                left(),
                makeGet(mylang::name_input)
            );
        });
    }

    MYLANG_ANALYSIS_LIST("restart", 7) {
        ExpressionCall::put([=]() -> libblock::Code * {
            (void) node;

            return makeCallGoto(id_begin.front());
        });
    }

    MYLANG_ANALYSIS_LIST("return", 6) {
        ExpressionCall::put([=]() -> libblock::Code * {
            if (I == 0) {
                ExpressionCall right;
                go(node);

                return makeChain(
                    makeCall2(
                        mylang::name_assign,
                        makeGet(mylang::name_result),
                        right()
                    ),
                    makeCallGoto(id_end.front())
                );
            } else {
                return makeCallGoto(id_end.front());
            }
        });
    }

    MYLANG_ANALYSIS_LIST("structure", 9) {
        go(node);
    }

    MYLANG_ANALYSIS_LIST("if structure", 12) {
        ExpressionCall::put([=]() -> libblock::Code * {
            NodeIter iter = scanBegin(node);

            ExpressionCall cond;
            scanFill(iter, cond);

            ExpressionCall body1;
            scanFill(iter, body1);

            ExpressionCall body2;
            scanFill(iter, body2);

            size_t id_local_mid = getUnique();
            size_t id_local_end = getUnique();

            libblock::Code *mid = makeCallLocate(id_local_mid);
            libblock::Code *end = makeCallLocate(id_local_end);

            libblock::Code *jump = makeCallBranch(id_local_mid, cond());
            libblock::Code *fin = makeCallGoto(id_local_end);

            libblock::Code *all = makeChain(
                jump,
                    body1(), fin,
                mid,
                    body2(),
                end
            );

            return all;
        });
    }

    MYLANG_ANALYSIS_LIST("for structure", 13) {
        ExpressionCall::put([=]() -> libblock::Code * {
            // notice: need debug!!!

            NodeIter iter = scanBegin(node);

            IdCall target;
            scanFill(iter, target);

            ExpressionCall initval;
            scanFill(iter, initval);

            IdCall step;
            scanFill(iter, step);

            ExpressionCall finval;
            scanFill(iter, finval);

            ExpressionCall body;
            scanFill(iter, body);

            enterZone();

            libblock::name_t targetname = target();

            libblock::Code *init = makeCall2(
                mylang::name_assign, makeGet(targetname), initval()
            );

            libblock::Code *cond = makeCall2(
                mylang::name_not_equal, makeGet(targetname), finval()
            );

            libblock::Code *dostep = makeCall(
                step(), makeGet(targetname)
            );

            libblock::Code *begin = makeCallLocate(id_begin.back());
            libblock::Code *end = makeCallLocate(id_end.back());

            libblock::Code *jump = makeCallBranch(id_end.back(), cond);
            libblock::Code *loop = makeCallGoto(id_begin.back());

            libblock::Code *all = makeChain(
                init,
                begin, jump,
                    body(), dostep, loop,
                end
            );

            leaveZone();

            return all;
        });
    }

    MYLANG_ANALYSIS_LIST("foreach structure", 17) {
        ExpressionCall::put([=]() -> libblock::Code * {
            // TODO
            (void) node;
            return nullptr;
        });
    }

    MYLANG_ANALYSIS_LIST("while structure", 15) {
        ExpressionCall::put([=]() -> libblock::Code * {
            NodeIter iter = scanBegin(node);

            ExpressionCall cond;
            scanFill(iter, cond);

            ExpressionCall body;
            scanFill(iter, body);

            enterZone();

            libblock::Code *begin = makeCallLocate(id_begin.back());
            libblock::Code *end = makeCallLocate(id_end.back());

            libblock::Code *jump = makeCallBranch(id_end.back(), cond());
            libblock::Code *loop = makeCallGoto(id_begin.back());

            libblock::Code *all = makeChain(
                begin, jump,
                    body(), loop,
                end
            );

            leaveZone();

            return all;
        });
    }

    MYLANG_ANALYSIS_LIST("condition chain", 15) {
        if (I == 0) {
            // the same as <if>
            ExpressionCall::put([=]() -> libblock::Code * {
                NodeIter iter = scanBegin(node);

                ExpressionCall cond;
                scanFill(iter, cond);

                ExpressionCall body1;
                scanFill(iter, body1);

                ExpressionCall body2;
                scanFill(iter, body2);

                size_t id_local_mid = getUnique();
                size_t id_local_end = getUnique();

                libblock::Code *mid = makeCallLocate(id_local_mid);
                libblock::Code *end = makeCallLocate(id_local_end);

                libblock::Code *jump = makeCallBranch(id_local_mid, cond());
                libblock::Code *fin = makeCallGoto(id_local_end);

                return makeChain(
                    jump,
                        body1(), fin,
                    mid,
                        body2(),
                    end
                );
            });
        } else if (I == 1) {
            go(node); // call the only member // no delayed call
        } else {
            ExpressionCall::put([=]() -> libblock::Code * {
                return nullptr;
            });
        }
    }

    MYLANG_ANALYSIS_LIST("to step", 7) {
        (void) node;

        IdCall::put([=]() {
            if (I == 0) {
                // to
                return libblock::name_t(mylang::name_next);
            } else {
                // downto
                return libblock::name_t(mylang::name_prev);
            }
        });
    }

    MYLANG_ANALYSIS_LIST("repeat", 6) {
        ExpressionCall::put([=]() -> libblock::Code * {
            NodeIter iter = scanBegin(node);

            ExpressionCall body;
            scanFill(iter, body);

            ExpressionCall cond;
            scanFill(iter, cond);

            enterZone();

            libblock::Code *begin = makeCallLocate(id_begin.back());
            libblock::Code *end = makeCallLocate(id_end.back());

            libblock::Code *jump = makeCallBranch(id_begin.back(), cond());

            libblock::Code *all = makeChain(begin, body(), jump, end);

            leaveZone();

            return all;
        });
    }

    MYLANG_ANALYSIS_LIST("expression list", 15) {
        ExpressionCall::put([=]() -> libblock::Code * {
            if (I == 0) {
                // member:
                ExpressionCall left;
                node->getChildren().front()->runPass(this);

                // next:
                ExpressionCall right;
                node->getChildren().back()->runPass(this);

                return makeChain(left(), right());
            } else if (I == 1) {
                // member:
                ExpressionCall left;
                node->getChildren().front()->runPass(this);

                return left();
            } else {
                return nullptr;
            }
        });
    }

    MYLANG_ANALYSIS_LIST("expression", 10) {
        go(node);
    }

    MYLANG_ANALYSIS_LIST("assign expression", 17) {
        ExpressionCall::put([=]() -> libblock::Code * {
            ExpressionCall left;
            OperationCall root;
            go(node);

            return root(left());
        });
    }

    MYLANG_ANALYSIS_LIST("assign operation", 16) {
        OperationCall::put([=](libblock::Code *left) -> libblock::Code * {
            if (I == 0) {
                IdCall op;
                ExpressionCall right;
                go(node);

                return makeCall2(
                    op(),
                    left,
                    right()
                );
            } else {
                return left;
            }
        });
    }

    MYLANG_ANALYSIS_LIST("relative expression", 19) {
        ExpressionCall::put([=]() -> libblock::Code * {
            ExpressionCall left;
            OperationCall root;
            go(node);

            return root(left());
        });
    }

    MYLANG_ANALYSIS_LIST("relative operation", 18) {
        OperationCall::put([=](libblock::Code *left) -> libblock::Code * {
            if (I == 0) {
                IdCall op;
                ExpressionCall right;
                OperationCall next;
                go(node);

                return next(makeCall2(
                    op(),
                    left,
                    right()
                ));
            } else {
                return left;
            }
        });
    }

    MYLANG_ANALYSIS_LIST("additive expression", 19) {
        ExpressionCall::put([=]() -> libblock::Code * {
            ExpressionCall left;
            OperationCall root;
            go(node);

            return root(left());
        });
    }

    MYLANG_ANALYSIS_LIST("additive operation", 18) {
        OperationCall::put([=](libblock::Code *left) -> libblock::Code * {
            if (I == 0) {
                IdCall op;
                ExpressionCall right;
                OperationCall next;
                go(node);

                return next(makeCall2(
                    op(),
                    left,
                    right()
                ));
            } else {
                return left;
            }
        });
    }

    MYLANG_ANALYSIS_LIST("multiplicative expression", 25) {
        ExpressionCall::put([=]() -> libblock::Code * {
            ExpressionCall left;
            OperationCall root;
            go(node);

            return root(left());
        });
    }

    MYLANG_ANALYSIS_LIST("multiplicative operation", 24) {
        OperationCall::put([=](libblock::Code *left) -> libblock::Code * {
            if (I == 0) {
                IdCall op;
                ExpressionCall right;
                OperationCall next;
                go(node);

                return next(makeCall2(
                    op(),
                    left,
                    right()
                ));
            } else {
                return left;
            }
        });
    }

    MYLANG_ANALYSIS_LIST("unary expression", 16) {
        if (I == 0) {
            ExpressionCall::put([=]() -> libblock::Code * {
                IdCall op;
                ExpressionCall right;
                go(node);

                return makeCall(
                    op(),
                    right()
                );
            });
        } else {
            go(node); // no delayed call
        }
    }

    MYLANG_ANALYSIS_LIST("call expression", 15) {
        ExpressionCall::put([=]() -> libblock::Code * {
            ExpressionCall left;
            OperationCall root;
            go(node);

            return root(left());
        });
    }

    MYLANG_ANALYSIS_LIST("call operation", 14) {
        OperationCall::put([=](libblock::Code *left) -> libblock::Code * {
            if (I == 0) {
                ExpressionCall right;
                go(node);

                return new libblock::CodeCall(left, right(), true);
            } else if (I == 1) {
                ExpressionCall right;
                go(node);

                return new libblock::CodeCall(left, right(), false);
            } else {
                return left;
            }
        });
    }

    MYLANG_ANALYSIS_LIST("access expression", 17) {
        ExpressionCall::put([=]() -> libblock::Code * {
            ExpressionCall left;
            OperationCall root;
            go(node);

            return root(left());
        });
    }

    MYLANG_ANALYSIS_LIST("access operation", 16) {
        OperationCall::put([=](libblock::Code *left) -> libblock::Code * {
            if (I == 0) {
                ExpressionCall right;
                OperationCall next;
                go(node);

                return next(new libblock::CodeWith(left, right()));
            } else {
                return left;
            }
        });
    }

    MYLANG_ANALYSIS_LIST("assignment", 10) {
        IdCall::put([=]() {
            static const std::map<const std::string, const std::string> table = {
                {":=", mylang::name_assign},
                {"+=", mylang::name_assign_add},
                {"-=", mylang::name_assign_sub},
                {"*=", mylang::name_assign_mul},
                {"/=", mylang::name_assign_div}
            };

            return libblock::name_t(table.find(node->getFullText())->second);
        });
    }

    MYLANG_ANALYSIS_LIST("relation", 8) {
        IdCall::put([=]() {
            static const std::map<const std::string, const std::string> table = {
                {"==", mylang::name_equal},
                {"<=", mylang::name_less_equal},
                {"=<", mylang::name_less_equal},
                {">=", mylang::name_greater_equal},
                {"=>", mylang::name_greater_equal},
                {"!=", mylang::name_not_equal},
                {"<", mylang::name_less},
                {">", mylang::name_greater},
                {"in", mylang::name_in}
            };

            return libblock::name_t(table.find(node->getFullText())->second);
        });
    }

    MYLANG_ANALYSIS_LIST("addition", 8) {
        IdCall::put([=]() {
            static const std::map<const std::string, const std::string> table = {
                {"+", mylang::name_add},
                {"-", mylang::name_sub},
                {"or", mylang::name_or},
                {"xor", mylang::name_xor}
            };

            return libblock::name_t(table.find(node->getFullText())->second);
        });
    }

    MYLANG_ANALYSIS_LIST("multiplication", 14) {
        IdCall::put([=]() {
            static const std::map<const std::string, const std::string> table = {
                {"*", mylang::name_mul},
                {"/", mylang::name_div},
                {"%", mylang::name_mod},
                {"div", mylang::name_div},
                {"mod", mylang::name_mod},
                {"and", mylang::name_and},
                {"shl", mylang::name_shl},
                {"shr", mylang::name_shr},
                {"rol", mylang::name_rol},
                {"ror", mylang::name_ror}
            };

            return libblock::name_t(table.find(node->getFullText())->second);
        });
    }

    MYLANG_ANALYSIS_LIST("unary operator", 14) {
        IdCall::put([=]() {
            static const std::map<const std::string, const std::string> table = {
                {"+", mylang::name_pos},
                {"-", mylang::name_neg},
                {"not", mylang::name_not}
            };

            return libblock::name_t(table.find(node->getFullText())->second);
        });
    }

    MYLANG_ANALYSIS_TEXT("comparison", 10) {
        (void) node; // see parent list
    }

    MYLANG_ANALYSIS_TEXT("addsub", 6) {
        (void) node; // see parent list
    }

    MYLANG_ANALYSIS_TEXT("muldivmod", 9) {
        (void) node; // see parent list
    }

    MYLANG_ANALYSIS_LIST("value", 5) {
        ExpressionCall::put([=]() -> libblock::Code * {
            switch (I) {
            case 0:
                // <id>
                {
                    IdCall value;
                    go(node);

                    return new libblock::CodeGet(value());
                }
            case 1:
                // <real>
                {
                    mylang::DelayedCall<mylang::LangSpec::real ()> value;
                    go(node);

                    return new libblock::CodeLiteral<mylang::LangSpec::real>(value());
                }
            case 2:
                // <integer>
                {
                    mylang::DelayedCall<mylang::LangSpec::integer ()> value;
                    go(node);

                    return new libblock::CodeLiteral<mylang::LangSpec::integer>(value());
                }
            case 3:
                // <byte>
                {
                    mylang::DelayedCall<mylang::LangSpec::byte ()> value;
                    go(node);

                    return new libblock::CodeLiteral<mylang::LangSpec::byte>(value());
                }
            case 4:
                // <string>
                {
                    mylang::DelayedCall<std::string ()> value;
                    go(node);

                    libblock::Code *arg = nullptr;
                    const std::string data = value();

                    for (auto iter = data.rbegin(); iter != data.rend(); ++iter) {
                        libblock::Code *prev =
                            new libblock::CodeLiteral<mylang::LangSpec::byte>(
                                mylang::LangSpec::byte(*iter)
                            );

                        arg = makeChain(prev, arg);
                    }

                    return makeCall(
                        mylang::name_list,
                        arg
                    );
                }
            case 5:
                // <tuple>
                {
                    ExpressionCall tuple;
                    go(node);

                    // tuple is always inline
                    return tuple();
                }
            case 6:
                // <list>
                {
                    ExpressionCall tuple;
                    go(node);

                    return makeCall(
                        mylang::name_list,
                        tuple()
                    );
                }
            case 7:
                // <class>
                {
                    // new block
                    libblock::Block *inner = makeBlock();

                    BodyCall body;

                    // analysis AST with a new Pass object
                    Pass<PASS_ANALYSIS> pass(inner);
                    pass.go(node);

                    body();

                    finishBlock(inner);

                    return new libblock::CodeBlock(inner, true);
                }
            default:
                // never reach
                throw libblock::error_t("internal error");
            }
        });
    }

    MYLANG_ANALYSIS_TEXT("real", 4) {
        mylang::DelayedCall<mylang::LangSpec::real ()>::put([=]() {
            return node->getData();
        });
    }

    MYLANG_ANALYSIS_TEXT("integer", 7) {
        mylang::DelayedCall<mylang::LangSpec::integer ()>::put([=]() {
            return node->getData();
        });
    }

    MYLANG_ANALYSIS_TEXT("byte", 4) {
        mylang::DelayedCall<mylang::LangSpec::byte ()>::put([=]() {
            return node->getRaw()[0];
        });
    }

    MYLANG_ANALYSIS_TEXT("string", 6) {
        mylang::DelayedCall<std::string ()>::put([=]() {
            return node->getRaw();
        });
    }

    MYLANG_ANALYSIS_LIST("tuple", 5) {
        go(node);
    }

    MYLANG_ANALYSIS_LIST("list", 4) {
        go(node);
    }

    MYLANG_ANALYSIS_LIST("space", 5) {
        // skip
        (void) node;
    }

    MYLANG_ANALYSIS_LIST("keyword", 7) {
        // skip
        (void) node;
    }

    MYLANG_ANALYSIS_TEXT("id", 2) {
        IdCall::put([=]() {
            return libblock::name_t(node->getFullText());
        });
    }

    MYLANG_ANALYSIS_TEXT("reserved id", 11) {
        // skip
        (void) node;
    }

    MYLANG_ANALYSIS_TEXT("sign", 4) {
        // skip
        (void) node;
    }

    MYLANG_ANALYSIS_TEXT("ignored", 7) {
        // skip
        (void) node;
    }

    #undef MYLANG_ANALYSIS_LIST
    #undef MYLANG_ANALYSIS_TEXT

    // ignored nodes

    template <class N, class E>
    void run(const NodeTyped<N, NodeError<E>> *node) {
        // never reach if no parsing error
        (void) node;
        throw libblock::error_t("syntax error");
    }
};

}

#endif
