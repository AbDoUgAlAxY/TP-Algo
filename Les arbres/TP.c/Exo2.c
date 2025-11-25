#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition de la structure Produit
typedef struct {
    int code;           
    char nom[25];       
    float prix;         
    int quantite;       
} Produit;

// Définition de la structure Noeud de l'arbre binaire
typedef struct Noeud {
    Produit produit;    
    struct Noeud *gauche;  
    struct Noeud *droit;   
} Noeud;

// Définition de la structure Arbre binaire
typedef struct {
    Noeud *racine;      
} A;

// Fonction pour créer un nouveau nœud
Noeud* creerNoeud(Produit produit) {
    Noeud *nouveau = (Noeud*)malloc(sizeof(Noeud));
    if (nouveau == NULL) {
        printf("Erreur d'allocation mémoire !\n");
        return NULL;
    }
    nouveau->produit = produit;
    nouveau->gauche = NULL;
    nouveau->droit = NULL;
    return nouveau;
}

// Fonction pour insérer un produit dans l'arbre binaire (basé sur le code)
Noeud* insererProduit(Noeud *noeud, Produit produit) {
    if (noeud == NULL) {
        return creerNoeud(produit);
    }
    
    if (produit.code < noeud->produit.code) {
        noeud->gauche = insererProduit(noeud->gauche, produit);
    } else if (produit.code >= noeud->produit.code) {
        noeud->droit = insererProduit(noeud->droit, produit);
    }
    
    return noeud;
}

// Procédure pour créer l'arbre binaire à partir des données saisies
void Creer(A *arbre) {
    int n, continuer;
    Produit produit;
    
    if (arbre == NULL) {
        printf("Erreur : l'arbre est NULL.\n");
        return;
    }
    
    arbre->racine = NULL;
    
    printf("=== Création de l'arbre binaire de produits ===\n");
    printf("Entrez le nombre de produits à ajouter : ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        printf("\n--- Produit %d ---\n", i + 1);
        
        printf("Code du produit : ");
        scanf("%d", &produit.code);
        getchar();
        
        printf("Nom du produit (max 24 caractères) : ");
        fgets(produit.nom, sizeof(produit.nom), stdin);

        printf("Prix du produit : ");
        scanf("%f", &produit.prix);
        getchar();
        
        printf("Quantité du produit : ");
        scanf("%d", &produit.quantite);
        getchar();
        
        arbre->racine = insererProduit(arbre->racine, produit);
        printf("Produit ajouté avec succès !\n");
    }
    
    printf("\n=== Arbre créé avec succès ===\n");
}
// Fonction récursive pour calculer le total des quantités en stock
int totalStockNoeud(Noeud *noeud) {
    if (noeud == NULL) {
        return 0;
    }
    int gauche = totalStockNoeud(noeud->gauche);
    int droite = totalStockNoeud(noeud->droit);
    return gauche + droite + noeud->produit.quantite;
}

// Fonction qui retourne le total des quantités de tous les produits de l'arbre
int TotalStock(A *arbre) {
    if (arbre == NULL) {
        printf("Erreur : l'arbre est NULL.\n");
        return 0;
    }
    return totalStockNoeud(arbre->racine);
}
// Fonction récursive pour afficher les produits en rupture de stock
int afficherRuptureNoeud(Noeud *noeud) {
    if (noeud == NULL) {
        return 0;
    }
    int compte = 0;
    compte += afficherRuptureNoeud(noeud->gauche);
    if (noeud->produit.quantite == 0) {
        printf("- %s\n", noeud->produit.nom);
        compte++;
    }
    compte += afficherRuptureNoeud(noeud->droit);
    return compte;
}

// Procédure qui affiche le nom des produits en rupture de stock
void Afficher(A *arbre) {
    if (arbre == NULL) {
        printf("Erreur : l'arbre est NULL.\n");
        return;
    }
    printf("Produits en rupture de stock :\n");
    int total = afficherRuptureNoeud(arbre->racine);
    if (total == 0) {
        printf("Aucun produit en rupture de stock.\n");
    }
}

// Fonction récursive qui cherche un produit par code et retourne le nœud
Noeud* rechercheNoeud(Noeud *noeud, int code) {
    if (noeud == NULL) {
        return NULL;
    }
    if (code == noeud->produit.code) {
        return noeud;
    } else if (code < noeud->produit.code) {
        return rechercheNoeud(noeud->gauche, code);
    } else {
        return rechercheNoeud(noeud->droit, code);
    }
}

