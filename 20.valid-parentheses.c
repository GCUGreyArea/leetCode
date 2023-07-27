/*
 * @lc app=leetcode id=20 lang=c
 *
 * [20] Valid Parentheses
 *
 * Accepted
    91/91 cases passed (0 ms)
    Your runtime beats 100 % of c submissions
    Your memory usage beats 48.73 % of c submissions (5.8 MB)

    https://leetcode.com/submissions/detail/549364035/
 */


#include <stdbool.h>
#include <stdlib.h>

// @lc code=start
typedef struct stack_s {
    int len;
    int place;
    char * ar;
} stack_t;


stack_t * makeStack(size_t len) {
    stack_t * st = (stack_t*) malloc(sizeof(stack_t));
    st->ar = (char*) malloc(sizeof(char)*len);
    st->len = len;
    st->place = 0;

    return st;
}

void destroyStack(stack_t * st) {
    free(st->ar);
    free(st);
}

bool push(stack_t * st, char c) {
    if(st->place == st->len) return false;
    st->ar[st->place++] = c;
    return true;
}

char pop(stack_t * st) {
    if(st->place == 0) return '\0';
    return st->ar[--(st->place)];
}

bool isValid(char * s) {
    if(s == NULL) {return false;}


    size_t len = strlen(s);
    stack_t * st = makeStack(len);
    char c = '\0';
    for(size_t i=0;i<len;i++) {
        switch(s[i]) {
            case '(':
            case '[':
            case '{':
                push(st,s[i]);
                break;
            case ')':
                c = pop(st);
                if(c != '(') {
                    destroyStack(st);
                    return false;
                }
                break;
            case ']':
                c = pop(st);
                if(c != '[') {
                    destroyStack(st);
                    return false;
                }
                break;
            case '}':
                c = pop(st);
                if(c != '{') {
                    destroyStack(st);
                    return false;
                }
                break;
            default:
                // return false;
                break; // Ignroe, though this should be an error!
        }
    }

    if(st->place != 0) {
        destroyStack(st);
        return false;
    }

    destroyStack(st);

    return true;
}
// @lc code=end


void main() {
    bool isOk = isValid("()[]{}");
    printf("Is ok %s\n", (isOk ? "true" : "false"));
}

