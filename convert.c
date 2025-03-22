#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("📄 Conversion de page.html en output.pdf...\n");
    
    // Commande pour convertir le fichier HTML en PDF
    int status = system("wkhtmltopdf page.html output.pdf");
    
    if (status == 0) {
        printf("Conversion réussie !\n");
    } else {
        fprintf(stderr, "ATTENTION PLUSIEUR ERREUR DE CONVERSION DU FICHIER PDF\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
