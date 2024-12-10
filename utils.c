#include "utils.h"
#include "interpreter.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// 去掉字符串的前后空格
char *trim(char *str) {
    char *end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = 0;
    return str;
}

// 简单的表达式求值（不支持复杂的运算）
int evaluate_expression(const char *expr) {
    // 这里只处理简单的数字和变量（+，-，*，/）。
    // 更复杂的表达式需要改进解析器来支持运算符优先级等。
    if (isalpha(expr[0])) {
        return variables[expr[0] - 'A'];
    }
    return atoi(expr);
}
