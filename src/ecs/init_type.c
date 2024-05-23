/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** init_type
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "macro.h"
#include "my_toml.h"
#include "components.h"
#include "type_create.h"
#include "ecs.h"
#include "vector.h"

static int check_component(size_t cmpt_id,
    entity_system_t *es, obj_t *obj, int entity)
{
    for (int i = 0; obj->data[i]; ++i) {
        if (strncmp(obj->data[i]->name, COMPONENT_INIT_DATA[cmpt_id].name,
            strlen(COMPONENT_INIT_DATA[cmpt_id].name)) != 0) {
            continue;
        }
        return COMPONENT_INIT_DATA[cmpt_id].init(es, obj, cmpt_id, entity);
    }
    return EXIT_SUCCESS;
}

int obj_to_components(entity_system_t *es, obj_t *obj, int entity)
{
    for (size_t cmpt_id = 0; cmpt_id < NB_OF_COMPONENT; cmpt_id++) {
        if (check_component(cmpt_id, es, obj, entity) == EXIT_ERROR) {
            return EXIT_ERROR;
        }
    }
    if (strcmp(obj->obj_name, "PLAYER") == 0) {
        if (es->player != -1) {
            dprintf(2, "you can't define 2 players... sry\n");
            return EXIT_ERROR;
        }
        es->player = entity;
    }
    return EXIT_SUCCESS;
}

int set_vector_size(entity_system_t *es, int index)
{
    for (size_t cmpt_id = 0; cmpt_id < NB_OF_COMPONENT; cmpt_id++) {
        es->components[cmpt_id] = push_index_vector(es->components[cmpt_id],
            NULL, COMPONENT_INIT_DATA[cmpt_id].size, index);
    }
    return EXIT_SUCCESS;
}

int add_entities_from_path(entity_system_t *es, char const *filepath)
{
    char **content = read_file(filepath);
    obj_t **obs = NULL;
    int offset = 0;

    obs = get_object(content, &offset, obs);
    if (obs == NULL)
        return EXIT_ERROR;
    for (int i = 0; obs[i] != NULL; i++) {
        if (obj_to_components(es, obs[i], es->total_indexes) == EXIT_ERROR) {
            free_obj(obs);
            return EXIT_ERROR;
        }
        es->all_indexes = realloc(es->all_indexes,
            sizeof(int) * (es->total_indexes + 1));
        if (es->all_indexes == NULL)
            return EXIT_ERROR;
        es->all_indexes[es->total_indexes] = es->total_indexes;
        es->total_indexes += 1;
    }
    return set_vector_size(es, es->total_indexes);
}

static vec_t **init_component_vector(entity_system_t *es, unsigned long size)
{
    es->components = calloc(sizeof(vec_t *), NB_OF_COMPONENT);
    if (!es->components)
        return NULL;
    for (size_t i = 0; i < NB_OF_COMPONENT; ++i) {
        es->components[i] = calloc(size, 1);
        if (!es->components[i])
            return NULL;
        es->components[i] = init_vector(es->components[i],
            COMPONENT_INIT_DATA[i].size);
        if (!es->components[i])
            return NULL;
    }
    return es->components;
}

entity_system_t *init_entity_system(entity_system_t *es)
{
    es->all_indexes = NULL;
    es->total_indexes = 0;
    es->player = -1;
    if (!init_component_vector(es, sizeof(vec_t))) {
        return NULL;
    }
    if (search_for_config_files(ENTITY_DIRECTORY_PATH, es) == EXIT_ERROR) {
        return NULL;
    }
    if (es->player == -1) {
        dprintf(2, "player not initialized\n");
        return NULL;
    }
    return es;
}
