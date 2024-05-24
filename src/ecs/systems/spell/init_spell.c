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

static int check_item_content(entity_system_t *es, int item_inventory,
    int entity)
{
    vec_t *component_item = es->components[ACTIVE_ITEM];
    c_inventory_t *inventory = (c_inventory_t *)
        get_comp(es, INVENTORY, entity);
    c_active_item_t *active_item = NULL;
    int item_entity = 0;

    if (!inventory)
        return EXIT_ERROR;
    item_entity = inventory->object_tab[item_inventory];
    active_item = (c_active_item_t *)
        ((void **)component_item->data)[item_entity];
    if (!active_item || !check_cooldown(active_item))
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}

static bool update_spell_position(entity_system_t *es, int entity,
    int spell_entity)
{
    c_position_t *entity_pos = get_comp(es, POSITION, entity);
    c_position_t *spell_pos = get_comp(es, POSITION, spell_entity);
    c_temporary_t *spell_temp = get_comp(es, TEMPORARY, spell_entity);

    if (!entity_pos || !spell_pos || !spell_temp)
        return false;
    sfClock_restart(spell_temp->clock);
    spell_pos->pos.x = entity_pos->pos.x;
    spell_pos->pos.y = entity_pos->pos.y - 20;
    printf("%f %f\n", spell_pos->pos.x, entity_pos->pos.x);
    return true;
}

static int search_index(entity_system_t *es)
{
    for (int i = 0; i < es->total_indexes; ++i) {
        if (get_comp(es, TEMPORARY, es->all_indexes[i]) != NULL)
            return es->all_indexes[i];
    }
    return -1;
}

int init_spell(entity_system_t *es, int item_inventory, int entity)
{
    int index = search_index(es);

    if (index < 0)
        return EXIT_ERROR;
    if (check_item_content(es, item_inventory, entity) == EXIT_ERROR)
        return EXIT_ERROR;
    if (!update_spell_position(es, entity, index))
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}

int create_spell(void *es)
{
    return init_spell((entity_system_t *)es, 0,
        ((entity_system_t *)es)->player);
}
