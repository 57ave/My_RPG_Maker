/*
** EPITECH PROJECT, 2024
** init_spell
** File description:
** init_spell
*/

#include <stdlib.h>
#include <math.h>
#include "ecs.h"
#include "components.h"
#include "filter_entity.h"
#include "systems.h"
#include "macro.h"

static char **get_item_content(entity_system_t *es, int item_inventory,
    int entity)
{
    vec_t *component_item = es->components[ACTIVE_ITEM];
    vec_t *component_inventory = es->components[INVENTORY];
    c_inventory_t *inventory = (c_inventory_t *)
        ((void **)component_inventory->data)[entity];
    c_active_item_t *active_item = NULL;
    int item_entity = 0;

    if (!inventory)
        return NULL;
    item_entity = inventory->object_tab[item_inventory];
    active_item = (c_active_item_t *)
        ((void **)component_item->data)[item_entity];
    if (!active_item)
        return NULL;
    return active_item->file;
}

static int get_spell_entity(entity_system_t *es, int *spell_entity)
{
    es->all_indexes = realloc(es->all_indexes,
            sizeof(int) * (es->total_indexes + 1));
    if (es->all_indexes == NULL)
        return EXIT_ERROR;
    es->all_indexes[es->total_indexes] = es->total_indexes;
    *spell_entity = es->total_indexes;
    es->total_indexes += 1;
    return EXIT_SUCCESS;
}

int init_spell(entity_system_t *es, int item_inventory, int entity)
{
    int spell_entity = 0;
    char **content = get_item_content(es, item_inventory, entity);
    obj_t *obj = malloc(sizeof(obj_t));
    int tmp = 0;

    if (!obj || !content)
        return -1;
    get_object_values(content, &tmp, obj);
    if (get_spell_entity(es, &spell_entity) == EXIT_ERROR)
        return -1;
    if (obj_to_components(es, obj, spell_entity) == EXIT_ERROR)
        return -1;
    set_vector_size(es, es->total_indexes);
    return spell_entity;
}
