#pragma once
#include <stdlib.h>
#include "Tools.h"

typedef enum {
    NUM,
    OPAREN,
    CPAREN,
    ADD,
    SUB,
    MULT,
    DIV,
    POW,
    BEGIN
} TokenType;

char * names[] = { "NUM", "OPAREN", "CPAREN", "ADD", "SUB", "MULT", "DIV", "POW", "BEGIN" };

typedef struct Token {
    TokenType type;
    char * value;
    struct Token * next;
    struct Token * prev;
} Token;

typedef struct TokenArrayElement {
    TokenType type;
    char * value;
} TokenArrayElement;

typedef struct TokenArray {
    TokenArrayElement * elements;
    int size;
} TokenArray;

Token * newToken(TokenType type, char * value) {    

    Token * new = ( Token * ) malloc( sizeof( Token ) );
    new->type = type;
    new->value = value;
    new->next = NULL;
    new->prev = NULL;
    return new;

}

TokenArray * newTokenArray( TokenArrayElement * list, int size ) {
    TokenArray * arr = ( TokenArray * ) malloc( sizeof( TokenArray ) );

    arr->elements = list;
    arr->size = size;

    return arr;
}

Token * addToken(Token * parent, TokenType type, char * value) {
    Token * new = newToken(type, value);
    new->prev = parent;
    parent->next = new;

    return new;
}

TokenArray toArray(Token * head, int size) {
    Token * current = head;

    TokenArrayElement * array = ( TokenArrayElement * ) malloc( sizeof( TokenArrayElement ) * size );

    int i = 0;

    while ( current != NULL ) {
        array[i] =  ( TokenArrayElement ) {current->type, current->value};
        current = current->next;
        i++;
    }

    return ( TokenArray ) { array, size };

}

void printToken( Token * token ) {
    if ( token->type != NUM ) printf("(%s)", names[token->type]); 
    else printf("(%s)", token->value);

    if ( token->next == NULL ) {
        printf("\n");
        return;
    }

    printf("<->");
    printToken(token->next);
}

Token * Tokenize( char * text ) {
    Token * tokens = newToken(BEGIN, NULL);

    Token * current = tokens;

    String * str = newString();

    int i = 0;

    // Best way to keep track of the size without adding unecessary complexity!
    int size = 0;
    char c;

    while ( (c = text[i]) != '\0' ) {
        switch( c ) {
            case '+':
                //printf("Addition!\n");

                if ( str->size != 0 ) {
                    current = addToken(current, NUM, str->content);
                    size += 1;
                    resetString(str);
                }
                current = addToken(current, ADD, NULL);
                size += 1;
                break;
            case '-':
                //printf("Moins!\n");

                if ( str->size != 0 ) {
                    current = addToken(current, NUM, str->content);
                    size += 1;
                    resetString(str);
                }

                current = addToken(current, SUB, NULL);
                size += 1;

                break;

            case '*':
                //printf("Mult!\n");

                if ( str->size != 0 ) {
                    current = addToken(current, NUM, str->content);
                    size += 1;
                    resetString(str);
                }

                current = addToken(current, MULT, NULL);
                size += 1;

                break;

            case '/':
                //printf("Div!\n");

                if ( str->size != 0 ) {
                    current = addToken(current, NUM, str->content);
                    size += 1;
                    resetString(str);
                }

                current = addToken(current, DIV, NULL);
                size += 1;

                break;

            case '^':
                //printf("Pow!\n");

                if ( str->size != 0 ) {
                    current = addToken(current, NUM, str->content);
                    size += 1;
                    resetString(str);
                }

                current = addToken(current, POW, NULL);
                size += 1;

                break;

            case '(':
                //printf("OpenP!\n");

                if ( str->size != 0 ) {
                    current = addToken(current, NUM, str->content);
                    size += 1;
                    resetString(str);
                }

                current = addToken(current, OPAREN, NULL);
                size += 1;

                break;

            case ')':
                //printf("ClosedP!\n");

                if ( str->size != 0 ) {
                    current = addToken(current, NUM, str->content);
                    size += 1;
                    resetString(str);
                }

                current = addToken(current, CPAREN, NULL);
                size += 1;

                break;

            case '0'...'9':
                addChar(str, c);
                break;
            default:
                if ( str->size != 0 ) {
                    current = addToken(current, NUM, str->content);
                    size += 1;
                    resetString(str);
                }
                break;
        }

        

        i++;
    }
    if ( str->size != 0 ) {
        current = addToken(current, NUM, str->content);
        size += 1;
        resetString(str);
    }

    return tokens;
}

