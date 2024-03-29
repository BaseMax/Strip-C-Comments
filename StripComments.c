/*
 * Name: Strip C Comments
 * Description: A C program to strip comments from a c file and output the result to a new file.
 * Date: 2022-02-11
 * Author: Max Base
 * Repository: https://github.com/BaseMax/Strip-C-Comments
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *EXTENSIONS[] = {"c", "py"};

// Read whole of a file and return char*
char *file_read(char *filepath)
{
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL)
    {
        // printf("Could not open file %s\n", filepath);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, fp);

    return string;
}

// Remove all of inline comments from a string
char *strip_inline_comments(char *input)
{
    char *output = malloc(strlen(input) + 1);
    char *p = input;
    char *q = output;
    while (*p)
    {
        if (*p == '/' && *(p + 1) == '/')
        {
            while (*p && *p != '\n')
            {
                p++;
            }
        }
        else
        {
            *q++ = *p++;
        }
    }
    *q = '\0';
    return output;
}

// Remove all of multiline comments from a string
char *strip_multiline_comments(char *input)
{
    char *output = malloc(strlen(input) + 1);
    char *p = input;
    char *q = output;
    int comment = 0;
    while (*p)
    {
        if (*p == '/' && *(p + 1) == '*')
        {
            comment = 1;
            p += 2;
        }
        else if (*p == '*' && *(p + 1) == '/')
        {
            comment = 0;
            p += 2;
        }
        else if (!comment)
        {
            *q++ = *p++;
        }
        else
        {
            p++;
        }
    }
    *q = '\0';
    return output;
}

char *strip_hash_sign_comments(char *input)
{
    char *output = (char *)malloc(strlen(input) + 1);
    char *p = input;
    char *q = output;

    while (*p)
    {
        if (*p == '#')
            while (*p != '\n' && *p)
                p++;
        else
            *q++ = *p++;
    }
    *q = '\0';
    return output;
}

// Trim and remove space, tab, and empty line only from first and last of a string
char *trim(char *input)
{
    char *output = malloc(strlen(input) + 1);
    char *p = input;
    char *q = output;
    int skip = 1;
    while (*p)
    {
        if (*p == ' ' || *p == '\t' || *p == '\n')
        {
            if (!skip)
            {
                *q++ = *p;
            }
        }
        else
        {
            skip = 0;
            *q++ = *p;
        }
        p++;
    }
    *q = '\0';
    return output;
}

// remove_two_or_more_empty_lines
char *remove_two_or_more_empty_lines(char *input)
{
    char *output = malloc(strlen(input) + 1);
    char *p = input;
    char *q = output;
    int skip = 0;
    while (*p)
    {
        if (*p == '\n')
        {
            if (skip)
            {
                skip = 0;
            }
            else
            {
                skip = 1;
                *q++ = *p;
            }
        }
        else
        {
            skip = 0;
            *q++ = *p;
        }
        p++;
    }
    *q = '\0';
    return output;
}

// Extract extension of file name
char *extract_extension(char *name)
{
    char *extension = (char *)malloc(strlen(name) + 1);
    if (extension == NULL)
        return NULL;
    char *ptr = name;
    char *current = extension;
    while (*ptr && *ptr != '.')
        ptr++;
    if (*ptr == '.')
        ptr++;
    while (*ptr)
        *current++ = *ptr++;
    return extension;
}

char *comment_remove(char *content, char *file_name)
{
    char *extension = extract_extension(file_name);
    if (strcmp(extension, *(EXTENSIONS + 0)) == 0)
    {
        content = strip_inline_comments(content);
        content = strip_multiline_comments(content);
    }
    else if (strcmp(extension, *(EXTENSIONS + 1)) == 0)
    {
        content = strip_hash_sign_comments(content);
    }
    content = remove_two_or_more_empty_lines(content);
    content = trim(content);
    free(extension);
    return content;
}

// Start point
int main(int argc, char **argv)
{
    if (argc == 1)
    {
        printf("\nUsage: %s <file>\n\n", argv[0]);
        return 1;
    }

    char *data = file_read(argv[1]);
    if (data == NULL)
    {
        fprintf(stderr, "Could not read file %s\n", argv[1]);
        return 1;
    }

    data = comment_remove(data, argv[1]);

    if (argc == 3)
    {
        FILE *fp = fopen(argv[2], "w");
        if (fp == NULL)
        {
            fprintf(stderr, "Could not open to create file %s\n", argv[2]);
            return 1;
        }
        fprintf(fp, "%s", data);
        fclose(fp);
    }
    else
    {
        printf("%s\n", data);
    }

    free(data);

    return 0;
}
