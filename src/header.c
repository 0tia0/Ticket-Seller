#include "header.h"

int AVAIBLE_CONCERT = 0;
Concert concertList[MAX_CONCERT_AVAIBLE]; 

int userAmount = 0;
User userList[20];

const char *concertFile = "./data/concerts.bin";
const char *userFile = "./data/users.bin";

void saveData(const char *concertFile, const char *userFile) {
    FILE *file = fopen(concertFile, "wb");
    if (file == NULL) {
        perror("Errore durante l'apertura del file concertFile");
        return;
    }
    fwrite(&AVAIBLE_CONCERT, sizeof(int), 1, file);
    fwrite(concertList, sizeof(Concert), AVAIBLE_CONCERT, file);
    fclose(file);

    file = fopen(userFile, "wb");
    if (file == NULL) {
        perror("Errore durante l'apertura del file userFile");
        return;
    }
    fwrite(&userAmount, sizeof(int), 1, file);
    fwrite(userList, sizeof(User), userAmount, file);
    fclose(file);
}

void loadData(const char *concertFile, const char *userFile) {
    FILE *file = fopen(concertFile, "rb");
    if (file == NULL) {
        perror("Errore durante l'apertura del file concertFile");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (fileSize == 0) {
        printf("Il file concertFile è vuoto.\n");
        fclose(file);
        return;
    }

    fread(&AVAIBLE_CONCERT, sizeof(int), 1, file);
    fread(concertList, sizeof(Concert), AVAIBLE_CONCERT, file);
    fclose(file);

    file = fopen(userFile, "rb");
    if (file == NULL) {
        perror("Errore durante l'apertura del file userFile");
        return;
    }

    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (fileSize == 0) {
        printf("Il file userFile è vuoto.\n");
        fclose(file);
        return;
    }

    fread(&userAmount, sizeof(int), 1, file);
    fread(userList, sizeof(User), userAmount, file);
    fclose(file);
}

void removeNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}