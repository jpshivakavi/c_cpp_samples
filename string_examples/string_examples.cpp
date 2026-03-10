// string_examples.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

// Simple custom atoi function implementation
int my_atoi(const char* string)
{
    int i = 0;
    while (*string)
    {
        i = (i << 3) + (i << 1) + (*string - '0');
        string++;
    }
    return i;
}

// Simple custom memmove impementation
void* my_memmove(void* dest, const void* src, size_t size)
{
    unsigned char* p1 = (unsigned char *) dest;
    const unsigned char* p2 = (const unsigned char*)src;

    p2 = p2 + size;
    // Check if p1 appears in the middle of p2 buffer
    // This while loop checks if dest is overlapping with the source
    while ((p2 != src) && (--p2 != dest))
        ;

    if (p2 != src)
    {
        printf("\n Overlap detected\n");
        // Overlap detected
        p2 = (const unsigned char*)src;
        p2 = p2 + size;
        p1 = p1 + size;

        while (size--)
        {
            *--p1 = *--p2;
        }
    }
    else
    {
        // No overlap
        while (size--)
        {
            *p1++ = *p2++;
        }
    }

    return dest;
}

// function to convert number of given base to string
char* num_to_string(unsigned int num, int base)
{
    static char buf[33] = { 0 };
    char* ptr = NULL;

    ptr = &buf[sizeof(buf) - 1];
    *ptr = '\0';
    do {
        *--ptr = "0123456789abcdef"[num % base];
        num = num / base;
    } while (num != 0);

    return ptr;
}

// custom printf function
void my_printf(char* fmt, ...)
{
    char* ptr_fmt = NULL;
    int i = 0;
    unsigned int u = 0;
    char* s = NULL;
    va_list argp = NULL;
    va_start(argp, fmt);
    ptr_fmt = fmt;
    for (ptr_fmt = fmt; *ptr_fmt != '\0'; ptr_fmt++)
    {
        if (*ptr_fmt != '%')
        {
            putchar(*ptr_fmt);
            continue;
        }
        ptr_fmt++;

        switch (*ptr_fmt)
        {
            case 'c':
                i = va_arg(argp, char);
                putchar(i);
                break;

            case 'd':
                i = va_arg(argp, int);
                fputs(num_to_string(i, 10), stdout);
                break;

            case 's':
                s = va_arg(argp, char*);
                fputs(s, stdout);
                break;
        }
    }
    va_end(argp);
}

char* my_strcpy(char* dest, const char* src)
{
    char* ptr = dest;
    while (*ptr++ = *src++);
    return dest;
}

int my_strcmp(const char* str1, const char* str2)
{
    while (*str1 == *str2)
    {
        if (*str1 == '\0')
        {
            return 0;
        }
        str1++;
        str2++;
    }

    if (*str1 > *str2)
    {
        return 1;
    }
    else {
        return -1;
    }
}

void my_strcmp_test()
{
    int result = 0;

    result = my_strcmp("JP", "PJ");
    printf("Result of comparison of JP and PJ = %d\n", result);

    result = my_strcmp("JP", "JP");
    printf("Result of comparison of JP and JP = %d\n", result);

    result = my_strcmp("PJ", "JP");
    printf("Result of comparison of PJ and JP = %d\n", result);

}

void my_atoi_test()
{
    char data[20] = { 0 };
    printf("Enter number string:\n");
    scanf_s("%19s", data, 20);
    printf("Data entered is :\n");
    printf("%s\n", data);

    printf("Converting the string to Integer data format\n");
    int data_i = my_atoi(data);
    printf("Value of data_i (int) = %d", data_i);
}

void my_memmove_test()
{
    // memove operations
    char* src = (char*)malloc(sizeof(char) * 20);
    if (src != NULL)
    {
        int size = 10;
        memset(src, '\0', 20);
        strcpy_s(src, 20, "ABCDEFGHI");
        char* dest = src + 2;
        printf("\nUsing my_memmove function to copy from src to dest\n");
        printf("Before memmove src = [%s]\n", src);
        printf("Before memmove dest = [%s]\n", dest);

        my_memmove(dest, src, 10);

        printf("After memmove src = [%s]\n", src);
        printf("After memmove dest = [%s]\n", dest);

    }
    else
    {
        printf("Failed to allocate memory to dest\n");
    }

}


void my_strcpy_test()
{
    char dest[30] = { 0 };
    const char src[] = "This is Jayaprakash";
    char* ptr = NULL;
    ptr = my_strcpy(dest, src);
    printf("Copied string = %s\n", ptr);
}

int main()
{
    // my_atoi_test()
    // my_memmove_test()
    // usage of my_printf to print char and int
    my_printf((char *)"The character is = %c number = %d name = %s\n", 'C', 100, (char *)"Jayaprakash");
    my_strcpy_test();
    my_strcmp_test();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
