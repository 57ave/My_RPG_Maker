/*
** EPITECH PROJECT, 2024
** MyRPG [WSL: Ubuntu]
** File description:
** read_config
*/

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "ecs.h"
#include "macro.h"
#include "type_create.h"

static char *create_filepath(const char *path, const char *filename)
{
    char *filepath =
        malloc(sizeof(char) * (strlen(path) + strlen(filename) + 1));

    snprintf(filepath,
        strlen(path) + strlen(filename) + 1, "%s%s", path, filename);
    return filepath;
}

static int process_directory(char *filepath, entity_system_t *es)
{
    filepath = realloc(filepath, sizeof(char) * (strlen(filepath) + 2));
    strcat(filepath, "/");
    if (search_for_config_files(filepath, es) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}

static int process_file(char *filepath, struct dirent *dir_entry,
    const char *path, entity_system_t *es)
{
    struct stat sb;

    filepath = create_filepath(path, dir_entry->d_name);
    stat(filepath, &sb);
    if (S_ISDIR(sb.st_mode)) {
        if (process_directory(filepath, es) == EXIT_ERROR)
            return EXIT_ERROR;
    } else {
        printf("Loading entities from: %s\n", filepath);
        if (add_entities_from_path(es, filepath) == EXIT_ERROR)
            return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}

int search_for_config_files(const char *path, entity_system_t *es)
{
    DIR *dir_stream = opendir(path);
    struct dirent *dir_entry;
    char *filepath = NULL;

    if (!dir_stream)
        return EXIT_ERROR;
    dir_entry = readdir(dir_stream);
    while (dir_entry != NULL) {
        if (strncmp(dir_entry->d_name, ".", 1) == 0) {
            dir_entry = readdir(dir_stream);
            continue;
        }
        if (process_file(filepath, dir_entry, path, es) == EXIT_ERROR)
            return EXIT_ERROR;
        dir_entry = readdir(dir_stream);
    }
    closedir(dir_stream);
    return EXIT_SUCCESS;
}
