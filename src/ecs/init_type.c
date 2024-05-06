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

int add_entities_from_path(entity_system_t *es, char const *filepath)
{
    char **content = read_file(filepath);
    obj_t **obj_tab = NULL;
    int offset = 0;

    obj_tab = get_object(content, &offset, obj_tab);
    if (obj_tab == NULL)
        return EXIT_ERROR;
    for (int entity = 0; obj_tab[entity] != NULL; entity++) {
        if (obj_to_components(es, obj_tab[entity], entity) == EXIT_ERROR) {
            free_obj(obj_tab);
            return EXIT_ERROR;
        }
        es->entity_indexes = realloc(es->entity_indexes,
            sizeof(int) * (es->nb_of_entities + 1));
        if (es->entity_indexes == NULL)
            return EXIT_ERROR;
        es->entity_indexes[es->nb_of_entities] = entity;
        es->nb_of_entities += 1;
    }
    return EXIT_SUCCESS;
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
    es->entity_indexes = NULL;
    es->nb_of_entities = 0;
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