/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** animation system
*/

#include <SFML/Graphics.h>
#include "ecs.h"
#include "components.h"
#include "systems.h"
#include "filter_entity.h"

bool put_in_inventory(entity_system_t *es, int object, int entity)
{
    c_inventory_t *inventory = get_comp(es, INVENTORY, entity);

    for (size_t i = 0; i < inventory->size; i++) {
        if (inventory->object_tab[i] == 0) {
            inventory->object_tab[i] = object;
            return true;
        }
    }
    return false;
}

void change_mode(entity_system_t *es, int entity)
{
    c_game_mode_t *obj_mode = get_comp(es, GAME_MODE, entity);

    obj_mode->mode = 2;
}

void pick_entities(entity_system_t *es, int entity,
    entity_filter_t *filter)
{
    for (int i = 0; i < filter->number; ++i) {
        if (collision_entities(es, entity, filter->indexes[i]) &&
            put_in_inventory(es, entity, filter->indexes[i])) {
            change_mode(es, entity);
            return;
        }
    }
}

void pick_system(entity_system_t *es)
{
    entity_filter_t *pickable = filter_entities(4,
        es, DRAW, POSITION, PICKABLE, COLLISION);
    entity_filter_t *inventory_perso = filter_entities(4,
        es, DRAW, POSITION, INVENTORY, COLLISION);

    for (int i = 0; i < pickable->number; i++) {
        pick_entities(es, pickable->indexes[i], inventory_perso);
    }
    if (pickable != NULL){
        free_filter(pickable);
    }
    if (inventory_perso != NULL) {
        free_filter(inventory_perso);
    }
}
