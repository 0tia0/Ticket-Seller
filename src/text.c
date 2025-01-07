#include "text.h"

/**
 * @brief stampa un testo all'interno di una box a carattere scelto con formattazione a scelta
 *
 * @param text il testo che la funzione deve stampare
 * @param externalCall se vero, il testo sarà stampato senza bordi
 */
void printText(const char *text, bool externalCall, int format)
{
    // calcola lo spazio da lasciare
    int length = strlen(text);
    int spaceToLeave = (BOX_WIDTH - length - 2) / 2;

    // togli i caraterri esterni se la chiamata della funziona è esterna alle BoxFunctions
    if (externalCall)
    {
        printf(" ");
    }
    else
    {
        printf("%c", BOX_SIDE);
    }

    switch (format)
    {
    case LEFT:
        // lascia lo spazio a sinistra
        printf(" ");

        // stampa il testo
        printf("%s", text);

        // lascia lo spazio a destra
        for (int i = 0; i < BOX_WIDTH - length - 3; i++)
        {
            printf(" ");
        }
        break;
    case RIGHT:
        // lascia lo spazio a sinistra
        for (int i = 0; i < BOX_WIDTH - length - 3; i++)
        {
            printf(" ");
        }

        // stampa il testo
        printf("%s", text);

        // lascia lo spazio a destra
        printf(" ");
        break;
    case CENTER:
        // lascia lo spazio a sinistra
        for (int i = 0; i < spaceToLeave; i++)
        {
            printf(" ");
        }

        // stampa il testo
        printf("%s", text);

        // lascia lo spazio a destra gestendo anche testi con grandezza pari
        for (int i = 0; i < spaceToLeave + ((BOX_WIDTH - length - 2) % 2); i++)
        {
            printf(" ");
        }
        break;
    default:
        break;
    }

    // togli i caraterri esterni se la chiamata della funziona è esterna alle BoxFunctions
    if (externalCall)
    {
        printf(" \n");
    }
    else
    {
        printf("%c\n", BOX_SIDE);
    }
}

/**
 * @brief pulisci il terminale
 */
void clearScreen()
{
    system("cls");
}

/**
 * @brief lascia una linea vuota nel terminale
 */
void leaveBlankLine()
{
    printf("\n");
} 