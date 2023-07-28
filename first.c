#include <stdio.h>

/**
 * main - Entry point of the program
 * Return: Always 0 (Success)
 */
int main(void)
{
    int num1 = 10;
    int num2 = 20;
    int result = multiply_and_add(num1, num2);
    
    printf("The result of multiplying %d and adding %d is %d.\n", num1, num2, result);

    return (0);
}

/**
 * multiply_and_add - Function to multiply two integers and then add
 * @a: First integer
 * @b: Second integer
 * Return: The result of (a * b) + b
 */
int multiply_and_add(int a, int b)
{
    return (a * b) + b;
}

