#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256
#define MAX_USERS 100

typedef struct {
    char user[64];
    double total;
} UserAmount;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <src.csv> <report.txt>\n", argv[0]);
        return 1;
    }

    FILE *src = fopen(argv[1], "r");
    if (!src) {
        perror("Errore apertura sorgente");
        return 1;
    }

    FILE *dst = fopen(argv[2], "w");
    if (!dst) {
        perror("Errore apertura destinazione");
        fclose(src);
        return 1;
    }

    UserAmount users[MAX_USERS];
    int userCount = 0;
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), src)) {
        char *user = strtok(line, ",\n");
        char *amountStr = strtok(NULL, ",\n");

        if (!user || !amountStr) continue;

        double amount = atof(amountStr);

        // Cerca se l'utente esiste già
        int found = -1;
        for (int i = 0; i < userCount; i++) {
            if (strcmp(users[i].user, user) == 0) {
                found = i;
                break;
            }
        }

        if (found >= 0) {
            users[found].total += amount;
        } else {
            if (userCount >= MAX_USERS) {
                fprintf(stderr, "Troppi utenti, aumenta MAX_USERS\n");
                fclose(src);
                fclose(dst);
                return 1;
            }
            strcpy(users[userCount].user, user);
            users[userCount].total = amount;
            userCount++;
        }
    }

    // Ordina alfabeticamente
    for (int i = 0; i < userCount - 1; i++) {
        for (int j = i + 1; j < userCount; j++) {
            if (strcmp(users[i].user, users[j].user) > 0) {
                UserAmount temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }

    // Scrivi il report
    for (int i = 0; i < userCount; i++) {
        fprintf(dst, "%s: %.2f\n", users[i].user, users[i].total);
    }

    fclose(src);
    fclose(dst);
    return 0;
