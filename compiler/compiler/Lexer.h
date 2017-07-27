#pragma once

#include <string>
#include <vector>

#include "Token.h"

using namespace std;

namespace LexerNS
{
    class Lexer
    {
    public: // Public methods
        Token Current();
        bool Advance();

        bool Load(string code);
        LexerState State();

    private: // Private variables
        string _code;
        int _curIdx = 0;

        LexerState _state;
        Token _mostRecentToken;
    };

    enum LexerState
    {
        NoCodeToProcess,
        ReadyToProcess
    };
}