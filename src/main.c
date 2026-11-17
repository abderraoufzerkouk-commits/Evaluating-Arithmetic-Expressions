#include <stdio.h>
#include "Tokenizer.h"
#include "Parser.h"

char *checkParen(char *text)
{
    int count = 0;

    int i = 0;

    char c = text[i];

    while (c != '\0')
    {
        if (c == '(')
        {
            count += 1;
        }
        if (c == ')')
        {
            count -= 1;
        }
        i++;
        c = text[i];
    }

    if (count == 1)
    {
        printf("There is a missing closing parenthesis!");
        exit(1);
    }

    if (count > 1)
    {
        printf("There are %i missing closing parenthesis!", count);
        exit(1);
    }

    if (count == -1)
    {
        printf("There is a missing open parenthesis!");
        exit(1);
    }

    if (count < -1)
    {
        printf("There are %i missing open parenthesis!", -count);
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    // char * code = "(4 + 2*4.2)^(3 - (10 - 3^2)) / (6 - 3) + 5 * ( (3^4) / (3^2) )";
    if (argc == 0)
    {
        printf("Usage of the command: arithma [expr]");
        return 1;
    }
    char *code = argv[1];

    checkParen(code);

    /*printToken( Tokenize( code ) );*/

    TokenArray arr = TokenizeToArray(code);
    Validity(arr);

    /*printToken(PostFixe( arr ));*/

    printf("%i\n", exec(PostFixe(arr)));

    return 0;
}