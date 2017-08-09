#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "parser.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        return -1;        
    }

    struct stat buf;
    if (fstat(fd, &buf) != 0) {
        perror("fstat");
        return -1;
    }

    char *data = (char*)malloc(buf.st_size);
    if (data == NULL) {
        perror("malloc");
        return -1;
    }

    if (read(fd, data, buf.st_size) != buf.st_size) {
        perror("read");
        return -1;
    }

    close(fd);

    struct parser_t *parser = parser_new();

    struct input_t *input = input_new(data, buf.st_size);

    struct ast_t *ast = parse(parser, input);

    display_ast(ast, type_strings);

    ast_recursive_delete(ast);
    input_delete(input);
    parser_delete(parser);

    free(data);

    return 0;
}
