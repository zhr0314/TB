#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"

int main() {
    char line[MAX_LINE];
    printf("Tiny BASIC Interpreter\n");
    printf("Type END to exit.\n");

    init_interpreter(); // ��ʼ��������

    while (1) {
        printf("> ");
        if (fgets(line, sizeof(line), stdin) == NULL) break;

        if (strnicmp(line, "END", 3) == 0) {
            printf("Program ended.\n");
            break;
        }

        execute_line(line); // ִ��������
    }

    cleanup_interpreter(); // ������Դ
    return 0;
}