TokenArray TokenizeToArray( char * text ) {
    Token * tokens = newToken(BEGIN, NULL);

    Token * current = tokens;

    String * str = newString();

    int i = 0;

    // Best way to keep track of the size without adding unecessary complexity!

    int size = 0;
    char c;

    while ( (c = text[i]) != '\0' ) {
        switch( c ) {
            case '+':
                //printf("Addition!\n");

                if ( str->size != 0 ) {
                    current = addToken(current, NUM, str->content);
                    size += 1;
                    resetString(str);
                }
        
                current = addToken(current, ADD, NULL);
                size += 1;

                break;
            case '-':
                //printf("Moins!\n");

                if ( str->size != 0 ) {
                    current = addToken(current, NUM, str->content);
                    size += 1;
                    resetString(str);
                }

                current = addToken(current, SUB, NULL);
                size += 1;

                break;

            case '*':
                //printf("Mult!\n");

                if ( str->size != 0 ) {
                    current = addToken(current, NUM, str->content);
                    size += 1;
                    resetString(str);
                }

                current = addToken(current, MULT, NULL);
                size += 1;

                break;

            case '/':
                //printf("Div!\n");

                if ( str->size != 0 ) {
                    current = addToken(current, NUM, str->content);
                    size += 1;
                    resetString(str);
                }

                current = addToken(current, DIV, NULL);
                size += 1;

                break;

            case '^':
                //printf("Pow!\n");

                if ( str->size != 0 ) {
                    current = addToken(current, NUM, str->content);
                    size += 1;
                    resetString(str);
                }

                current = addToken(current, POW, NULL);
                size += 1;

                break;

            case '(':
                //printf("OpenP!\n");

                if ( str->size != 0 ) {
                    current = addToken(current, NUM, str->content);
                    size += 1;
                    resetString(str);
                }

                current = addToken(current, OPAREN, NULL);
                size += 1;

                break;

            case ')':
                //printf("ClosedP!\n");

                if ( str->size != 0 ) {
                    current = addToken(current, NUM, str->content);
                    size += 1;
                    resetString(str);
                }

                current = addToken(current, CPAREN, NULL);
                size += 1;

                break;

            case '0'...'9':
                addChar(str, c);
                break;
            case ' ':
            case '\t':
            case '\n':
                if ( str->size != 0 ) {
                    current = addToken(current, NUM, str->content);
                    size += 1;
                    resetString(str);
                }
                break;
            default:
                printf("Unrecognized character \"%c\" .", c);
                exit(1);
                break;
        }

        

        i++;
    }
    if ( str->size != 0 ) {
        current = addToken(current, NUM, str->content);
        size += 1;
        resetString(str);
    }

    return toArray(tokens->next, size);
}

TokenArray * InverseTokenArray( TokenArray * array ) {
    int size = array->size;

    TokenArrayElement * newArray = ( TokenArrayElement * ) malloc( sizeof( TokenArrayElement ) * size ) ;

    for ( int i = 0; i < size; i++ ) {
        newArray[ i ] = array->elements[ size - ( i + 1 ) ];
    }

    return newTokenArray( newArray, size );

}

TokenArray * Split( TokenArray * array, int start, int finish ) {
    if ( finish < start ) {
        fprintf(stderr, "Cannot get elements from reverse order!\n");

        return newTokenArray(NULL, 0);
    }
    
    int size = finish - start;

    if ( start < 0 || finish > array->size ) {
        fprintf(stderr, "Out of boundaries errors!\n");
        return newTokenArray(NULL, 0);
    }

    TokenArrayElement * newArray = ( TokenArrayElement * ) malloc( sizeof( newArray ) * size );

    for ( int i = 0; i < finish - start; i++ ) {
        newArray[i] = array->elements[start + i];
    }

    return newTokenArray( newArray, size );

}

int FindClosing( TokenArray * array, int start, TokenType type ) {
    int direction = ( type == CPAREN ? 1 : -1 );
    int size = array->size;
    int count = 1;

    for ( int i = start + 1; i < size; i++ ) {
        TokenArrayElement token =  array->elements[i];
        if ( token.type == CPAREN ) {
            count += direction;
        }
        else if ( token.type == OPAREN ) {
            count -= direction;
        }

        if ( count == 0 ) {
            return i;
        }
    }

    printf("Couldn't find ) !\n");
    exit(1);
    return size;
}

void ShowArray(TokenArray * array) {
    printf("[ ");
    for ( int i = 0; i < array->size - 1; i++ ) {
        printf("%s, ", names[ array->elements[i].type ]);
    }

    printf("%s ]\n", names[ array->elements[array->size - 1].type ]);

}