#pragma once
#include <vector>
#include <optional>
#include ".\tokenization.hpp"

namespace nodes {
    struct __expression__node {
        _Token_ WInteger;
    };

    struct __return__node {
        __expression__node expr;
    };
}

class tokenParser
{
public: 
    inline explicit tokenParser(std::vector <_Token_> tokens)
        : m_tokens(std::move(tokens)){}

    std::optional <nodes::__expression__node> parse_expression_()
    {
        // ...

        if (peak().has_value())
        {
            if (peak().value().type == _TokenType_::WInteger)
            {
                return nodes::__expression__node{.WInteger = consume()};
            }
        }
        else
        {
            return {};
        }

        // Add a return statement here
        return {}; // or another appropriate value
    }


    std::optional <nodes::__return__node> parse()
    {
        std::optional <nodes::__return__node> __return_node;

        while (peak().has_value())
        {
            if (peak().value().type == _TokenType_::returnToken)
            {
                consume();

                if (auto __expression_node__ = parse_expression_())
                {
                    __return_node = nodes::__return__node {.expr = __expression_node__.value() };
                }
                else
                {
                    std::cerr << "Invalid expression \n";
                    exit(EXIT_FAILURE);
                }

                if (peak().has_value() && peak().value().type == _TokenType_::lineSepToken)
                {
                    consume();
                }
                else
                {
                    std::cerr << "Invalid expression \n";
                    exit(EXIT_FAILURE);
                }
            }
        }
        m_index = 0;
        return __return_node;
    }

private: 
    [[nodiscard]] inline std::optional <_Token_> peak(int ahead = 1) const
    {
        if (m_index + ahead - 1 >= m_tokens.size())
        {
            return {};
        }
        else
        {
            return m_tokens.at(m_index + ahead - 1);
        }
    }

    inline _Token_ consume()
    {
        return m_tokens.at(m_index++);
    }

    const std::vector <_Token_> m_tokens;
    size_t m_index = 0;
};
