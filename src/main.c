#include <limits.h>
#include <stdio.h>

#define NOB_IMPLEMENTATION
#include "../nob.h"

size_t sv_count_characters(const Nob_String_View* sv, char c) {
    size_t total = 0;
    for (size_t i = 0; i < sv->count; ++i) {
        char svc = sv->data[i];
        if (svc == c) total++;
    }
    return total;
}

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
        size_t valueCount = sv_count_characters(&line, ',') + 1;

        printf("LINE: %zu\n", i);
        for (size_t j = 0; j < valueCount; ++j) {
            Nob_String_View value = nob_sv_chop_by_delim(&line, ',');
            printf("[VALUE]: %.*s\n", (int)value.count, value.data);
        }
    }

    return 0;
}