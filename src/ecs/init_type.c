/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** init_type
*/

#include "macro.h"
#include "my_toml.h"
#include "components.h"
#include "type_create.h"
#include "ecs.h"
#include "vector.h"

int obj_to_components(entity_system_t *es, obj_t *obj, int entity)
{
    for (component_t cmpt_id = 0; cmpt_id < LAST_COMPONENT; cmpt_id++) {
        if (COMPONENT_INIT_DATA[cmpt_id].init(es, obj, cmpt_id, entity)
            == EXIT_ERROR) {
            return EXIT_ERROR;
        }
    }
    return EXIT_SUCCESS;
}

int add_entities_type(entity_system_t *es, entity_t type)
{
    char **content = read_file(entity_type_creater[type]);
    obj_t **obj_tab = NULL;
    int offset = 0;

    for (int i = 0; content[i]; ++i)
        printf("%s\n", content[i]);
    obj_tab = get_object(content, &offset, obj_tab);
    if (obj_tab == NULL) {
        return EXIT_ERROR;
    }
    for (int entity = 0; obj_tab[entity] != NULL; entity++) {
        if (obj_to_components(es, obj_tab[entity], entity) == EXIT_ERROR) {
            free_obj(obj_tab);
            return EXIT_ERROR;
        }
    }
    return EXIT_SUCCESS;
}

entity_system_t *init_entity_system(entity_system_t *es)
{
    es->entity_state = init_vector(es->entity_state, sizeof(int));
    if (es->entity_state == NULL) {
        return NULL;
    }
    for (entity_t i = 0; i < LAST_ENTITY; i++) {
        if (add_entities_type(es, i) == EXIT_ERROR) {
            return NULL;
        }
    }
    return es;
}
