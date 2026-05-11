#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ----------------------------
// Reverse Caesar Cipher
// ----------------------------
char* caesar_decrypt(const char* text, int shift) {
    int len = strlen(text);
    char* result = malloc(len + 1);
    shift = shift % 26;

    for (int i = 0; i < len; i++) {
        char c = text[i];

        if (isupper(c)) {
            result[i] = (c - 'A' - shift + 26) % 26 + 'A';
        }
        else if (islower(c)) {
            result[i] = (c - 'a' - shift + 26) % 26 + 'a';
        }
        else {
            result[i] = c;
        }
    }

    result[len] = '\0';
    return result;
}


// ----------------------------
// Reverse ZigZag Conversion
// ----------------------------
char* zigzag_restore(const char* s, int numRows) {
    int len = strlen(s);
    if (numRows == 1 || numRows >= len) {
        return strdup(s);
    }

    char* result = malloc(len + 1);
    int cycle = 2 * numRows - 2;

    int* pos = malloc(len * sizeof(int));
    int idx = 0;

    // Compute original positions
    for (int row = 0; row < numRows; row++) {
        for (int i = row; i < len; i += cycle) {
            pos[idx++] = i;

            int diag = i + cycle - 2 * row;
            if (row != 0 && row != numRows - 1 && diag < len) {
                pos[idx++] = diag;
            }
        }
    }

    // Reconstruct original string
    for (int i = 0; i < len; i++) {
        result[pos[i]] = s[i];
    }

    result[len] = '\0';
    free(pos);
    return result;
}


char* decode(const char* text) {
    int total_len = strlen(text);
    int len = total_len - 2;

    int caesarShift = text[0] - 'A';
    int numRows = text[1] - 'a';

    char* payload = malloc(len + 1);
    memcpy(payload, text + 2, len);
    payload[len] = '\0';

    char* caesar = caesar_decrypt(payload, caesarShift);
    free(payload);

    char* restored = zigzag_restore(caesar, numRows);
    free(caesar);

    return restored;  // caller owns this
}
char* load_file(const char* filename) {
    FILE* f = fopen(filename, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char* buffer = malloc(size + 1);
    if (!buffer) {
        fclose(f);
        return NULL;
    }

    fread(buffer, 1, size, f);
    buffer[size] = '\0';

    fclose(f);
    return buffer;
}
int main() {

    char* text= load_file("encrypted.txt");
    printf("%s\n", decode(text));
}