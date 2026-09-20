#include <limits.h>
#include <stdio.h>

#define NOB_IMPLEMENTATION
#include "../nob.h"

typedef struct {
    Nob_String_View values[256][256];
    size_t rowCount, colCount;
} Csv;

char num_to_char(size_t num) {
    return 'A' + num;
}

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

    data.rowCount = lineCount;
    for (size_t row = 0; row < lineCount; ++row) {
        line = nob_sv_chop_by_delim(&workingSv, '\n');
        size_t valueCount = sv_count_characters(&line, ',') + 1;
        data.colCount = valueCount;

        for (size_t col = 0; col < valueCount; ++col) {
            Nob_String_View value = nob_sv_chop_by_delim(&line, ',');
            data.values[row][col] = value;
        }
    }

    printf("%zu x %zu\n", data.rowCount, data.colCount);

    printf("       ");

    for (size_t col = 0; col < data.colCount; ++col) {
        printf("[  %c  ] ", num_to_char(col));
    }
    printf("\n");

    for (size_t col = 0; col < data.colCount; ++col) {
            printf("[  %c  ] ", num_to_char(col));
            for (size_t row = 0; row < data.rowCount; ++row) {
                Nob_String_View value = data.values[col][row];
                if (value.count == 0) continue;
                printf("%.*s ", (int)value.count, value.data);
            }
        printf("\n");
    }

    return 0;
}