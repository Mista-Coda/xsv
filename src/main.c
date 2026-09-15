#include <limits.h>
#include <stdio.h>

#define NOB_IMPLEMENTATION
#include "../nob.h"

int main(int argc, char** argv) {
    const char* programName = nob_shift_args(&argc, &argv);
    NOB_UNUSED(programName);

    if (argc < 1) {
        nob_log(NOB_ERROR, "Please provide a file path!");
        return 1;
    }

    const char* filePath = nob_shift_args(&argc, &argv);
    printf("%s\n", filePath);

    Nob_String_Builder sb = {0};
    nob_read_entire_file(filePath, &sb);

    size_t lineCount = 1;
    Nob_String_View sv = nob_sb_to_sv(sb);

    for (size_t i = 0; i < sv.count; ++i) {
        char c = sv.data[i];
        if (c == '\n') lineCount++;
    }

    Nob_String_View workingSv = sv;
    Nob_String_View line = {0};
    for (size_t i = 0; i < lineCount; ++i) {
        line = nob_sv_chop_by_delim(&workingSv, '\n');
        printf("[LINE]: %.*s\n", (int)line.count, line.data);

    }

    return 0;
}