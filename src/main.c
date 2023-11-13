
#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>
#include <zephyr/zephyr.h>
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
    shell_fprintf(shell, SHELL_NORMAL, "%s ok: %s\n", argv[1], myval);
    return 0;
}

static int modem_start(const struct shell *shell, size_t argc, char *argv[])
{
    k_msleep(2000);
    shell_fprintf(shell, SHELL_NORMAL, "start ok\n");
    return 0;
}

static int modem_stop(const struct shell *shell, size_t argc, char *argv[])
{
    k_msleep(1000);
    shell_fprintf(shell, SHELL_NORMAL, "stop ok\n");
    return 0;
}

void main(void)
{
    SHELL_STATIC_SUBCMD_SET_CREATE(
        myval_cmds,
        SHELL_CMD_ARG(set, NULL,
            "Commands:\n"
            "\t$set <var> something\n",
            myval_set, 3, 0),
        SHELL_CMD_ARG(get, NULL,
            "Commands:\n"
            "\t$get <var>",
            myval_get, 2, 0),
        SHELL_CMD_ARG(start, NULL,
            "Commands:\n"
            "\t$get <var>",
            modem_start, 1, 0),
        SHELL_CMD_ARG(stop, NULL,
            "Commands:\n"
            "\t$get <var>",
            modem_stop, 1, 0),
        SHELL_SUBCMD_SET_END
        );

    SHELL_CMD_REGISTER(modem, &myval_cmds, "modem settings", NULL);
}