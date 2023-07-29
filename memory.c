#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * This function frees the memory block pointed to by 'ptr' and sets the
 * pointer address to NULL to avoid potential use-after-free bugs. If 'ptr'
 * is already NULL or not pointing to a valid memory block, the function
 * does nothing and returns 0.
 *
 * It is important to pass a pointer to a pointer (void **) as an argument to
 * this function to ensure the actual pointer address is modified. For example,
 * if you have a pointer char *str and you want to free it and set it to NULL,
 * you would call bfree((void **)&str).
 *
 * Example usage:
 * char *str = malloc(10);
 * // Do something with str...
 * bfree((void **)&str); // Free the memory and set str to NULL
 * // Now str is NULL, and it is safe to check if it's NULL before using it.
 *
 * Return: 1 if 'ptr' was freed and set to NULL, otherwise 0.
 */
int bfree(void **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);
        *ptr = NULL;
        return 1;
    }
    return 0;
}

