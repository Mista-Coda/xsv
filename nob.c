#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"

#define EXECUTABLE_NAME "xsv"
#define INSTALL_PATH "/bin/"EXECUTABLE_NAME

int main(int argc, char** argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);

    bool enableDebug = false;
    if (argc > 1) {
        const char* firstArg = argv[1];
        if (strcmp("debug", firstArg) == 0) {
            enableDebug = true;
            nob_log(NOB_INFO, "Enabling debug");
        }
    }

    Cmd cmd = {0};
    cmd_append(&cmd, "cc", "-Wall", "-Wextra", "-o", EXECUTABLE_NAME);
    if (enableDebug) {
        cmd_append(&cmd, "-ggdb");
    }

    cmd_append(&cmd, "src/main.c");

    if (!cmd_run(&cmd)) return 1;
}