// Procédure qui recherche un produit par code et affiche ses informations
void Recherche(A *arbre, int code) {
    if (arbre == NULL) {
        printf("Erreur : l'arbre est NULL.\n");
        return;
    }
    Noeud *res = rechercheNoeud(arbre->racine, code);
    if (res == NULL) {
        printf("Produit de code %d n'existe pas.\n", code);
    } else {
        printf("Produit trouvé :\n");
        printf("Nom      : %s\n", res->produit.nom);
        printf("Prix     : %.2f\n", res->produit.prix);
        printf("Quantité : %d\n", res->produit.quantite);
    }
}

// Helper récursif qui retourne la hauteur d'un nœud si le sous-arbre est équilibré,
// ou -1 si le sous-arbre est déséquilibré.
int hauteurEquilibreNoeud(Noeud *noeud) {
    if (noeud == NULL) {
        return 0; // hauteur d'un arbre vide = 0
    }
    int hg = hauteurEquilibreNoeud(noeud->gauche);
    if (hg == -1) return -1; // sous-arbre gauche déséquilibré
    int hd = hauteurEquilibreNoeud(noeud->droit);
    if (hd == -1) return -1; // sous-arbre droit déséquilibré

    if (hg - hd > 1 || hd - hg > 1) {
        return -1; // écart de hauteur > 1 => déséquilibré
    }
    return 1 + (hg > hd ? hg : hd);
}

// Fonction qui vérifie si l'arbre est équilibré.
// Retourne 1 si équilibré, 0 sinon. Affiche la hauteur si équilibré.
int HauteurEquilibre(A *arbre) {
    if (arbre == NULL) {
        printf("Erreur : l'arbre est NULL.\n");
        return 0;
    }
    int h = hauteurEquilibreNoeud(arbre->racine);
    if (h == -1) {
        printf("L'arbre n'est pas équilibré.\n");
        return 0;
    } else {
        printf("L'arbre est équilibré .\n");
        return 1;
    }
}

// Fonction pour insérer un produit dans l'arbre B selon son prix (ABR par prix)
Noeud* insereABR(Noeud *noeud, Produit produit) {
    if (noeud == NULL) {
        return creerNoeud(produit);
    }
    if (produit.prix < noeud->produit.prix) {
        noeud->gauche = insereABR(noeud->gauche, produit);
    } else {
        noeud->droit = insereABR(noeud->droit, produit);
    }
    return noeud;
}

// Fonction récursive qui parcourt A en inordre et construit B
void parcourirEtInserer(Noeud *noeudA, A *arbreB) {
    if (noeudA == NULL) {
        return;
    }
    parcourirEtInserer(noeudA->gauche, arbreB);
    arbreB->racine = insereABR(arbreB->racine, noeudA->produit);
    parcourirEtInserer(noeudA->droit, arbreB);
}

// Procédure qui crée l'arbre B à partir de l'arbre A en triant par prix
void creerArbreB(A *arbreA, A *arbreB) {
    if (arbreA == NULL || arbreB == NULL) {
        printf("Erreur : l'un des arbres est NULL.\n");
        return;
    }
    arbreB->racine = NULL;
    printf("=== Création de l'arbre B (ordonné par prix croissant) ===\n");
    parcourirEtInserer(arbreA->racine, arbreB);
    printf("Arbre B créé avec succès !\n");
}

// Helper récursif pour afficher les prix en ordre croissant (inordre)
void afficherPrixCroissantNoeud(Noeud *noeud) {
    if (noeud == NULL) {
        return;
    }
    afficherPrixCroissantNoeud(noeud->gauche);
    printf("%.2f ", noeud->produit.prix);
    afficherPrixCroissantNoeud(noeud->droit);
}

// Procédure qui affiche les prix des produits en ordre croissant
void afficherPrixCroissant(A *arbre) {
    if (arbre == NULL) {
        printf("Erreur : l'arbre est NULL.\n");
        return;
    }
    printf("Prix des produits (ordre croissant) : ");
    afficherPrixCroissantNoeud(arbre->racine);
    printf("\n");
}

