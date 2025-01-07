#include "file.h"

/**
 * @brief salva una lista di strutture Concert all'interno di un file
 *  
 * @param fileName nome del file per il salvataggio dei dati
 * @param c lista dei concerti da salvare
 */
void saveConcertToFile(char *fileName, Concert *c)
{
    FILE *file = fopen(fileName, "a"); // a = append mode
    if (!file)
    {
        perror("Errore nell'apertura del file");
        exit(-1);
    }

    for (int i = 0; i < AVAIBLE_CONCERT; i++)
    {
        fprintf(file, "\n\n%s\n", c[i].name);
        fprintf(file, "%ld\n", c[i].concertDate);
        fprintf(file, "%ld\n", c[i].preSale);
        fprintf(file, "%d\n", c[i].soldOut);
        fprintf(file, "%d\n", c[i].maxTicket);
        fprintf(file, "%d\n", c[i].remaingTicket);
        fprintf(file, "%.2f %d\n", c[i].fullPrice.price, c[i].fullPrice.age);
        fprintf(file, "%.2f %d\n", c[i].underPrice.price, c[i].underPrice.age);
        fprintf(file, "%.2f %d\n", c[i].overPrice.price, c[i].overPrice.age);
        
        fprintf(file, "%s\n", c[i].seller.name);
        fprintf(file, "%s\n", c[i].seller.surname);
        fprintf(file, "%.2f\n", c[i].seller.avaibleMoney);
        fprintf(file, "%s\n", c[i].seller.IBAN);

        for (int j = 0; j < 5; j++)
        {
            fprintf(file, "%s %s %s %d\n",
                    c[i].seller.associatedCards[j].name,
                    c[i].seller.associatedCards[j].surname,
                    c[i].seller.associatedCards[j].CARD_NUMBER,
                    c[i].seller.associatedCards[j].CVC);
        }
    }

    fclose(file);
}

/**
 * @brief carica una lista di strutture Concert da un file
 *  
 * @param fileName nome del file per la lettura dei dati
 * @param list lista dei concerti dove salvare i dati letti
 */
void loadConcertsFromFile(char *fileName, Concert *list)
{ 
    FILE *file = fopen(fileName, "r");
    if (!file)
    {
        perror("Errore nell'apertura del file");
        exit(-1);
    }

    for (int i = 0; i < AVAIBLE_CONCERT; i++)
    {
        Concert c;
        if (fscanf(file, "\n\n%49[^\n]\n", c.name) != 1)
            break; // Legge il nome
        if (fscanf(file, "%ld\n", &c.concertDate) != 1)
            break; // Data concerto
        if (fscanf(file, "%ld\n", &c.preSale) != 1)
            break; // Data prevendita
        if (fscanf(file, "%d\n", (int *)&c.soldOut) != 1)
            break; // Esaurito o no
        if (fscanf(file, "%d\n", &c.maxTicket) != 1)
            break; // Max biglietti
        if (fscanf(file, "%d\n", &c.remaingTicket) != 1)
            break; // Biglietti rimasti
        if (fscanf(file, "%f %d\n", &c.fullPrice.price, &c.fullPrice.age) != 2)
            break; // Biglietti normali
        if (fscanf(file, "%f %d\n", &c.underPrice.price, &c.underPrice.age) != 2)
            break; // Biglietti under
        if (fscanf(file, "%f %d\n", &c.overPrice.price, &c.overPrice.age) != 2)
            break; // Biglietti over
        
        if (fscanf(file, "%49[^\n]\n", c.seller.name) != 1)
            break; // Nome venditore
        if (fscanf(file, "%49[^\n]\n", c.seller.surname) != 1)
            break; // Cognome venditore
        if (fscanf(file, "%f\n", &c.seller.avaibleMoney) != 1)
            break; // Denaro disponibile
        if (fscanf(file, "%33[^\n]\n", c.seller.IBAN) != 1)
            break; // IBAN

        for (int j = 0; j < 5; j++)
        {
            if (fscanf(file, "%49s %49s %15s %d\n",
                       c.seller.associatedCards[j].name,
                       c.seller.associatedCards[j].surname,
                       c.seller.associatedCards[j].CARD_NUMBER,
                       &c.seller.associatedCards[j].CVC) != 4)
            {
                break; // Carte associate
            }
        }

        list[i] = c;
    }

    fclose(file);
}

/**
 * @brief conta quanti concerti sono presenti un file
 * 
 * @param fileName il file dove effetuare il controllo
 * @return int numero di concerti
 */
int countConcertsInFile(char *fileName)
{
    FILE *file = fopen(fileName, "r");
    if (!file)
    {
        perror("Errore nell'apertura del file");
        exit(-1);
    }

    int concertCount = 0;
    char line[256];

    while (fgets(line, sizeof(line), file))
    {
        if (strlen(line) > 1)
        {
            concertCount++;
        }
    }

    fclose(file);
    return concertCount / (9 + 1 + 5); // 9 campi originali + 1 campo seller + 5 carte
}