#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

static int is_number(const char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

static int is_seperator(const char c)
{
    if (c == '-' || c == 13 || c == 9 || c == 10 || c == '.' || c == '/' || c == ',' || c == '\0')
        return (1);
    return (0);
}

static int read_full_number(char *c, int *ret, int fd)
{
    int nb = 0;
    nb = nb * 10 + atoi(c);
    while(read(fd, c, 1) != 0)
    {
        if (is_number(*c))
            nb = nb * 10 + atoi(c);
        else
            return (nb);
    }
    *ret = 0;
    return (nb);
}

static int sixfive(char *file)
{
    char sep = 0;
    char c;
    int nb;
    int ret = 1;
    int fd = open(file, O_RDONLY);

    if (fd == -1)
        return (1);

    while (read(fd, &c, 1) > 0)
    {
        if (is_number(c))
        {
            nb = read_full_number(&c, &ret, fd);
            if (is_seperator(sep) && (is_seperator(c) || ret == 0) && (nb % 5 == 0 || nb % 6 == 0))
                printf("%d\n", nb);
            sep = c;
        }
        else 
        {
            sep = c;
        }
    }
    return (0);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (sixfive(argv[i]))
            return (1);
    }
}