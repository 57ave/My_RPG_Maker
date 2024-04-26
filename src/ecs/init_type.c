/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** init_type
*/

#include <string.h>
#include <stdlib.h>
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
    return EXIT_SUCCESS;
}

int add_entities_type(entity_system_t *es, entity_t type)
{
    char **content = read_file(ENTITY_TYPE_CREATER[type]);
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
            es->nb_of_entities + 1);
        if (es->entity_indexes == NULL)
            return NULL;
        es->entity_indexes[es->nb_of_entities] = (int)entity;
        es->nb_of_entities += 1;
    }
    return EXIT_SUCCESS;
}

static vec_t *init_component_vector(entity_system_t *es, unsigned long size)
{
    es->components = init_vector(es->components, size);
    if (!es->components)
        return NULL;
    for (size_t i = 0; i < NB_OF_COMPONENT; ++i) {
        es->components[i].data = calloc(sizeof(vec_t), 1);
        if (!es->components[i].data)
            return NULL;
        es->components[i].data = init_vector(es->components[i].data,
            COMPONENT_INIT_DATA[i].size);
        if (!es->components[i].data)
            return NULL;
    }
    return es->components;
}

entity_system_t *init_entity_system(entity_system_t *es)
{
    es->entity_indexes = NULL;
    es->nb_of_entities = 0;
    if (!init_component_vector(es, sizeof(vec_t))) {
        return NULL;
    }
    for (entity_t i = 0; i < LAST_ENTITY; i++) {
        if (add_entities_type(es, i) == EXIT_ERROR) {
            return NULL;
        }
    }
    return es;
}
