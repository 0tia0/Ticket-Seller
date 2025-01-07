#include "boxes.h"

/**
 * @brief stampa il lati del box
 */
void printBoxSide()
{
    printf("%c", BOX_SIDE);
    for (int i = 0; i < BOX_WIDTH - 2; i++)
    {
        printf(" ");
    }
    printf("%c", BOX_SIDE);
}

/**
 * @brief stampa la parte superio del box
 */
void printBoxLines()
{
    printf("%c", BOX_SIDE);
    for (int i = 0; i < BOX_WIDTH - 2; i++)
    {
        printf("%c", BOX_CHAR);
    }
    printf("%c", BOX_SIDE);
    printf("\n");
}

/**
 * @brief stampa diverse linee di testo centrate in un box
 *
 * @param text le linee da stampare
 * @param lineCount la quantita delle linee
 */
void printBox(const char *text[], int lineCount)
{
    printBoxLines();

    // stampa le linee centrate
    for (int i = 0; i < lineCount; i++)
    {
        printText(text[i], false, CENTER);
    }

    printBoxLines();
}