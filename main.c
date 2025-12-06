// main.c
// Menu principal pour gérer les emplacements

#include "emplacement.h" // Fonctions de gestion des emplacements
#include <locale.h>      // Support des accents et locale française
#include <stdio.h>       // Entrée/Sortie standard


int main() {
    // Définir la locale sur français pour permettre l'affichage correct des accents
    setlocale(LC_ALL, "french");

    int choix; // Variable pour stocker le choix de l'utilisateur dans le menu

    do {
        // Effacer l'écran avant d'afficher le menu
        clear_screen();

        // Affichage du menu principal
        printf("\n==================================\n");
        printf("      GESTION DES EMPLACEMENTS  \n");
        printf("==================================\n");
        printf("1 - Ajouter un emplacement\n");
        printf("2 - Modifier un emplacement\n");
        printf("3 - Supprimer un emplacement\n");
        printf("4 - Consulter un emplacement\n");
        printf("5 - Lister tous les emplacements\n");
        printf("0 - Quitter\n");
        printf("Votre choix : ");

        // Lecture du choix de l'utilisateur
        scanf("%d", &choix);
        getchar(); // Consomme le '\n' restant dans le buffer après scanf

        // Traitement du choix via switch
        switch(choix) {
            case 1:
                ajouter_emplacement(); // Ajouter un nouvel emplacement
                break;
            case 2:
                modifier_emplacement(); // Modifier un emplacement existant
                break;
            case 3:
                supprimer_emplacement(); // Supprimer un emplacement
                break;
            case 4:
                consulter_emplacement(); // Consulter les détails d'un emplacement
                break;
            case 5:
                lister_emplacements(); // Lister tous les emplacements
                break;
            case 0:
                printf("\nMerci d'avoir utilisé le programme !\n"); // Message de sortie
                break;
            default:
                printf("\nChoix invalide !\n"); // Message pour un choix incorrect
                pause_ecran(); // Pause pour permettre à l'utilisateur de lire le message
                break;
        }
    } while(choix != 0); // Répète le menu tant que l'utilisateur n'a pas choisi de quitter

    return 0; // Fin normale du programme
}
