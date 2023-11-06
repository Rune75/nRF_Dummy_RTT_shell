
#include <zephyr/kernel.h>
#include <zephyr/shell/shell.h>
//#include <zephyr/zephyr.h>
#include <stdlib.h>
 
//#include <shell/shell.h>

 
uint16_t myval = 10000;
 
static int myval_set(const struct shell *shell, size_t argc, char *argv[])
{
    /* Received value is a string so do some test to convert and validate it */
    int32_t requested_myval = -1;
    if ((strlen(argv[1]) == 1) && (argv[1][0] == '0')) {
        requested_myval = 0;
    }
    else {
        requested_myval = strtol(argv[1], NULL, 10);
        if (requested_myval == 0) {
            //There was no number at the beginning of the string
            requested_myval = -1;
        }
    }
 
    /* Reject invalid values */
    if ((requested_myval < 0) || (requested_myval > 65535)) {
        shell_fprintf(shell, SHELL_ERROR, "Invalid value: %s; expected [0..65535]\n", argv[1]);
        return -1;
    }
    /* Otherwise set and report to the user with a shell message */
    else {
        myval = (uint16_t)requested_myval;
        shell_fprintf(shell, SHELL_NORMAL, "myval: %d\n", requested_myval);
    }
 
    return 0;
}
 
static int myval_get(const struct shell *shell, size_t argc, char *argv[])
{
    shell_fprintf(shell, SHELL_NORMAL, "Current myval level: %d\n", myval);
    return 0;
}
 
void main(void)
{
    SHELL_STATIC_SUBCMD_SET_CREATE(
        myval_cmds,
        SHELL_CMD_ARG(set, NULL,
            "example:\n"
            "$ myval set 1337\n",
            myval_set, 2, 0),
        SHELL_CMD_ARG(get, NULL,
            "get the myval level\n"
            "usage:\n"
            "$ myval get",
            myval_get, 1, 0),
        SHELL_SUBCMD_SET_END
        );
 
    SHELL_CMD_REGISTER(myval, &myval_cmds, "myval level setting", NULL);
}