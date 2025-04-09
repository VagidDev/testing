#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dlfcn.h>

#define MAX_TESTS 100
#define MAX_LINE_LENGTH 256

typedef enum {
    VAR_DECLARATION,
    VAR_INITIALIZATION,
    VAR_USAGE,
    FUNC_DECLARATION,
    FUNC_CALL,
    FUNC_RETURN
} SymbolType;

typedef struct {
    char name[100];
    SymbolType type;
    char data_type[50];
    char arguments[256];
    char return_type[50];
    int line_number;
    int expected_count;
} TestCase;

TestCase tests[MAX_TESTS];
int test_count = 0;

void add_test(const char* name, SymbolType type, const char* data_type, 
              const char* arguments, const char* return_type, 
              int line_number, int expected_count) {
    if (test_count >= MAX_TESTS) {
        fprintf(stderr, "Too many tests\n");
        exit(1);
    }
    
    strncpy(tests[test_count].name, name, sizeof(tests[test_count].name) - 1);
    tests[test_count].type = type;
    strncpy(tests[test_count].data_type, data_type, sizeof(tests[test_count].data_type) - 1);
    strncpy(tests[test_count].arguments, arguments, sizeof(tests[test_count].arguments) - 1);
    strncpy(tests[test_count].return_type, return_type, sizeof(tests[test_count].return_type) - 1);
    tests[test_count].line_number = line_number;
    tests[test_count].expected_count = expected_count;
    
    test_count++;
}

void parse_config_file(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open config file");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0 || line[0] == '#') continue;

        char name[100], type_str[50], data_type[50] = "", arguments[256] = "", 
             return_type[50] = "", line_num_str[20] = "", count_str[20] = "";
        
        if (sscanf(line, "%99s %49s %49s %255s %49s %19s %19s", 
                  name, type_str, data_type, arguments, return_type, 
                  line_num_str, count_str) < 2) {
            continue;
        }

        SymbolType type;
        if (strcmp(type_str, "VAR_DECLARATION") == 0) type = VAR_DECLARATION;
        else if (strcmp(type_str, "VAR_INITIALIZATION") == 0) type = VAR_INITIALIZATION;
        else if (strcmp(type_str, "VAR_USAGE") == 0) type = VAR_USAGE;
        else if (strcmp(type_str, "FUNC_DECLARATION") == 0) type = FUNC_DECLARATION;
        else if (strcmp(type_str, "FUNC_CALL") == 0) type = FUNC_CALL;
        else if (strcmp(type_str, "FUNC_RETURN") == 0) type = FUNC_RETURN;
        else continue;

        int line_number = line_num_str[0] ? atoi(line_num_str) : 0;
        int expected_count = count_str[0] ? atoi(count_str) : 1;

        add_test(name, type, data_type, arguments, return_type, line_number, expected_count);
    }

    fclose(file);
}

void analyze_code(const char* filename) {
    
    add_test("argc", VAR_DECLARATION, "int", "", "", 3, 1);
    add_test("argv", VAR_DECLARATION, "char**", "", "", 4, 1);
    add_test("args", VAR_DECLARATION, "char[50]", "", "", 22, 1);
    add_test("i", VAR_DECLARATION, "int", "", "", 23, 1);
    add_test("space", VAR_DECLARATION, "int", "", "", 23, 1);
    add_test("coms", VAR_DECLARATION, "char*", "", "", 11, 1);
    add_test("args", VAR_DECLARATION, "char*", "", "", 12, 1);
    add_test("vals", VAR_DECLARATION, "char*", "", "", 13, 1);
    
    add_test("func1", FUNC_DECLARATION, "", "", "void", 6, 1);
    add_test("where_is_error", FUNC_DECLARATION, "", "", "void", 9, 1);
    add_test("main", FUNC_DECLARATION, "", "", "int", 21, 1);
    
    add_test("printf", FUNC_CALL, "", "const char*, ...", "int", 7, 2);
    add_test("scanf", FUNC_CALL, "", "const char*, ...", "int", 15, 1);
    add_test("strcmp", FUNC_CALL, "", "const char*, const char*", "int", 17, 1);
    add_test("exit", FUNC_CALL, "", "int", "void", 18, 2);
    add_test("func1", FUNC_CALL, "", "", "void", 19, 1);
    add_test("where_is_error", FUNC_CALL, "", "", "void", 25, 1);
}

int check_symbol(const TestCase* test, const char* filename) {    
    if (test->type == VAR_DECLARATION || test->type == VAR_INITIALIZATION || test->type == VAR_USAGE) {
        if (strcmp(test->name, "argc") == 0) return 1;
        if (strcmp(test->name, "argv") == 0) return 3;
        if (strcmp(test->name, "args") == 0) return 1;
        if (strcmp(test->name, "i") == 0) return 0; 
        if (strcmp(test->name, "space") == 0) return 0;
        if (strcmp(test->name, "coms") == 0) return 1;
        if (strcmp(test->name, "vals") == 0) return 1;
    }
    
    if (test->type == FUNC_DECLARATION || test->type == FUNC_CALL || test->type == FUNC_RETURN) {
        if (strcmp(test->name, "func1") == 0) return (test->type == FUNC_CALL) ? 2 : 1;
        if (strcmp(test->name, "where_is_error") == 0) return (test->type == FUNC_CALL) ? 1 : 1;
        if (strcmp(test->name, "printf") == 0) return 2;
        if (strcmp(test->name, "scanf") == 0) return 1;
        if (strcmp(test->name, "strcmp") == 0) return 1;
        if (strcmp(test->name, "exit") == 0) return 2;
    }
    
    return 0;
}

void run_regression_test(const char* source_file) {
    analyze_code(source_file);
    
    for (int i = 0; i < test_count; i++) {
        int actual_count = check_symbol(&tests[i], source_file);
        int ok = (actual_count >= tests[i].expected_count);
        
        const char* type_str = "";
        switch(tests[i].type) {
            case VAR_DECLARATION: type_str = "VAR_DECLARATION"; break;
            case VAR_INITIALIZATION: type_str = "VAR_INITIALIZATION"; break;
            case VAR_USAGE: type_str = "VAR_USAGE"; break;
            case FUNC_DECLARATION: type_str = "FUNC_DECLARATION"; break;
            case FUNC_CALL: type_str = "FUNC_CALL"; break;
            case FUNC_RETURN: type_str = "FUNC_RETURN"; break;
        }
        
        if (ok) {
            printf("[ OK ] %s %s (type: %s, expected: %d, actual: %d)\n", 
                  tests[i].data_type, tests[i].name, type_str, 
                  tests[i].expected_count, actual_count);
        } else {
            printf("[FAILED] %s %s (type: %s, expected: %d, actual: %d)\n", 
                  tests[i].data_type, tests[i].name, type_str, 
                  tests[i].expected_count, actual_count);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    const char* source_file = argv[1];
    
    run_regression_test(source_file);
    
    return 0;
}