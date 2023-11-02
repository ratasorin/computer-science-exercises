#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    void* v;
    int size;
} DynamicVector;

DynamicVector selfClosingHtmlTags() {
    FILE *fptr;

    // Open a file in read mode
    fptr = fopen("resources/self-closing-html-tags.csv", "r");

    if(fptr == NULL) {
        DynamicVector dn = {NULL, -1};
        return dn;
    }

    int HTML_TAG_MAX_LENGHT = 20;
    int maxTagsCount = 100;
    char* content = (char *) malloc(HTML_TAG_MAX_LENGHT * maxTagsCount * sizeof(char));
    char** selfClosingTags = (char**) malloc(maxTagsCount * sizeof(char*));
    
    fgets(content, HTML_TAG_MAX_LENGHT * maxTagsCount, fptr);

    int tagNumber = 0, letterPosition = 0;
    char* tag = malloc(HTML_TAG_MAX_LENGHT * sizeof(char));

    for(int i = 0; content[i] != '\0'; i++) {
        if(content[i] == ',') {
            tag[letterPosition + 1] = '\0';
            selfClosingTags[tagNumber] = tag;
            
            tag = malloc(HTML_TAG_MAX_LENGHT * sizeof(char));

            tagNumber++;
            letterPosition = 0;
            if(content[i + 1] == ' ')
                i++;
        }
        else {
            tag[letterPosition] = content[i];
            letterPosition++;
        }
    }

    selfClosingTags[tagNumber] = tag;

    DynamicVector dn = {selfClosingTags, tagNumber + 1};
    return dn;
}

int main(void) {
    char current;
    int openedTags = 0;

    DynamicVector selfClosingTagsVector = selfClosingHtmlTags();
    char** selfClosingTags = selfClosingTagsVector.v;

    if(selfClosingTags == NULL) {
        printf("Cannot open file: ./resources/self-closing-html-tags.csv!\n");
        return 0;
    }

    while((current = getchar()) != EOF) {
        
        // start processing the new HTML tag
        if(current == '<') {
            if(current == EOF) return 0;

            // find what tag is currently processed
            char tag[25] = "";
            while(current != '/' && current != '>') {
                if(current == '<') {
                    current = getchar();
                    if(current == EOF) return 0;
                };

                char letter[2] = {current, '\0'};
                strcat(tag, letter);
                current = getchar();
                if(current == EOF) return 0;
            }

            int isSelfClosing = 0;
            for(int i = 0; selfClosingTags[i] != NULL; i++) {
                char* selfClosingTag = selfClosingTags[i];


                if(strcmp(tag, selfClosingTag) == 0) {
                    isSelfClosing = 1;
                }
            }


            if(!isSelfClosing) {
                if(tag[0] == '/')
                    openedTags--;
                else openedTags++;
            }
        }
    }

    if(openedTags == 0) 
        printf("The html is ✅ CORRECTLY ✅ formatted!\n");
    else 
        printf("The hmtl is ❌ INCORRECTLY ❌ formatted!\n");
}