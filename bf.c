#include <stdio.h>
#include <stdlib.h>

#define STACK_LEN 10240


char *
exec(char *code)
{
    int             len, lc, rc;
    char           *pc;
    unsigned char  *stack, *ps;

    stack = malloc(STACK_LEN);
    if (stack == NULL) {
        return "alloc memory error";
    }

    lc = rc = 0;
    pc = code;
    ps = stack;

    for (pc = code; *pc != 0; pc++) {
        switch(*pc) {
        case '+': (*ps)++; break;
        case '-': (*ps)--; break;
        case '>': ps++; break;
        case '<': ps--; break;
        case '.': putchar(*ps); break;
        case ',': *ps = getchar(); break;
        case '[':
            if (*ps == 0) {
                lc++;
                while (lc != 0) {
                    pc++;
                    if (*pc == '[') lc++;
                    if (*pc == ']') lc--;
                }
            }
            break;

        case ']':
            if (*ps != 0) {
                rc++;
                while (rc != 0) {
                    pc--;
                    if (*pc == ']') rc++;
                    if (*pc == '[') rc--;
                }
            }
            break;
        }

        if(ps - stack > STACK_LEN) {
            return "> out of boundary";
        }

        if (ps - stack < 0) {
            return "< out of boundary";
        }
    }

    return NULL;
}

int
main(int argc, char *argv[])
{

    char *rv = NULL;

    if (argc != 2) {
        puts("usage: bf code");
    }

    rv = exec(argv[1]);
    if (rv != NULL) {
        puts(rv);
        return 1;
    }

    return 0;
}
