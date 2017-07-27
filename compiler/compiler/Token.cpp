#include "Token.h"

using namespace LexerNS;

/////////////////////////////////////////////
// Public methods
/////////////////////////////////////////////

Token::Token(TokenType type, string description)
{
    _type = type;
    _description = description;
}

TokenType Token::Type()
{
    return _type;
}

string Token::Description()
{
    return _description;
}