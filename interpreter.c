#include "interpreter.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int variables[MAX_VARS];      // A-Z 的变量
char *code[MAX_PROG];         // 存储程序行
int program_counter = 0;      // 程序计数器
int stack[MAX_STACK];         // 调用堆栈
int sp = 0;                   // 堆栈指针

// 初始化解释器
void init_interpreter() {
    memset(variables, 0, sizeof(variables));
    memset(code, 0, sizeof(code));
    program_counter = 0;
    sp = 0;
}

// 清理解释器
void cleanup_interpreter() {
    for (int i = 0; i < MAX_PROG; i++) {
        if (code[i]) {
            free(code[i]);
            code[i] = NULL;
        }
    }
}

// 执行一行代码
void execute_line(const char *line) {
    parse_and_execute(line);
}

// 从文件加载程序
void load_program(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    char line[MAX_LINE];
    int line_number;
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d", &line_number);
        if (line_number >= MAX_PROG) {
            printf("Error: Line number exceeds program limit\n");
            continue;
        }
        code[line_number] = strdup(line);
    }

    fclose(file);
}

// 执行程序
void execute_program() {
    for (program_counter = 0; program_counter < MAX_PROG; program_counter++) {
        if (code[program_counter]) {
            execute_line(code[program_counter]);
        }
    }
}
