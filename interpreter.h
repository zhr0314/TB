#ifndef INTERPRETER_H
#define INTERPRETER_H

#define MAX_LINE 256    // 单行最大字符数
#define MAX_VARS 26     // 支持的变量数（A-Z）
#define MAX_PROG 1000   // 最大程序行数
#define MAX_STACK 10    // 调用堆栈大小

extern int variables[MAX_VARS];      // 声明变量数组
extern int program_counter;          // 声明程序计数器
extern int stack[MAX_STACK];         // 声明调用堆栈
extern int sp;                       // 声明堆栈指针

// 初始化和清理
void init_interpreter();
void cleanup_interpreter();

// 核心执行函数
void execute_line(const char *line);
void load_program(const char *filename);
void execute_program();
int evaluate_expression(const char *expr);

#endif
