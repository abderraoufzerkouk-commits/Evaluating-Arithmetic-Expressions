#include "Tokenizer.h"
#include <stdbool.h>
#include <math.h>

typedef struct IntNode {
    int val;
    struct IntNode * next;
} IntNode;

typedef IntNode * IntList;

int intPop( IntList * list ) {
    IntList current = (*list);
    (*list) = current->next;

    int val = current->val;

    free(current);

    return val;
}

void intPush( IntList * list, int value ) {
    IntList new = (IntList) malloc( sizeof( IntNode ) );

    new->val = value;
    new->next = (*list);

    (*list) = new;
}

typedef Token * TokenList;

TokenList InitList( TokenList * l ) {
    return NULL;
}

TokenArrayElement pop( TokenList * list ){
    TokenList current = *list;

    (*list) = current->next;

    TokenArrayElement val = ( TokenArrayElement ) { current->type, current->value };

    free(current);

    return val;
}

void push( TokenList * list, TokenArrayElement t ) {
    Token * token = newToken( t.type, t.value );

    token->next = (*list);

    (*list) = token;
}

TokenArrayElement top( TokenList list ) {
    Token t = (*list);
    return ( TokenArrayElement ) { list->type, list->value };
}

TokenArrayElement toTokenArrayElement(Token t) {
    return ( TokenArrayElement ) { t.type, t.value };
}

bool operand(TokenArrayElement t) {
    if ( t.type == NUM ) {
        return true;
    }

    return false;
}

bool operator(TokenArrayElement t){
    switch ( t.type ) {
        case ADD:
        case SUB:
        case MULT:
        case DIV:
        case POW:
            return true;
            break;
        default:
            return false;
            break;
    }
}

int priority( TokenArrayElement t ) {
    switch (t.type)
    {
        case ADD:
        case SUB:
            return 0;
            break;
        case MULT:
        case DIV:
            return 1;
            break;
        case POW:
            return 2;
            break;
        default:
            break;
    
    }
    printf("Unexpected operator error!\n");
    return 4;
}


TokenList PostFixe( TokenArray arr ) {
    TokenList P = InitList(&P);
    TokenList R = InitList(&R);
    
    TokenArrayElement * array = arr.elements;

    for ( int i = 0; i < arr.size; i++ ) {
        if ( operand( array[i] ) ) {
            push( &R, array[i] );
        }
        else if ( array[i].type == OPAREN ) {
            push( &P, array[i] );
        }
        else if ( operator(array[i]) ) {
            while ( P != NULL && operator(top(P)) && priority(array[i]) <= priority(top(P)) ) {
                TokenArrayElement c = pop(&P);
                push(&R, c);
            }
            push(&P, array[i]);
        }
        else if ( array[i].type == CPAREN ) {
            while ( top( P ).type != OPAREN && P != NULL ) {
                TokenArrayElement t = pop(&P);
                push(&R, t);
            }
            if ( P == NULL ) {
                printf("Missing ( !");
            }
            pop(&P);
        }
    }

    while ( R != NULL ) {
        TokenArrayElement t = pop(&R);
        push( &P, t );
    }

    return P;
}

int operate( int left, int right, TokenType type ) {
    switch ( type ) {
        case ADD:
            return left + right;
            break;
        case SUB:
            return left - right;
            break;
        case MULT:
            return left * right;
            break;
        case DIV:
            if ( right == 0 ) {
                printf("Math Error: Division by 0!");
                exit(1);
            }
            return left / right;
            break;
        case POW:
            if ( right < 0 ) {
                printf("Math Error: Negative power!");
                exit(1);
            }
            if ( right == 0 && left == 0 ) {
                printf("Math Error: 0 to the 0!");
                exit(1);
            }
            return pow(left, right);
            break;
        
    }
}

int exec( TokenList list ) {
    IntList ls = NULL;

    Token * current = list;

    int left, right;

    while ( current != NULL ) {
        if ( operand( toTokenArrayElement( (*current) ) ) ) {
            intPush( &ls, atoi( current->value ) );
        }

        else {

            right = intPop( &ls );
            left = intPop( &ls );

            int res = operate(left, right, current->type);
            // printf("Operated %i and %i with %s got %i\n", left, right, names[current->type], res);
            intPush( &ls,  res );
        }

        current = current->next;
    }

    return ls->val;
}

void Validity(TokenArray arr) {
    if ( operator( arr.elements[0] ) ) {
        printf("Cannot start the expression with an operator.");
        exit(1);
    }
    for ( int i = 1; i < arr.size; i++ ) {
        if ( operator( arr.elements[i] ) ) {
            if ( operand(arr.elements[i - 1] ) == false && arr.elements[i-1].type != CPAREN ) {
                printf("Every operator must be preceeded by an operand!");
                exit(1);
            }
            if ( i + 1 >= arr.size || ( arr.elements[i+1].type != OPAREN  && operand(arr.elements[i+1]) == false ) ) {
                printf("Type: %i\n", arr.elements[i+1].type);
                printf("Every operator must be followed by an operand!");
                exit(1);
            }
        }
    }
}