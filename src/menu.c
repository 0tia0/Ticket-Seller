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

        keyPressed = _getch(); // Lettura input
        if (keyPressed == 224)
        {
            keyPressed = _getch(); // Lettura del secondo byte per i tasti speciali
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
                exit(0); // Uscita
            }
            return currentSelection;
        } 
        else if (keyPressed == ESC_KEY)
        {
            exit(0);
        }
    }
}

int login(User *userList, int listSize)
{
    int user;
    char pass[25];

    int step;

    clearScreen();
    printBoxLines();
    printText("Inserire il codice utente", false, CENTER);
    printBoxLines();

    printf("\n?:");
    scanf("%d", &user);

    leaveBlankLine();
    printBoxLines();
    printText("Inserire la password", false, CENTER);
    printBoxLines();

    printf("\n?:");
    fgets(pass, sizeof(pass) / sizeof(char), stdin);

    for (int i = 0; i < listSize; i++)
    {
        if (userList[i].username == user)
        {
            step++;
        }

        if (userList[i].pass == pass)
        {
            step++;
        }

        if(step==2) {
            return user;
        } else {
            continue;
        }
    }

    return 0;
}