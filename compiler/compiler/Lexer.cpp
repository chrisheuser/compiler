#include "Lexer.h"

using namespace LexerNS;

/////////////////////////////////////////////
// Public methods
/////////////////////////////////////////////

Token Lexer::Current()
{
    return _mostRecentToken;
}

bool Lexer::Advance()
{
    // Make sure we think have code to process
    if (_state = LexerState::NoCodeToProcess)
    {
        return false;
    }

    // Make sure we actually have code to process
    if (_code.size == 0)
    {
        return false;
    }

    // Check if we're past the end of code to process
    if (_curIdx >= _code.size)
    {
        _code = "";
        _curIdx = 0;
        _state = LexerState::NoCodeToProcess;
        return false;
    }

    // Extract current character
    char currentChar = _code[_curIdx];

    // Is this a space? If so, skip past it.
    if (currentChar == ' ')
    {
        _curIdx++;

        // Check if we're past the end of code to process again:
        if (_curIdx >= _code.size)
        {
            _code = "";
            _curIdx = 0;
            _state = LexerState::NoCodeToProcess;
            return false;
        }
    }

    // Is this a symbol?
    bool foundSymbol = false;
    switch (currentChar)
    {
    case '\r':
        _mostRecentToken = Token(TokenType::CarriageReturn, "carriage-return");
        foundSymbol = true;
    case '\n':
        _mostRecentToken = Token(TokenType::LineFeed, "line-feed");
        foundSymbol = true;
    case ':':
        _mostRecentToken = Token(TokenType::Colon, "colon");
        foundSymbol = true;
    case '[':
        _mostRecentToken = Token(TokenType::LeftBracket, "left-bracket");
        foundSymbol = true;
    case ']':
        _mostRecentToken = Token(TokenType::RightBracket, "right-bracket");
        foundSymbol = true;
    case '{':
        _mostRecentToken = Token(TokenType::LeftBrace, "left-brace");
        foundSymbol = true;
    case '}':
        _mostRecentToken = Token(TokenType::RightBrace, "right-brace");
        foundSymbol = true;
    case '(':
        _mostRecentToken = Token(TokenType::LeftParenthesis, "left-parenthesis");
        foundSymbol = true;
    case ')':
        _mostRecentToken = Token(TokenType::RightPrenthesis, "right-parenthesis");
        foundSymbol = true;
    case '+':
        _mostRecentToken = Token(TokenType::Plus, "plus");
        foundSymbol = true;
    case '-':
        _mostRecentToken = Token(TokenType::Dash, "dash");
        foundSymbol = true;
    case '!':
        _mostRecentToken = Token(TokenType::Bang, "bang");
        foundSymbol = true;
    case '*':
        _mostRecentToken = Token(TokenType::Asterisk, "asterisk");
        foundSymbol = true;
    case '/':
        _mostRecentToken = Token(TokenType::ForwardSlash, "forward-slash");
        foundSymbol = true;
    case '%':
        _mostRecentToken = Token(TokenType::Percent, "percent");
        foundSymbol = true;
    case '<':
        _mostRecentToken = Token(TokenType::LessThan, "less-than");
        foundSymbol = true;
    case '>':
        _mostRecentToken = Token(TokenType::GreaterThan, "greater-than");
        foundSymbol = true;
    case '=':
        _mostRecentToken = Token(TokenType::Equals, "equals");
        foundSymbol = true;
    case '#':
        _mostRecentToken = Token(TokenType::Hashtag, "hashtag");
        foundSymbol = true;
    case '&':
        _mostRecentToken = Token(TokenType::Ampersand, "ampersand");
        foundSymbol = true;
    case '|':
        _mostRecentToken = Token(TokenType::Pipe, "pipe");
        foundSymbol = true;
    case ',':
        _mostRecentToken = Token(TokenType::Comma, "comma");
        foundSymbol = true;
    case ';':
        _mostRecentToken = Token(TokenType::Semicolon, "semicolon");
        foundSymbol = true;
    }

    if (foundSymbol == true)
    {
        _curIdx += 1;
        return true;
    }

    // Is this an identifier?
    if ((currentChar == '_') ||
        ('A' <= currentChar && currentChar <= 'Z') ||
        ('a' <= currentChar && currentChar <= 'z'))
    {
        // We now have either an identifier or a keyword (or an error), let's figure out which
        //TODO
    }

    // Is this a keyword?
    //TODO: this section doesn't work very well yet, fix it after the identifier code is done (or put it inside the identifier code)
    if (_code.substr(_curIdx, 4) == "true")
    {
        _mostRecentToken = Token(TokenType::True, "true");
        _curIdx += 4;
        return true;
    }
    else if (_code.substr(_curIdx, 5) == "false")
    {
        _mostRecentToken = Token(TokenType::False, "false");
        _curIdx += 5;
        return true;
    }
    else if (_code.substr(_curIdx, 4) == "func")
    {
        _mostRecentToken = Token(TokenType::Func, "func");
        _curIdx += 4;
        return true;
    }
    else if (_code.substr(_curIdx, 5) == "while")
    {
        _mostRecentToken = Token(TokenType::While, "while");
        _curIdx += 5;
        return true;
    }
    else if (_code.substr(_curIdx, 3) == "for")
    {
        _mostRecentToken = Token(TokenType::For, "for");
        _curIdx += 3;
        return true;
    }
    else if (_code.substr(_curIdx, 5) == "guard")
    {
        _mostRecentToken = Token(TokenType::Guard, "guard");
        _curIdx += 5;
        return true;
    }
    else if (_code.substr(_curIdx, 2) == "if")
    {
        _mostRecentToken = Token(TokenType::If, "if");
        _curIdx += 2;
        return true;
    }
    else if (_code.substr(_curIdx, 4) == "else")
    {
        _mostRecentToken = Token(TokenType::Else, "while");
        _curIdx += 4;
        return true;
    }
    else if (_code.substr(_curIdx, 5) == "return")
    {
        _mostRecentToken = Token(TokenType::Return, "return");
        _curIdx += 5;
        return true;
    }

    // Is this a number?
    //TODO
}

bool Lexer::Load(string code)
{
    if (code.size == 0)
    {
        _state = LexerState::NoCodeToProcess;
        return false;
    }

    _code = code;
    _state = LexerState::ReadyToProcess;
    return true;
}

LexerState Lexer::State()
{
    return _state;
}