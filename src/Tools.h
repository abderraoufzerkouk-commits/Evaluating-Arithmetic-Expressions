#pragma once

#include <stdlib.h>

typedef struct String {
    char * content;
    int size;
} String;

String * newString() {
    String * new = malloc( sizeof( String ) );
    new->content = NULL;
    new->size = 0;
    return new;
}

int resetString( String * str ) {
    str->content = NULL;

    str->size = 0;

    return 0;
}

int addChar( String * text, char c ) {
    char * newContent = (char *) malloc( sizeof(char) * (text->size + 2) );
    text->size += 1;

    int size = text->size;

    newContent[size] = '\0';

    newContent[size - 1] = c;

    for ( int i = 0; i < size - 1; i++ ) {
        newContent[i] = text->content[i];
    }

    free(text->content);

    text->content = newContent;

    return 0;
}