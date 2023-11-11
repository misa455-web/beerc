#pragma once
#include <string>
#include <vector>
#include <optional>

enum class _TokenType_ {
    returnToken,
    WInteger,
    lineSepToken,
};

struct _Token_ {
    _TokenType_ type;
    std::optional<std::string> value;
};

class Tokenizer
{
public:
    inline Tokenizer(std::string& src) : m_src(std::move(src)), m_index(0)
    {
    }

    std::vector<_Token_> tokenize()
    {
        std::vector<_Token_> tokens;
        std::string buf;

        while (peak().has_value() && std::isdigit(peak().value()))
        {
            if (std::isalpha(peak().value()))
            {
                buf.push_back(consume());
                while (peak().has_value() && std::isalnum(peak().value()))
                {
                    buf.push_back(consume());
                }
                if (buf == "return")
                {
                    tokens.push_back({.type = _TokenType_::returnToken});
                    buf.clear();
                    continue;
                }
                else
                {
                    std::cerr << "Uhhhhh... you messed up! \n";
                    exit(EXIT_FAILURE);
                }
            }
            else if (std::isdigit(peak().value()))
            {
                buf.push_back(consume());
                while (peak().has_value() && std::isdigit(peak().value()))
                {
                    buf.push_back(consume());
                }
                tokens.push_back({.type = _TokenType_::WInteger, .value = buf});
                buf.clear();
                continue;
            }
            else if (peak().value() == ';')
            {
                consume();
                tokens.push_back({.type = _TokenType_::lineSepToken});
                continue;
            }
            else if (std::isspace(peak().value()))
            {
                consume();
                continue;
            }
            else
            {
                std::cerr << "Uhhhhh... you messed up! \n";
                exit(EXIT_FAILURE);
            }
        }
        m_index = 0;
        return tokens;
    }

private:
    [[nodiscard]] inline std::optional<char> peak(int ahead = 1) const
    {
        if (m_index + ahead - 1 >= m_src.length())
        {
            return {};
        }
        else
        {
            return m_src.at(m_index + ahead - 1);
        }
    }

    inline char consume()
    {
        return m_src.at(m_index++);
    }

    const std::string m_src;
    size_t m_index = 0;
};
