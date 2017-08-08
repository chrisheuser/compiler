#include "stdafx.h"
#include "Lexer.h"

using namespace LexerNS;

/////////////////////////////////////////////
// Public methods
/////////////////////////////////////////////

Token* Lexer::Current()
{
    return _mostRecentToken;
}

bool Lexer::Advance()
{
    // Make sure we think have code to process:
    if (_state = LexerState::NoCodeToProcess)
    {
        return false;
    }

    // Make sure we actually have code to process:
    if (_code.size() == 0)
    {
        return false;
    }

    // Check if we're past the end of code to process:
    if (_curIdx >= _code.size())
    {
        _code = "";
        _curIdx = 0;
        _state = LexerState::NoCodeToProcess;
        return false;
    }

    // Extract current character:
    char currentChar = _code[_curIdx];

    // Is this a space? If so, skip past it:
    if (currentChar == ' ')
    {
        _curIdx++;

        // Check if we're past the end of code to process again:
        if (_curIdx >= _code.size())
        {
            _code = "";
            _curIdx = 0;
            _state = LexerState::NoCodeToProcess;
            return false;
        }

        // We're not, so set currentChar to the new value:
        currentChar = _code[_curIdx];
    }

    // Is this a symbol?
    bool foundSymbol = false;
    switch (currentChar)
    {
    case '\r':
        _mostRecentToken = new Token(TokenType::CarriageReturn, "carriage-return");
        foundSymbol = true;
        break;
    case '\n':
        _mostRecentToken = new Token(TokenType::LineFeed, "line-feed");
        foundSymbol = true;
        break;
    case ':':
        _mostRecentToken = new Token(TokenType::Colon, "colon");
        foundSymbol = true;
        break;
    case '[':
        _mostRecentToken = new Token(TokenType::LeftBracket, "left-bracket");
        foundSymbol = true;
        break;
    case ']':
        _mostRecentToken = new Token(TokenType::RightBracket, "right-bracket");
        foundSymbol = true;
        break;
    case '{':
        _mostRecentToken = new Token(TokenType::LeftBrace, "left-brace");
        foundSymbol = true;
        break;
    case '}':
        _mostRecentToken = new Token(TokenType::RightBrace, "right-brace");
        foundSymbol = true;
        break;
    case '(':
        _mostRecentToken = new Token(TokenType::LeftParenthesis, "left-parenthesis");
        foundSymbol = true;
        break;
    case ')':
        _mostRecentToken = new Token(TokenType::RightPrenthesis, "right-parenthesis");
        foundSymbol = true;
        break;
    case '+':
        _mostRecentToken = new Token(TokenType::Plus, "plus");
        foundSymbol = true;
        break;
    case '-':
        _mostRecentToken = new Token(TokenType::Dash, "dash");
        foundSymbol = true;
        break;
    case '!':
        _mostRecentToken = new Token(TokenType::Bang, "bang");
        foundSymbol = true;
        break;
    case '*':
        _mostRecentToken = new Token(TokenType::Asterisk, "asterisk");
        foundSymbol = true;
        break;
    case '/':
        _mostRecentToken = new Token(TokenType::ForwardSlash, "forward-slash");
        foundSymbol = true;
        break;
    case '%':
        _mostRecentToken = new Token(TokenType::Percent, "percent");
        foundSymbol = true;
        break;
    case '<':
        _mostRecentToken = new Token(TokenType::LessThan, "less-than");
        foundSymbol = true;
        break;
    case '>':
        _mostRecentToken = new Token(TokenType::GreaterThan, "greater-than");
        foundSymbol = true;
        break;
    case '=':
        _mostRecentToken = new Token(TokenType::Equals, "equals");
        foundSymbol = true;
        break;
    case '#':
        _mostRecentToken = new Token(TokenType::Hashtag, "hashtag");
        foundSymbol = true;
        break;
    case '&':
        _mostRecentToken = new Token(TokenType::Ampersand, "ampersand");
        foundSymbol = true;
        break;
    case '|':
        _mostRecentToken = new Token(TokenType::Pipe, "pipe");
        foundSymbol = true;
        break;
    case ',':
        _mostRecentToken = new Token(TokenType::Comma, "comma");
        foundSymbol = true;
        break;
    case ';':
        _mostRecentToken = new Token(TokenType::Semicolon, "semicolon");
        foundSymbol = true;
        break;
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
        // We now have either an identifier or a keyword, let's figure out which

        // Check for a keyword first:
        Token* potentialToken = NULL;
        if (_code.substr(_curIdx, 4) == "true")
        {
            potentialToken = new Token(TokenType::True, "true");
        }
        else if (_code.substr(_curIdx, 5) == "false")
        {
            potentialToken = new Token(TokenType::False, "false");
        }
        else if (_code.substr(_curIdx, 4) == "func")
        {
            potentialToken = new Token(TokenType::Func, "func");
        }
        else if (_code.substr(_curIdx, 5) == "while")
        {
            potentialToken = new Token(TokenType::While, "while");
        }
        else if (_code.substr(_curIdx, 3) == "for")
        {
            potentialToken = new Token(TokenType::For, "for");
        }
        else if (_code.substr(_curIdx, 5) == "guard")
        {
            potentialToken = new Token(TokenType::Guard, "guard");
        }
        else if (_code.substr(_curIdx, 2) == "if")
        {
            potentialToken = new Token(TokenType::If, "if");
        }
        else if (_code.substr(_curIdx, 4) == "else")
        {
            potentialToken = new Token(TokenType::Else, "while");
        }
        else if (_code.substr(_curIdx, 6) == "return")
        {
            potentialToken = new Token(TokenType::Return, "return");
        }

        if (potentialToken != NULL)
        {
            // We found a potential matching keyword, let's check if it's just a prefix of a larger identifier:
            int nextCharIndex = _curIdx + potentialToken->Description().size();
            if (nextCharIndex < _code.size())
            {
                char nextChar = _code[nextCharIndex];
                if (!((nextChar == '_') ||
                    ('0' <= nextChar && nextChar <= '9') ||
                    ('A' <= nextChar && nextChar <= 'Z') ||
                    ('a' <= nextChar && nextChar <= 'z')))
                {
                    // The next character isn't one that could be in an identifier, so we found a keyword!
                    _mostRecentToken = potentialToken;
                    _curIdx += _mostRecentToken->Description().size();
                    return true;
                }
            }
        }

        // Well, it's not a keyword, so it's definitely an identifier
        unsigned int endOfIdentifier = _curIdx;
        unsigned int currentCheckPosition = endOfIdentifier + 1;
        while (currentCheckPosition < _code.size())
        {
            char oneChar = _code[endOfIdentifier];
            if ((oneChar == '_') ||
                ('0' <= oneChar && oneChar <= '9') ||
                ('A' <= oneChar && oneChar <= 'Z') ||
                ('a' <= oneChar && oneChar <= 'z'))
            {
                endOfIdentifier++;
            }

            currentCheckPosition++;
        }

        _mostRecentToken = new Token(TokenType::Identifier, "identifier", _code.substr(_curIdx, endOfIdentifier - _curIdx));
        _curIdx = endOfIdentifier++;
        return true;
    }

    // Is this a number?
    //TODO

    return false;
}

bool Lexer::Load(string code)
{
    if (code.size() == 0)
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