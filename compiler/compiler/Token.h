#pragma once

#include <string>

using namespace std;

namespace LexerNS
{
    class Token
    {
    public:
        Token(TokenType type, string description);

        TokenType Type();
        string Description();

    private: // Private variables
        TokenType _type;
        string _description;
    };

    enum TokenType
    {
        // Keywords:
        True,
        False,
        Func,
        While,
        For,
        Guard,
        If,
        Else,
        Return,

        // Symbols:
        CarriageReturn,
        LineFeed,
        Colon,
        LeftBracket,
        RightBracket,
        LeftBrace,
        RightBrace,
        LeftParenthesis,
        RightPrenthesis,
        Plus,
        Dash,
        Bang,
        Asterisk,
        ForwardSlash,
        Percent,
        LessThan,
        GreaterThan,
        Equals,
        Hashtag,
        Ampersand,
        Pipe,
        Comma,
        Semicolon
    };
}