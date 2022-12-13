#include <stdio.h>
#include <stdlib.h>

int loadInputFile();
int nextLine(char *dst);

char crt[6][41];

#define CICLE_DRAW_PIXEL()                               \
    {                                                    \
        diff = j - x;                                    \
        crt[i][j] = ((diff > 1 || diff < -1) ? '.' : '#'); \
        j++;                                             \
        if (j == 40)                                     \
        {                                                \
            j = 0;                                       \
            i++;                                         \
        }                                                \
    }

int main()
{
    char line[16];
    int x = 1;
    int i = 0;
    int j = 0;
    int diff;

    if (loadInputFile() < 0)
    {
        fprintf(stderr, "Can't open: input.txt\n");
        return 1;
    }

    int n;
    while (nextLine(line) > 0)
    {
        CICLE_DRAW_PIXEL();
        if (sscanf(line, "%*s %d", &n) == 1)
        {
            CICLE_DRAW_PIXEL();
            x += n;
        }
    }

    for(int i = 0; i < 6; i++)
        puts(crt[i]);
}

#define BUFSIZE 1024

char fileBuf[BUFSIZE];
char *pbuf = fileBuf;
char *pbufend = fileBuf;

int loadInputFile()
{
    FILE *pf = fopen("input.txt", "r");
    if (!pf)
        return -1;
    pbuf = fileBuf;
    pbufend = fileBuf + fread(fileBuf, 1, BUFSIZE, pf);
    fclose(pf);

    return 0;
}

inline int nextLine(char *dst)
{
    char c;
    char *orig = dst;

    // read line:
    while (pbuf < pbufend && (c = *(pbuf++)) != '\n')
    {
        *(dst++) = c;
    }
    *dst = '\0';
    // return line length
    return dst - orig;
}