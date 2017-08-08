#pragma once

#include <string>

using namespace std;

namespace LexerNS
{
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
        None,
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
        Semicolon,

        // Others:
        Identifier
    };

    class Token
    {
    public:
        Token();
        Token(TokenType type, string description);
        Token(TokenType type, string description, string data);

        TokenType Type();
        string Description();

    private: // Private variables
        TokenType _type;
        string _description;
        string _stringData;
    };
}