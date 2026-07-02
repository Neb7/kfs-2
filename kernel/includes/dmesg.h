#ifndef DMESG_H
# define DMESG_H

# define DMESG_LINES    64
# define DMESG_LINE_LEN 128

void    dmesg_write(const char *msg);
void    dmesg_print(void);

#endif