// Helper récursif pour afficher les prix en ordre décroissant (inordre inversé)
void afficherPrixDecroissantNoeud(Noeud *noeud) {
    if (noeud == NULL) {
        return;
    }
    afficherPrixDecroissantNoeud(noeud->droit);
    printf("%.2f ", noeud->produit.prix);
    afficherPrixDecroissantNoeud(noeud->gauche);
}

// Procédure qui affiche les prix des produits en ordre décroissant
void afficherPrixDecroissant(A *arbre) {
    if (arbre == NULL) {
        printf("Erreur : l'arbre est NULL.\n");
        return;
    }
    printf("Prix des produits (ordre décroissant) : ");
    afficherPrixDecroissantNoeud(arbre->racine);
    printf("\n");
}

// Fonction main avec menu multiChoix
int main() {
    A arbreA, arbreB;
    int choix, code;
    int arbreACreé = 0, arbreBCreé = 0;
    
    while (1) {
        printf("\n========== MENU PRINCIPAL ==========\n");
        printf("1.  Créer l'arbre A (par code, saisie utilisateur)\n");
        printf("2.  Afficher les produits en rupture de stock (arbre A)\n");
        printf("3.  Calculer le total des quantités en stock (arbre A)\n");
        printf("4.  Rechercher un produit par code (arbre A)\n");
        printf("5.  Vérifier l'équilibre de l'arbre A\n");
        printf("6.  Créer l'arbre B (ordonné par prix)\n");
        printf("7.  Afficher les prix en ordre croissant (arbre B)\n");
        printf("8.  Afficher les prix en ordre décroissant (arbre B)\n");
        printf("9.  Quitter\n");
        printf("====================================\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);
        
        switch (choix) {
            case 1:
                printf("\n--- Création de l'arbre A ---\n");
                Creer(&arbreA);
                arbreACreé = 1;
                break;
                
            case 2:
                if (!arbreACreé) {
                    printf("Erreur : L'arbre A n'a pas été créé. Veuillez d'abord créer l'arbre A (option 1).\n");
                } else {
                    printf("\n--- Produits en rupture de stock ---\n");
                    Afficher(&arbreA);
                }
                break;
                
            case 3:
                if (!arbreACreé) {
                    printf("Erreur : L'arbre A n'a pas été créé. Veuillez d'abord créer l'arbre A (option 1).\n");
                } else {
                    int total = TotalStock(&arbreA);
                    printf("Total des quantités en stock : %d\n", total);
                }
                break;
                
            case 4:
                if (!arbreACreé) {
                    printf("Erreur : L'arbre A n'a pas été créé. Veuillez d'abord créer l'arbre A (option 1).\n");
                } else {
                    printf("Entrez le code du produit à rechercher : ");
                    scanf("%d", &code);
                    Recherche(&arbreA, code);
                }
                break;
                
            case 5:
                if (!arbreACreé) {
                    printf("Erreur : L'arbre A n'a pas été créé. Veuillez d'abord créer l'arbre A (option 1).\n");
                } else {
                    printf("\n--- Vérification de l'équilibre ---\n");
                    HauteurEquilibre(&arbreA);
                }
                break;
                
            case 6:
                if (!arbreACreé) {
                    printf("Erreur : L'arbre A n'a pas été créé. Veuillez d'abord créer l'arbre A (option 1).\n");
                } else {
                    printf("\n");
                    creerArbreB(&arbreA, &arbreB);
                    arbreBCreé = 1;
                }
                break;
                
            case 7:
                if (!arbreBCreé) {
                    printf("Erreur : L'arbre B n'a pas été créé. Veuillez d'abord créer l'arbre A (option 1), puis l'arbre B (option 6).\n");
                } else {
                    printf("\n");
                    afficherPrixCroissant(&arbreB);
                }
                break;
                
            case 8:
                if (!arbreBCreé) {
                    printf("Erreur : L'arbre B n'a pas été créé. Veuillez d'abord créer l'arbre A (option 1), puis l'arbre B (option 6).\n");
                } else {
                    printf("\n");
                    afficherPrixDecroissant(&arbreB);
                }
                break;
                
            case 9:
                printf("Au revoir !\n");
                return 0;
                
            default:
                printf("Choix invalide. Veuillez entrer un numéro entre 1 et 9.\n");
        }
    }
    
    return 0;
}


