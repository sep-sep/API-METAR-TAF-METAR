#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Syntaxe : %s <ORIG>\n", argv[0]);
        return EXIT_FAILURE;
    }

    printf("🔄 Exécution de NOTAM pour récupérer les données...\n");
    char command[256];
    snprintf(command, sizeof(command), "./notam %s > page.html", argv[1]);
    int status = system(command);
    if (status != 0) {
        printf(" Erreur lors de l'exécution de NOTAM\n");
        return EXIT_FAILURE;
    }

    printf("Fichier HTML généré avec succès\n");
    
    printf("Conversion de page.html en PDF...\n");
    status = system("./CONVERT page.html output.pdf");
    if (status != 0) {
        printf("Erreur lors de la conversion en PDF\n");
        return EXIT_FAILURE;
    }

    printf("Conversion terminée : output.pdf est prêt !\n");
    return EXIT_SUCCESS;
}
