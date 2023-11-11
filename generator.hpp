#pragma once
#include ".\parser.hpp"
#include ".\tokenization.hpp"
#include <string>

class Generator {
public:
    inline Generator(const nodes::__return__node& root) : m_root(root) {};  // Definition added

    std::string generate() 
    {
        std::stringstream output;
        output << "global _start\n_start:\n";
        output << "    mov rax, 60\n";
        output << "    mov rdi, " << m_root.expr.WInteger.value.value() << '\n';
        output << "    syscall";
        return output.str();
    }

private:
    const nodes::__return__node m_root;
};
