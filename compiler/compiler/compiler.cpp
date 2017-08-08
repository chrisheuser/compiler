// compiler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Lexer.h"
#include "Token.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace LexerNS;

int main()
{
    Lexer* lexer = new Lexer();
    lexer->Load(
        "func testMethod() {\r\n"
            "return true\r\n"
        "}"
    );

    vector<Token*> tokens;
    while (lexer->Advance())
    {
        tokens.push_back(lexer->Current());
    }

    for (unsigned int i = 0; i < tokens.size(); i++)
    {
        cout << tokens[i]->Description() << " ";
    }

    char closePress;
    cin >> closePress;

    return 0;
}

