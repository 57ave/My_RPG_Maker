/*
** EPITECH PROJECT, 2024
** floor
** File description:
** floor init
*/

#ifndef FLOOR_INIT_H
    #define FLOOR_INIT_H

    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>

typedef struct tailed_s {
    char character;
    sfTexture *texture;
    sfSoundBuffer *buffer;
    sfSound *sound;
}tailed_t;

#endif /* !floor */
