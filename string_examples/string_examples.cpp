// string_examples.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <malloc.h>
#include <string.h>

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

int main()
{
    char data[20] = { 0 };
    printf("Enter number string:\n");
    scanf_s("%19s", data, 20);
    printf("Data entered is :\n");
    printf("%s\n", data);

    printf("Converting the string to Integer data format\n");
    int data_i = my_atoi(data);
    printf("Value of data_i (int) = %d", data_i);


    // memove operations
    char* src = (char* ) malloc(sizeof(char) * 20);
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
        return 1;
    }

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
