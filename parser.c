#include "parser.h"
#include "interpreter.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 执行 PRINT 语句
void handle_print(char *line) {
    char *expr = trim(line + 5);
    printf("%d\n", evaluate_expression(expr));
}

// 执行 LET 语句
void handle_let(char *line) {
    char var = line[4];
    char *expr = trim(line + 6);
    variables[var - 'A'] = evaluate_expression(expr);
}

// 执行 INPUT 语句
void handle_input(char *line) {
    char var = line[5];
    printf("Enter value for %c: ", var);
    scanf("%d", &variables[var - 'A']);
}

// 执行 IF 语句
void handle_if(char *line) {
    char condition[256], statement[256];
    if (sscanf(line + 2, "%s THEN %s", condition, statement) == 2) {
        if (evaluate_expression(condition)) {
            parse_and_execute(statement);
        }
    }
}

// 执行 GOTO 语句
void handle_goto(char *line) {
    int target;
    sscanf(line + 4, "%d", &target);
    program_counter = target - 1;
}

// 执行 GOSUB 语句
void handle_gosub(char *line) {
    int target;
    sscanf(line + 5, "%d", &target);
    stack[sp++] = program_counter;  // 保存当前行
    program_counter = target - 1;   // 跳转到目标行
}

// 执行 RETURN 语句
void handle_return() {
    if (sp > 0) {
        program_counter = stack[--sp];  // 从堆栈返回
    } else {
        printf("Error: Stack underflow\n");
    }
}

// 执行 FOR 语句
void handle_for(char *line) {
    char var = line[4];
    int start, end, step = 1;
    sscanf(line + 6, "%d TO %d STEP %d", &start, &end, &step);
    variables[var - 'A'] = start;

    while (variables[var - 'A'] <= end) {
        parse_and_execute(line + 6);  // 执行循环体
        variables[var - 'A'] += step;
    }
}

// 解析并执行每行
void parse_and_execute(const char *line) {
    char *cmd = strdup(line);
    cmd = trim(cmd);

    if (strncmp(cmd, "PRINT", 5) == 0) {
        handle_print(cmd);
    } else if (strncmp(cmd, "LET", 3) == 0) {
        handle_let(cmd);
    } else if (strncmp(cmd, "INPUT", 5) == 0) {
        handle_input(cmd);
    } else if (strncmp(cmd, "IF", 2) == 0) {
        handle_if(cmd);
    } else if (strncmp(cmd, "GOTO", 4) == 0) {
        handle_goto(cmd);
    } else if (strncmp(cmd, "GOSUB", 5) == 0) {
        handle_gosub(cmd);
    } else if (strncmp(cmd, "RETURN", 6) == 0) {
        handle_return();
    } else if (strncmp(cmd, "FOR", 3) == 0) {
        handle_for(cmd);
    } else {
        printf("Error: Unknown command\n");
    }

    free(cmd);
}
