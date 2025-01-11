#include "menu.h"
#include "text.h"

/**
 * @brief stampa un menu "a tendina" utilizzabile che permette all'utente di scegliere un valore in una lista
 *
 * @param question la domanda da mettere al di sopra delle opzioni
 * @param text le opzioni
 * @param lineCount il numero di opzioni
 * @param count la conta del numero di volte che si ha inserito un output, puo essere un valore passato e inizializzato pari a 0
 * @return int la voce scelta nella listsa
 */
int newMenu(char *question, const char *text[], int lineCount, int *count)
{
    int currentSelection = 0;
    int keyPressed;

    while (1)
    {
        clearScreen();
        printBoxLines();
        printText(question, false, CENTER);
        printBoxLines();

        for (int i = 0; i < lineCount + 1; i++)
        {
            char buffer[BOX_WIDTH] = {0};
            if (i == 0)
            {
                if (currentSelection == 0)
                {
                    sprintf(buffer, " * Esci");
                }
                else
                {
                    sprintf(buffer, " - Esci");
                }
                printText(buffer, false, LEFT);
                printText("", false, CENTER);
            }
            else
            {
                if (currentSelection == i)
                {
                    sprintf(buffer, " * %s", text[i - 1]);
                }
                else
                {
                    sprintf(buffer, " - %s", text[i - 1]);
                }
                printText(buffer, false, LEFT);
            }
        }

        printBoxLines();

        keyPressed = _getch();
        if (keyPressed == 224)
        {
            keyPressed = _getch();
            if (keyPressed == UP_ARROW)
            {
                currentSelection = (currentSelection - 1 + (lineCount + 1)) % (lineCount + 1);
            }
            else if (keyPressed == DOWN_ARROW)
            {
                currentSelection = (currentSelection + 1) % (lineCount + 1);
            }
        }
        else if (keyPressed == ENTER_KEY)
        {
            if (currentSelection == 0)
            {
                exit(0);
            }
            return currentSelection;
        }
        else if (keyPressed == ESC_KEY)
        {
            exit(0);
        }
    }
}

/**
 * @brief stampa un menu "a tendina" utilizzabile che permette all'utente di scegliere un concerto (non souldout) da una lista
 * 
 * @param count la conta del numero di volte che si ha inserito un output, puo essere un valore passato e inizializzato pari a 0
 * @return int la voce scelta nella listsa 
 */
int concertMenu(int *count)
{
    int currentSelection = 0;
    int keyPressed;

    // Crea una lista per identificare i concerti sold out
    int soldoutConcert[AVAIBLE_CONCERT + 1];
    for (int i = 0; i < AVAIBLE_CONCERT + 1; i++)
    {
        if (concertList[i].remaingTicket == 0)
        {
            soldoutConcert[i] = i + 1;
        }
    }

    // Ciclo che si ripete fino a quando la scelta non è valida
    while (1)
    {
        clearScreen();
        printBoxLines();
        printText("Scegli un concerto", false, CENTER);
        printBoxLines();

        for (int i = 0; i < AVAIBLE_CONCERT + 1; i++)
        {
            char buffer[BOX_WIDTH] = {0};
            if (i == 0)
            {
                if (currentSelection == 0)
                {
                    sprintf(buffer, " * Esci");
                }
                else
                {
                    sprintf(buffer, " - Esci");
                }
                printText(buffer, false, LEFT);
                printText("", false, CENTER);
            }
            else
            {
                if (concertList[i - 1].remaingTicket == 0)
                {
                    if (currentSelection == i)
                    {
                        sprintf(buffer, " * %s - SOLD OUT", concertList[i - 1].name);
                    }
                    else
                    {
                        sprintf(buffer, " - %s - SOLD OUT", concertList[i - 1].name);
                    }
                    printText(buffer, false, LEFT);
                    continue;
                }

                if (currentSelection == i)
                {
                    sprintf(buffer, " * %s", concertList[i - 1].name);
                }
                else
                {
                    sprintf(buffer, " - %s", concertList[i - 1].name);
                }
                printText(buffer, false, LEFT);
            }
        }

        printBoxLines();

        keyPressed = _getch();
        if (keyPressed == 224)
        {
            keyPressed = _getch();
            if (keyPressed == UP_ARROW)
            {
                currentSelection = (currentSelection - 1 + (AVAIBLE_CONCERT + 1)) % (AVAIBLE_CONCERT + 1);
            }
            else if (keyPressed == DOWN_ARROW)
            {
                currentSelection = (currentSelection + 1) % (AVAIBLE_CONCERT + 1);
            }
        }
        else if (keyPressed == ENTER_KEY)
        {
            if (currentSelection == 0)
            {
                exit(0);
            }

            for (int i = 0; i < AVAIBLE_CONCERT + 1; i++)
            {
                if (currentSelection == soldoutConcert[i])
                {
                    concertMenu(count);
                }
            }

            return currentSelection;
        }
        else if (keyPressed == ESC_KEY)
        {
            exit(0);
        }
    }

    free(soldoutConcert);
}