#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *f = fopen(argv[1], "r");
    
    char c;
    unsigned char lineAcc = 0;
    unsigned int line = 0;
    char string[17];
    string[16] = '\0';

    while ((c = fgetc(f)) != EOF) {
        if(lineAcc == 0) {
            fprintf(stdout, "%08x: ", line);
            line += 16;
        }

        fprintf(stdout, "%02x", c);
        if(c > 31 && c < 127) {
            string[lineAcc] = c;
        } else {
            string[lineAcc] = '.';
        }

        lineAcc++;

        if(lineAcc % 2 == 0) {
            fprintf(stdout, " ");
        }
        if(lineAcc == 16) {
            fprintf(stdout, " %s\n", string);
            lineAcc = 0;
            memset(string, 0, sizeof(char) * 16);
        }
    }

    int jump = ((16 - lineAcc) / 2) * 5;
    if(lineAcc % 2 == 1)
        jump += 3;

    fprintf(stdout, " \x1B[%dC%s\n", jump, string);

    return 0;
}
