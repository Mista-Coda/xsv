#include <limits.h>
#include <stdio.h>

#define NOB_IMPLEMENTATION
#include "../nob.h"

typedef struct {
    Nob_String_View values[256][256];
} Csv;

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
    Csv data = {0};

    for (size_t row = 0; row < lineCount; ++row) {
        line = nob_sv_chop_by_delim(&workingSv, '\n');
        size_t valueCount = sv_count_characters(&line, ',') + 1;

        for (size_t col = 0; col < valueCount; ++col) {
            Nob_String_View value = nob_sv_chop_by_delim(&line, ',');
            data.values[row][col] = value;
        }
    }

    for (size_t i = 0; i < 256; ++i) {
        for (size_t j = 0; j < 256; ++j) {
            Nob_String_View value = data.values[j][i];
            if (value.count == 0) continue;
            printf("%.*s\n", (int)value.count, value.data);
        }
    }

    return 0;
}