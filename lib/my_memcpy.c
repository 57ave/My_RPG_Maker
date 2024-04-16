/*
** EPITECH PROJECT, 2023
** my_hunter
** File description:
** my_memcpy
*/

#include <stddef.h>

void *my_memset(void *dest, size_t size)
{
    char *dest_bytes = (char *)dest;
    size_t byte_count = 0;

    while (byte_count < size) {
        dest_bytes[byte_count] = 0;
        byte_count++;
    }
    return dest_bytes;
}

void *my_memcpy(void *dest, void *src, size_t new_size, size_t old_size)
{
    char *dest_bytes = (char *)dest;
    char *src_bytes = (char *)src;
    size_t byte_count = 0;

    while (byte_count < old_size) {
        dest_bytes[byte_count] = src_bytes[byte_count];
        byte_count++;
    }
    while (byte_count < new_size) {
        dest_bytes[byte_count] = 0;
        byte_count++;
    }
    return dest_bytes;
}
