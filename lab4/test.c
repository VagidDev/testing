#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int argc;
char *argv[3];
func1() { printf("Hello world!\n"); }
where_is_error()
{
    char *coms = argv[0];
    char *args = argv[1];
    char *vals = argv[2];
    printf("> ");
    scanf("%s", argv);
    if (strcmp(coms, "quit") == 0)
        func1();
    else
        exit(1);
    exit(0);
}

main()
{
    char args[50];
    int i, space;
    where_is_error();
}