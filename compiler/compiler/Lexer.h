#pragma once

#include <string>
#include <vector>

#include "Token.h"

using namespace std;

namespace LexerNS
{
    enum LexerState
    {
        NoCodeToProcess,
        ReadyToProcess
    };

    class Lexer
    {
    public: // Public methods
        Token* Current();
        bool Advance();

        bool Load(string code);
        LexerState State();

    private: // Private variables
        string _code;
        unsigned int _curIdx = 0;

        LexerState _state;
        Token* _mostRecentToken = NULL;
    };
}