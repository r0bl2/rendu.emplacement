// emplacement.c
// Implémentation des fonctions de gestion des emplacements

#include "emplacement.h"

// ===== Fonctions utilitaires =====

// Efface l'écran (fonction multiplateforme)
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pause pour permettre à l'utilisateur de lire les messages
void pause_ecran() {
    printf("\nAppuyez sur Entrée pour continuer...");
    getchar();
}

// Lit un entier positif avec message
int lire_entier(char *message) {
    int val;
    while (1) {
        printf("%s : ", message);
        if (scanf("%d", &val) != 1 || val <= 0) {
            printf("Erreur : entrez un entier positif.\n");
            while (getchar() != '\n'); // Vide le buffer
        } else {
            getchar(); // Consomme le '\n' restant
            return val;
        }
    }
}

// Lit un nombre flottant positif avec message
float lire_float(char *message) {
    float val;
    while (1) {
        printf("%s : ", message);
        if (scanf("%f", &val) != 1 || val <= 0) {
            printf("Erreur : entrez un nombre positif.\n");
            while (getchar() != '\n'); // Vide le buffer
        } else {
            getchar();
            return val;
        }
    }
}

// Lit une chaîne de caractères avec taille limitée
void lire_chaine(char *message, char *buffer, int taille) {
    printf("%s : ", message);
    fgets(buffer, taille, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Supprime le retour à la ligne
}

// ===== Fonctions de gestion =====

// Ajouter un nouvel emplacement
void ajouter_emplacement() {
    clear_screen();
    printf("\n==================================\n");
    printf("      AJOUT D'EMPLACEMENTS  \n");
    printf("==================================\n");

    Emplacement e;
    e.id = lire_entier("Entrez l'ID de l'emplacement (ex: 1, 2, 3)");
    printf("\nExemple de type : Tente, Caravane, Camping-car, Bungalow\n");
    lire_chaine("Entrez le type", e.type.type, MAX_TYPE);
    e.type.nb_places = lire_entier("Nombre maximum de personnes");
    e.type.surface = lire_float("Surface en m²");
    e.type.tarif = lire_float("Tarif par jour par personne (euros)");

    FILE *f = fopen(FICHIER_EMPLACEMENT, "a");
    if (f) {
        fprintf(f, "%d;%s;%d;%.2f;%.2f\n", e.id, e.type.type, e.type.nb_places, e.type.surface, e.type.tarif);
        fclose(f);
        printf("\nEmplacement ajouté avec succès !\n");
    } else {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
    }
    pause_ecran();
}

// Lister tous les emplacements enregistrés
void lister_emplacements() {
    clear_screen();
    printf("\n==================================\n");
    printf("      Liste DES EMPLACEMENTS  \n");
    printf("==================================\n");

    FILE *f = fopen(FICHIER_EMPLACEMENT, "r");
    if (!f) {
        printf("Aucun emplacement enregistré.\n");
        pause_ecran();
        return;
    }

    Emplacement e;
    printf("ID | Type       | Places | Surface | Tarif\n");
    printf("----------------------------------------------\n");
    while (fscanf(f, "%d;%[^;];%d;%f;%f\n", &e.id, e.type.type, &e.type.nb_places, &e.type.surface, &e.type.tarif) == 5) {
        printf("%2d | %-10s | %5d | %7.2f | %5.2f\n", e.id, e.type.type, e.type.nb_places, e.type.surface, e.type.tarif);
    }
    fclose(f);
    pause_ecran();
}

// Consulter un emplacement par ID
void consulter_emplacement() {
    clear_screen();
    printf("\n==================================\n");
    printf("      CONSULTER UN EMPLACEMENTS  \n");
    printf("==================================\n");

    int id = lire_entier("Entrez l'ID de l'emplacement à consulter");
    FILE *f = fopen(FICHIER_EMPLACEMENT, "r");
    if (!f) {
        printf("Aucun emplacement enregistré.\n");
        pause_ecran();
        return;
    }

    Emplacement e;
    int trouve = 0;
    while (fscanf(f, "%d;%[^;];%d;%f;%f\n", &e.id, e.type.type, &e.type.nb_places, &e.type.surface, &e.type.tarif) == 5) {
        if (e.id == id) {
            printf("\nID : %d\nType : %s\nPlaces : %d\nSurface : %.2f m²\nTarif : %.2f euros\n",
                   e.id, e.type.type, e.type.nb_places, e.type.surface, e.type.tarif);
            trouve = 1;
            break;
        }
    }
    if (!trouve) printf("Emplacement introuvable.\n");
    fclose(f);
    pause_ecran();
}

// Supprimer un emplacement par ID
void supprimer_emplacement() {
    clear_screen();
    printf("\n==================================\n");
    printf("     SUPPRIMER UN EMPLACEMENTS  \n");
    printf("==================================\n");

    int id = lire_entier("Entrez l'ID de l'emplacement à supprimer");
    FILE *f = fopen(FICHIER_EMPLACEMENT, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!f || !temp) {
        printf("Erreur fichier.\n");
        pause_ecran();
        return;
    }

    Emplacement e;
    int trouve = 0;
    while (fscanf(f, "%d;%[^;];%d;%f;%f\n", &e.id, e.type.type, &e.type.nb_places, &e.type.surface, &e.type.tarif) == 5) {
        if (e.id != id)
            fprintf(temp, "%d;%s;%d;%f;%f\n", e.id, e.type.type, e.type.nb_places, e.type.surface, e.type.tarif);
        else
            trouve = 1;
    }
    fclose(f);
    fclose(temp);

    remove(FICHIER_EMPLACEMENT);
    rename("temp.txt", FICHIER_EMPLACEMENT);

    if (trouve) printf("\nEmplacement supprimé avec succès !\n");
    else printf("\nEmplacement introuvable.\n");
    pause_ecran();
}

// Modifier un emplacement existant
void modifier_emplacement() {
    clear_screen();
    printf("\n==================================\n");
    printf("      MODIFIER EMPLACEMENTS  \n");
    printf("==================================\n");

    int id = lire_entier("Entrez l'ID de l'emplacement à modifier");
    FILE *f = fopen(FICHIER_EMPLACEMENT, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!f || !temp) {
        printf("Erreur fichier.\n");
        pause_ecran();
        return;
    }

    Emplacement e;
    int trouve = 0;
    while (fscanf(f, "%d;%[^;];%d;%f;%f\n", &e.id, e.type.type, &e.type.nb_places, &e.type.surface, &e.type.tarif) == 5) {
        if (e.id == id) {
            printf("\nExemple de type : Tente, Caravane, Camping-car, Bungalow\n");
            lire_chaine("Entrez le nouveau type", e.type.type, MAX_TYPE);
            e.type.nb_places = lire_entier("Nombre maximum de personnes");
            e.type.surface = lire_float("Surface en m²");
            e.type.tarif = lire_float("Tarif par jour par personne (euros)");
            trouve = 1;
        }
        fprintf(temp, "%d;%s;%d;%f;%f\n", e.id, e.type.type, e.type.nb_places, e.type.surface, e.type.tarif);
    }

    fclose(f);
    fclose(temp);

    remove(FICHIER_EMPLACEMENT);
    rename("temp.txt", FICHIER_EMPLACEMENT);

    if (trouve) printf("\nEmplacement modifié avec succès !\n");
    else printf("\nEmplacement introuvable.\n");
    pause_ecran();
}
