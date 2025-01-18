/*
    Ticket Seller V1.0                                  This code simulate a ticket seller software
                                                        moving money from customers to sellers acc.
    Code wrote by Mattia Marelli                        calculating age range discounts and presells
    on 2024 as an homework for school
*/

#include "include/header.h"
#include "boxes.h"
#include "menu.h"
#include "text.h"
#include "usergui.h"
#include "admingui.h"
#include "money.h"

/**
 * @brief avvia la procedure di acquisto del biglietto
 *
 * @param user utente che ha effetuato il login
 */
void buyProcedure(User user)
{
    Concert concert;

    const char *options[] = {
        "Acquista biglietti",
        "Mostra informazioni conto corrente"};

    int lineCount1 = sizeof(options) / sizeof(options[0]);
    int count = 0;

    // Richiesta del tipo di azione che si decidere svolgere
    switch (newMenu("Cosa desideri fare:", options, lineCount1, &count))
    {
    case 1:
        // Acquisto biglietti

        // Scegli concerto
        selectConcert(&concert);
        clearScreen();

        // Quantità di concerti
        int ticketAmount = ticketSelection(concert);
        clearScreen();

        // Stampa informazioni
        const char *ticket[] = {
            "Acquisto Biglietti",
            "",
            "di seguito ti sara\' richiesto di compilare",
            "i dati per acquistare il tuo ticket"};
        int lineCount0 = sizeof(ticket) / sizeof(ticket[0]);
        printBox(ticket, lineCount0);

        Sleep(3000);
        clearScreen();

        // Compila le informazioni dei ticket
        Ticket *tickets = compileTicketInformation(ticketAmount, concert);

        clearScreen();

        // Calcola il prezzo totale
        int sum = 0;
        for (int i = 0; i < ticketAmount; i++)
        {
            sum += tickets[i].price;
        }

        // Calcolare il prezzo al re-seller
        int sellerSum = 0;
        for (int i = 0; i < ticketAmount; i++)
        {
            if (tickets[i].age < concert.underPrice.age)
            {
                // 6% dall'under
                sellerSum += tickets[i].price * 0.6;
            }
            else if (tickets[i].age > concert.overPrice.age)
            {
                // 12% dall'over
                sellerSum += tickets[i].price * 0.12;
            }
            else
            {
                // 15% dal normal
                sellerSum += tickets[i].price * 0.15;
            }
        }

        // Stampa informazioni del prezzo
        char totalPrice[50];
        sprintf(totalPrice, "Il totale per %d biglietti: %.2f", ticketAmount, (float)sum);
        printBoxLines();
        printText(totalPrice, false, CENTER);
        printBoxLines();

        Sleep(3000);
        clearScreen();

        // Chiedi in che modo desidera pagare
        int paymentType = askForPaymentType();
        switch (paymentType - 1)
        {
        case CASH:
            manageCashPayment(sum, sellerSum, concert, user);
            break;
        case CREDIT_CARD:
            manageCardPayment(sum, sellerSum, concert, user);
            break;
        case BONIFICO:
            manageBonificoPayment(sum, sellerSum, concert, user);
            break;
        default:
            break;
        }

        // Effetua le modifiche ai dati del concerto
        concertList[concert.index].remaingTicket -= ticketAmount;

        // Aggiunta del premio
        concertList[concert.index].selledTicket += ticketAmount;
        if (concertList[concert.index].selledTicket >= 100)
        {
            // Reset Counter
            concertList[concert.index].selledTicket -= 100;
            // Premio
            concertList[concert.index].seller.cA.avaibleMoney += 50;
        }

        saveData(concertFile, userFile);

        break;
    case 2:
        // Ottieni le informazioni degli account
        getAccountInformation(user);
        break;
    default:
        break;
    }
}

int main()
{
    loadData(concertFile, userFile);

    // Imposta il charset in UTF-8
    SetConsoleOutputCP(CP_UTF8);
    clearScreen();

    // Conferma avvio programma + menu segreto per aggiungere soldi agli utenti
    printBoxLines();
    printText("Premere un tasto per avviare il programma", false, CENTER);
    printBoxLines();

    if (getch() == SECRET_KEY && userAmount > 0)
    {
        char *options[userAmount];

        int lineCount1 = sizeof(options) / sizeof(options[0]);
        int count = 0;

        for (int i = 0; i < userAmount; i++)
        {
            options[i] = userList[i].name;
        }

        int selection = newMenu("Selezione a quale utente aggiungere 1000€:", options, lineCount1, &count);
        userList[selection - 1].cA.avaibleMoney += 1000;

        printBoxLines();
        printText("Soldi aggiunti corretamente", false, CENTER);
        printBoxLines();

        Sleep(3000);

        saveData(concertFile, userFile);
    }

    // Struttura utente dove salvare le informazioni dopo il login
    User user;

    // Caricamento dei dati dai file
    loadData(concertFile, userFile);

    // Stampa la schermata di benvenuto con piccola animazione
    printWelcomeScreen(3);
    clearScreen();

    // Ciclo per eseguire continuamente la scritture a schermo del menu
    while (1)
    {
        // Se l'utente non è ancora loggato richiedi il login
        if (!user.isValid)
        {
            // Effetua il login o sign up
            user = WelcomeScreen();
            clearScreen();

            // Verifica che le credenziali non siano errate
            if (!user.isValid)
            {
                continue;
            }

            // Se sono corrette dai il benvenuto all'utente
            char welcomeMessage[50];
            sprintf(welcomeMessage, "Ciao %s, ben tornato!", user.name);

            clearScreen();
            printBoxLines();
            printText(welcomeMessage, false, CENTER);
            printBoxLines();

            Sleep(2000);
        }

        // Se l'utente non è admin avvia la procedura d'acquisto
        if (user.admin == false)
        {
            buyProcedure(user);
        }

        // Se l'utente è admin richiedi che tipo di interfaccia desidera, admin o utente
        else if (user.admin == true)
        {
            // ADMIN
            if (adminOrUSer() == 1)
            {
                // Se sceglie utente avvia la procedura d'acquisto
                buyProcedure(user);
            }
            else
            {
                // Altrimenti mostra il menu admin
                mainAdminMenu(user);
            }
        }
    }
    return 0;
}