#include "stdafx.h"
#include "Token.h"

using namespace LexerNS;

/////////////////////////////////////////////
// Public methods
/////////////////////////////////////////////

Token::Token()
{
    _type = TokenType::None;
    _description = "NONETOKEN";
}

Token::Token(TokenType type, string description)
{
    _type = type;
    _description = description;
}

Token::Token(TokenType type, string description, string data)
{
    _type = type;
    _description = description;
    _stringData = data;
}

TokenType Token::Type()
{
    return _type;
}

string Token::Description()
{
    return _description;
}