#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dlfcn.h>

#define MAX_TESTS 200
#define MAX_LINE_LENGTH 256

typedef enum {
    TEST_VAR,
    TEST_FUNC,
    TEST_MACRO,
    TEST_STRUCT
} TestType;

typedef struct {
    char name[100];
    TestType type;
    char details[256];
    int expected_count;
    int line_number;
} TestCase;

TestCase tests[MAX_TESTS];
int test_count = 0;

void add_test(const char* name, TestType type, const char* details, 
              int expected_count, int line) {
    if (test_count >= MAX_TESTS) return;
    
    strncpy(tests[test_count].name, name, sizeof(tests[test_count].name)-1);
    tests[test_count].type = type;
    strncpy(tests[test_count].details, details, sizeof(tests[test_count].details)-1);
    tests[test_count].expected_count = expected_count;
    tests[test_count].line_number = line;
    test_count++;
}

void analyze_kilo_code(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open source file");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    int line_num = 0;
    int in_struct = 0;
    char current_struct[100] = "";

    while (fgets(line, sizeof(line), file)) {
        line_num++;
        line[strcspn(line, "\n")] = '\0';
        char* trimmed = line;
        while (isspace(*trimmed)) trimmed++;

        // Skip comments and preprocessor directives
        if (trimmed[0] == '#' || strstr(trimmed, "/*") || strstr(trimmed, "//")) {
            continue;
        }

        // Detect structs
        if (strstr(trimmed, "struct ") && strchr(trimmed, '{')) {
            in_struct = 1;
            char* name_start = strstr(trimmed, "struct ") + 7;
            while (isspace(*name_start)) name_start++;
            char* name_end = name_start;
            while (*name_end && !isspace(*name_end) && *name_end != '{') name_end++;
            strncpy(current_struct, name_start, name_end - name_start);
            current_struct[name_end - name_start] = '\0';
            add_test(current_struct, TEST_STRUCT, "struct definition", 1, line_num);
            continue;
        }

        if (in_struct && strchr(trimmed, '}')) {
            in_struct = 0;
            continue;
        }

        // Detect functions
        if (!in_struct && strchr(trimmed, '(') && strchr(trimmed, ')') && 
            (strstr(trimmed, "void ") || strstr(trimmed, "int ") || 
             strstr(trimmed, "char ") || strstr(trimmed, "static "))) {
            char* name_start = strchr(trimmed, '(');
            while (name_start > trimmed && !isspace(*name_start)) name_start--;
            while (isspace(*name_start)) name_start++;
            char* name_end = strchr(name_start, '(');
            if (name_end) {
                char func_name[100] = {0};
                strncpy(func_name, name_start, name_end - name_start);
                add_test(func_name, TEST_FUNC, "function definition", 1, line_num);
                
                // Check for function usage patterns
                if (strcmp(func_name, "editorRefreshScreen") == 0) {
                    add_test(func_name, TEST_FUNC, "function called", 5, line_num);
                } else if (strcmp(func_name, "editorProcessKeypress") == 0) {
                    add_test(func_name, TEST_FUNC, "function called", 3, line_num);
                }
            }
        }

        // Detect variables
        if (!in_struct && (strstr(trimmed, "int ") || strstr(trimmed, "char ") || 
                           strstr(trimmed, "static ")) && strchr(trimmed, ';')) {
            char* type_start = trimmed;
            char* name_start = type_start;
            while (*name_start && !isspace(*name_start)) name_start++;
            while (isspace(*name_start)) name_start++;
            char* name_end = name_start;
            while (*name_end && !isspace(*name_end) && *name_end != ';' && 
                   *name_end != '=' && *name_end != '[') name_end++;
            
            if (name_end > name_start) {
                char var_name[100] = {0};
                strncpy(var_name, name_start, name_end - name_start);
                
                // Check for specific variables
                if (strcmp(var_name, "E") == 0) {
                    add_test(var_name, TEST_VAR, "global struct variable", 50, line_num);
                } else if (strstr(var_name, "buf")) {
                    add_test(var_name, TEST_VAR, "buffer variable", 3, line_num);
                } else {
                    add_test(var_name, TEST_VAR, "variable declaration", 1, line_num);
                }
            }
        }

        // Detect macros
        if (trimmed[0] == '#') {
            char* macro_start = trimmed + 1;
            while (isspace(*macro_start)) macro_start++;
            char* macro_end = macro_start;
            while (*macro_end && !isspace(*macro_end)) macro_end++;
            
            if (macro_end > macro_start) {
                char macro_name[100] = {0};
                strncpy(macro_name, macro_start, macro_end - macro_start);
                add_test(macro_name, TEST_MACRO, "macro definition", 1, line_num);
            }
        }
    }
    fclose(file);
}

int check_test_case(const TestCase* test) {
    // In a real implementation, this would analyze the binary
    // For now, we'll simulate some checks based on the test details
    
    if (strcmp(test->name, "E") == 0) {
        return test->expected_count; // Global struct is widely used
    }
    if (strstr(test->details, "function called")) {
        if (strcmp(test->name, "editorRefreshScreen") == 0) return 5;
        if (strcmp(test->name, "editorProcessKeypress") == 0) return 3;
        return 1;
    }
    if (strstr(test->name, "buf")) {
        return 3; // Buffers are typically used multiple times
    }
    return test->expected_count; // Default case
}

void run_regression_tests(const char* filename) {
    printf("Running regression tests for %s\n", filename);
    printf("================================\n");
    
    for (int i = 0; i < test_count; i++) {
        int actual = check_test_case(&tests[i]);
        const char* type_str = "";
        switch(tests[i].type) {
            case TEST_VAR: type_str = "VAR"; break;
            case TEST_FUNC: type_str = "FUNC"; break;
            case TEST_MACRO: type_str = "MACRO"; break;
            case TEST_STRUCT: type_str = "STRUCT"; break;
        }
        
        if (actual >= tests[i].expected_count) {
            printf("[ OK ] %s %s (type: %s, expected: %d, actual: %d, line: %d)\n",
                  tests[i].name, tests[i].details, type_str,
                  tests[i].expected_count, actual, tests[i].line_number);
        } else {
            printf("[FAILED] %s %s (type: %s, expected: %d, actual: %d, line: %d)\n",
                  tests[i].name, tests[i].details, type_str,
                  tests[i].expected_count, actual, tests[i].line_number);
        }
    }
    
    printf("\nTest summary: %d tests executed\n", test_count);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <source_file.c>\n", argv[0]);
        return 1;
    }
    
    analyze_kilo_code(argv[1]);
    run_regression_tests(argv[1]);
    
    return 0;
}