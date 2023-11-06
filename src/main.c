
#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>
//#include <zephyr/zephyr.h>
#include <stdlib.h>
 
//#include <shell/shell.h>

#define LENGTH 6

char  myval[LENGTH];
char  psk[LENGTH];
char  bt_token[LENGTH];
 
static int myval_set(const struct shell *shell, size_t argc, char *argv[])
{

    if (strlen(argv[2]) != LENGTH-1){
        shell_fprintf(shell, SHELL_ERROR, "%s Fail: string is wrong!\n", argv[1]);
    }
    else {
        strcpy(myval, argv[2]);
        shell_fprintf(shell, SHELL_NORMAL, "%s ok: %s\n", argv[1], myval);
    }
    return 0;
}
 
static int myval_get(const struct shell *shell, size_t argc, char *argv[])
{
    shell_fprintf(shell, SHELL_NORMAL, "Current myval level: %s\n", myval);
    return 0;
}
 
void main(void)
{
    SHELL_STATIC_SUBCMD_SET_CREATE(
        myval_cmds,
        SHELL_CMD_ARG(set, NULL,
            "example:\n"
            "$ myval set dhfhekenso\n",
            myval_set, 3, 0),
        SHELL_CMD_ARG(get, NULL,
            "get the myval level\n"
            "usage:\n"
            "$ myval get",
            myval_get, 2, 0),
        SHELL_SUBCMD_SET_END
        );
 
    SHELL_CMD_REGISTER(cmd, &myval_cmds, "myval level setting", NULL);
}