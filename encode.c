#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
int rand_range(int min, int max) {
    if (min >= max) {
        return 0;
    }
    return min + rand() % (max - min + 1);
}
char* zigzag_convert(const char* s, int numRows) {
    int len = strlen(s);
    if (numRows == 1 || numRows >= len) {
        return strdup(s);
    }

    char* result = malloc(len + 1);
    int idx = 0;
    int cycle = 2 * numRows - 2;

    for (int row = 0; row < numRows; row++) {
        for (int i = row; i < len; i += cycle) {
            result[idx++] = s[i];

            int diag = i + cycle - 2 * row;
            if (row != 0 && row != numRows - 1 && diag < len) {
                result[idx++] = s[diag];
            }
        }
    }

    result[idx] = '\0';
    return result;
}


// ----------------------------
// Caesar Cipher
// ----------------------------
char* caesar_cipher(const char* text, int shift) {
    int len = strlen(text);
    char* result = malloc(len + 1);
    shift = shift % 26;

    for (int i = 0; i < len; i++) {
        char c = text[i];

        if (isupper(c)) {
            result[i] = (c - 'A' + shift + 26) % 26 + 'A';
        }
        else if (islower(c)) {
            result[i] = (c - 'a' + shift + 26) % 26 + 'a';
        }
        else {
            result[i] = c;
        }
    }

    result[len] = '\0';
    return result;
}
char* encode_message(const char* text, int numRows, int caesarShift) {
    char* zigzag = zigzag_convert(text, numRows);
    char* cipher = caesar_cipher(zigzag, caesarShift);

    int cipher_len = strlen(cipher);

    // 2 prefix chars + cipher + null terminator
    char* result = malloc(cipher_len + 3);

    result[0] = 'A' + caesarShift;
    result[1] = 'a' + numRows;
    result[2] = '\0';

    strcat(result, cipher);

    free(zigzag);
    free(cipher);

    return result;
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
void out_file(char* encrypted) {
    FILE* f = fopen("encrypted.txt", "wb");
    if (!f) return;
    fwrite(encrypted, 1, strlen(encrypted), f);
    fclose(f);
}
int main() {

    char* text = load_file("encodeFile.txt");
    int numRows = rand_range(3, strlen(text) / 3);
    if (numRows == 0) {
        printf("Not enough rows to encode.\n");
        return 0;
    }
    if ( numRows >=25) {
        numRows = rand_range(4, 9);
    }
    int caesarShift = rand_range(7, 19);
    char* encoded = encode_message(text, numRows, caesarShift);
    printf("%s\n", text);
    printf("%s\n", encoded);
    out_file(encoded);
    free(encoded);
    return 0;
}