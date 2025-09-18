//
// Created by ludovic on 07/09/2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

static int rand_range(int min_inclusive, int max_inclusive) {
    return min_inclusive + rand() % (max_inclusive - min_inclusive + 1);
}

static void vider_entree() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main(void)
    {
        int distance_parcourue = 0;
        int soif = 0;
        int fatigue_chameau = 0;
        int gourdes = 3;
        int distance_nomades = -20;
        const int objectif_km = 200;

        bool termine = false;

        srand((unsigned)time(NULL));

        puts("=== Jeu du Chameau ===");
        puts("Traverse 200 km de désert. Gère ta soif et la fatigue du chameau,");
        puts("et ne te fais pas rattraper par les nomades !");

        while (!termine) {
            // Afficher le menu
            puts("\nChoisis une action:");
            puts("A) Boire dans ta gourde");
            puts("B) Avancer à allure modérée");
            puts("C) Foncer à toute allure");
            puts("D) T'arrêter pour la nuit");
            puts("E) État");
            puts("Q) Quitter");
            printf("> ");

            int choix = getchar();
            if (choix == '\n') choix = getchar();
            vider_entree();

            bool tour_effectue = false;
            switch (choix) {
                case 'A':
                case 'a':
                    if (gourdes > 0) {
                        gourdes--;
                        soif = 0;
                        puts("Tu bois une gorgée. Ça va mieux.");
                    } else {
                        puts("Tes gourdes sont vides !");
                    }
                    tour_effectue = true;
                    break;

                case 'B':
                case 'b': {
                    int avance = rand_range(5, 12);
                    distance_parcourue += avance;
                    soif += 1;
                    fatigue_chameau += 1;
                    printf("Tu avances modérément de %d km.\n", avance);
                    tour_effectue = true;
                    break;
                }

                case 'C':
                case 'c': {
                    int avance = rand_range(10, 20);
                    distance_parcourue += avance;
                    soif += 1;
                    fatigue_chameau += rand_range(1, 3);
                    printf("Tu fonces et parcours %d km rapidement !\n", avance);
                    tour_effectue = true;
                    break;
                }

                case 'D':
                case 'd':
                    fatigue_chameau = 0;
                    puts("Vous vous reposez pour la nuit. Le chameau est reposé.");
                    tour_effectue = true;
                    break;

                case 'E':
                case 'e':
                    printf("Distance parcourue: %d km / %d km\n", distance_parcourue, objectif_km);
                    printf("Gourdes restantes: %d\n", gourdes);
                    printf("Soif: %d (>=4 attention, >6 c'est la mort)\n", soif);
                    printf("Fatigue du chameau: %d (>=5 attention, >8 c'est la mort)\n", fatigue_chameau);
                    printf("Les nomades sont à %d km derrière.\n", distance_parcourue - distance_nomades);
                    break;

                case 'Q':
                case 'q':
                    puts("Tu abandonnes. Partie terminée.");
                    termine = true;
                    break;

                default:
                    puts("Choix invalide.");
                    break;
            }

            if (termine) break;

            if (tour_effectue) {

                int avance_nomades = rand_range(7, 14);
                distance_nomades += avance_nomades;

                // Chance d'oasis (5%)
                if (rand_range(1, 20) == 1) {
                    puts("Chance ! Tu trouves une oasis : tu remplis tes gourdes, tu bois et le chameau se repose.");
                    gourdes = 3;
                    soif = 0;
                    fatigue_chameau = 0;
                }

                // Avertissements
                if (soif >= 4 && soif <= 6) {
                    puts("Tu as très soif !");
                }
                if (fatigue_chameau >= 5 && fatigue_chameau <= 8) {
                    puts("Ton chameau est fatigué.");
                }
                if (distance_parcourue - distance_nomades <= 15) {
                    puts("Les nomades se rapprochent !");
                }

                // Conditions de fin
                if (soif > 6) {
                    puts("Tu es mort de soif. Game over.");
                    break;
                }
                if (fatigue_chameau > 8) {
                    puts("Ton chameau s'effondre d'épuisement. Game over.");
                    break;
                }
                if (distance_nomades >= distance_parcourue) {
                    puts("Les nomades t'ont rattrapé ! Game over.");
                    break;
                }
                if (distance_parcourue >= objectif_km) {
                    puts("Félicitations ! Tu as traversé le désert avec succès !");
                    break;
                }
            }
        }

        puts("Merci d'avoir joué !");
        return 0;
    }
