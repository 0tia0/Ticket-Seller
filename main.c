/*
    Ticket Seller V1.0                                  This code simulate a ticket seller software
                                                        moving money from customers to sellers acc.
    Code wrote by Mattia Marelli                        calculating age range discounts and presells
    on 2024 as an homework for school
*/

#include "include/header.h"
#include "file.h"
#include "boxes.h"
#include "menu.h"
#include "text.h"
#include "usergui.h"
#include "admingui.h"
#include "money.h"

int main()
{

    loadData(concertFile, userFile);

    while (1)
    {

        printWelcomeScreen(3);
        clearScreen();

        User user = WelcomeScreen();
        clearScreen();

        if (!user.isValid)
        {
            continue;
        }

        char welcomeMessage[50];
        sprintf(welcomeMessage, "Ciao %s, ben tornato!", user.name);

        clearScreen();
        printBoxLines();
        printText(welcomeMessage, false, CENTER);
        printBoxLines();

        Sleep(2000);

        if (user.admin == false)
        {
            // USER
            Concert concert;
            selectConcert(&concert);
            clearScreen();

            int ticketAmount = ticketSelection(&concert);
            clearScreen();

            const char *ticket[] = {
                "Acquisto Biglietti",
                "",
                "di seguito ti sara\' richiesto di compilare",
                "i dati per acquistare il tuo ticket"};
            int lineCount0 = sizeof(ticket) / sizeof(ticket[0]);
            printBox(ticket, lineCount0);

            Sleep(3000);
            clearScreen();

            Ticket *tickets = compileTicketInformation(ticketAmount, concert);

            clearScreen();

            int sum = 0;
            for (int i = 0; i < ticketAmount; i++)
            {
                sum += tickets[i].price;
            }

            char totalPrice[50];
            sprintf(totalPrice, "Il totale per %d biglietti: %.2f", ticketAmount, (float)sum);
            printBoxLines();
            printText(totalPrice, false, CENTER);
            printBoxLines();

            Sleep(3000);
            clearScreen();

            int paymentType = askForPaymentType();
            printf("\n\n%d", paymentType);
            switch (paymentType - 1)
            {
            case CASH:
                manageCashPayment(sum, &concert);
                break;
            case CREDIT_CARD:
                manageCardPayment;
                break;
            case BONIFICO:
                manageBonificoPayment;
                break;
            default:
                break;
            }
        }
        else if (user.admin == true)
        {
            // ADMIN
            mainAdminMenu(user.cA);
        }
    }

    return 0;
}