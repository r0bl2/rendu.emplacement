// emplacement.h
// Projet : Gestion des emplacements - Camping La Cerisaie
// Auteurs : TCHINDOU Essowazou Félicien, COMADAN Ilénin Jacques
// Professeur : MR AKAKPO

#ifndef EMPLACEMENT_H
#define EMPLACEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Taille maximale pour le type d'emplacement
#define MAX_TYPE 20
// Fichier de stockage des emplacements
#define FICHIER_EMPLACEMENT "emplacements.txt"

// Structure représentant un type d'emplacement
typedef struct {
    int id;               // Identifiant unique
    char type[MAX_TYPE];  // Type : Tente, Caravane, Camping-car, Bungalow
    int nb_places;        // Nombre maximum de personnes
    float surface;        // Surface en m²
    float tarif;          // Tarif par jour par personne
} TypeEmplacement;

// Structure représentant un emplacement concret
typedef struct {
    int id;               // Identifiant unique
    TypeEmplacement type; // Type associé
} Emplacement;

// Fonctions utilitaires
void clear_screen();                // Efface l'écran
void pause_ecran();                 // Pause avant de continuer
int lire_entier(char *message);     // Lire un entier positif
float lire_float(char *message);    // Lire un nombre flottant positif
void lire_chaine(char *message, char *buffer, int taille); // Lire une chaîne

// Fonctions de gestion des emplacements
void ajouter_emplacement();         // Ajouter un emplacement
void supprimer_emplacement();       // Supprimer un emplacement
void modifier_emplacement();        // Modifier un emplacement
void consulter_emplacement();       // Consulter un emplacement
void lister_emplacements();         // Lister tous les emplacements

#endif // EMPLACEMENT_H
