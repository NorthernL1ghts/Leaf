#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long file_size(FILE* file) {
    if (!file) { return 0; }
    fpos_t original = 0;
    if (fgetpos(file, &original) != 0) {
        printf("fgetpos() failed: %i\n", errno);
        return 0;
    }
    fseek(file, 0, SEEK_END);
    long out = ftell(file);
    if (fsetpos(file, &original) != 0) {
        printf("fsetpos() failed: %i\n", errno);
    }
    return out;
}

char* file_contents(char* path) {
    FILE* file = fopen(path, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", path);
        return NULL;
    }
    long size = file_size(file);
    char* contents = malloc(size + 1);
    assert(contents && "Could not allocate buffer for file contents");
    char* write_it = contents;
    size_t bytes_read = 0;
    while (bytes_read < (size_t)size) {
        size_t bytes_read_this_iteration = fread(write_it, 1, (size_t)size - bytes_read, file);
        if (ferror(file)) {
            printf("Error: Could not read file %s\n", path);
            free(contents);
            fclose(file);
            return NULL;
        }

        bytes_read += bytes_read_this_iteration;
        write_it += bytes_read_this_iteration;

        if (feof(file)) { break; }
    }
    contents[bytes_read] = '\0';
    fclose(file);
    return contents;
}

void print_usage(char** argv) {
    printf("USAGE: %s <path_to_file_to_compile>\n", argv[0]);
}

typedef struct Error {
    enum ErrorType {
        ERROR_NONE = 0,
        ERROR_ARGUMENTS,
        ERROR_TYPE,
        ERROR_GENERIC,
        ERROR_SYNTAX,
        ERROR_TODO,
        ERROR_MAX,
    } type;
    char* msg;
} Error;

Error ok = { ERROR_NONE, NULL };

void print_error(Error err) {
    if (err.type == ERROR_NONE) {
        return;
    }
    printf("ERROR: ");
    assert(ERROR_MAX == 6);
    switch (err.type) {
    default:
        printf("Unkown error type...");
        break;
    case ERROR_TODO:
        printf("TODO (not implemented)");
        break;
    case ERROR_SYNTAX:
        printf("Invalid syntax");
        break;
    case ERROR_TYPE:
        printf("Mismatched types");
        break;
    case ERROR_ARGUMENTS:
        printf("Invalid arguments");
        break;
    case ERROR_GENERIC:
        break;
    case ERROR_NONE:
        break;
    }
    putchar('\n');
    if (err.msg) {
        printf("     : %s\n", err.msg);
    }
}

#define ERROR_CREATE(n, t, msg)           \
    Error (n) = { (t), (msg) }

#define ERROR_PREP(n, t, message)           \
    (n).type = (t);                          \
    (n).msg = (message);

const char *whitespace = " \r\n";
const char *delimiters = " \r\n,{}():";

/// Lex the next token from SOURCE, and point to it with BEG and END.
Error lex(char* source, char** beg, char** end) {
    Error err = ok;
    if (!source || !beg || !end) {
        ERROR_PREP(err, ERROR_ARGUMENTS, "Can not lex empty source.");
        return err;
    }
    *beg = source;
    *beg += strspn(*beg, whitespace); // Skip whitespace
    if (**end == '\0') { return err; }
    *end = *beg;
    *end += strcspn(*beg, delimiters); // Skip to next delimiter
    if (*end == *beg) {
        *end += 1;
    }
    return err;
}

Error parse_expr(char* source) {
    char* beg = source;
    char* end = source;
    Error err = ok;
    while ((err = lex(end, &beg, &end)).type == ERROR_NONE) {
        if (end - beg == 0) { break;}
        printf("lexed: %.*s\n", end - beg, beg);
    }
    return err;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        print_usage(argv);
        exit(0);
    }

    char* path = argv[1];
    char* contents = file_contents(path);
    if (contents) {
        // printf("Contents of %s:\n--------------------------------\n%s\n--------------------------------\n", path, contents);

        Error err = parse_expr(contents);
        print_error(err);

        free(contents);
    }
    
    return 0;
}