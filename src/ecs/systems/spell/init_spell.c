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
#include "my_lib.h"
#include "macro.h"

static bool check_cooldown(c_active_item_t *active_item)
{
    if ((sfClock_getElapsedTime(active_item->clock).microseconds / 1000000) >
    (int)active_item->time) {
        sfClock_restart(active_item->clock);
        return true;
    }
    return false;
}

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
    if (!active_item || !check_cooldown(active_item))
        return NULL;
    return active_item->file;
}

static int get_spell_entity(entity_system_t *es, int *spell_entity)
{
    es->all_indexes = realloc(es->all_indexes,
        sizeof(int) * (es->total_indexes + 1));
    if (es->all_indexes == NULL)
        return EXIT_ERROR;
    es->all_indexes[es->total_indexes] = es->max_index;
    *spell_entity = es->max_index;
    es->max_index += 1;
    es->total_indexes += 1;
    return EXIT_SUCCESS;
}

static bool update_spell_position(entity_system_t *es, int entity,
    int spell_entity)
{
    c_position_t *entity_pos = get_comp(es, POSITION, entity);
    c_position_t *spell_pos = get_comp(es, POSITION, spell_entity);

    if (!entity_pos || !spell_pos)
        return false;
    spell_pos->pos.x = entity_pos->pos.x;
    spell_pos->pos.y = entity_pos->pos.y - 20;
    return true;
}

int init_spell(entity_system_t *es, int item_inventory, int entity)
{
    int spell_entity = 0;
    char **content = get_item_content(es, item_inventory, entity);
    obj_t *obj = malloc(sizeof(obj_t));
    int tmp = 0;
    int err = 0;

    if (!obj || !content)
        return -1;
    get_object_values(content, &tmp, obj, &err);
    if (err == -1 || get_spell_entity(es, &spell_entity) == EXIT_ERROR)
        return -1;
    obj->obj_name = my_strdup_delim(content[0], ']');
    if (obj_to_components(es, obj, spell_entity) == EXIT_ERROR) {
        update_spell_position(es, entity, spell_entity);
        return -1;
    }
    set_vector_size(es, es->total_indexes);
    if (update_spell_position(es, entity, spell_entity))
            return -1;
    return spell_entity;
}

int create_spell(void *es)
{
    return init_spell((entity_system_t *)es, 0,
        ((entity_system_t *)es)->player);
}
