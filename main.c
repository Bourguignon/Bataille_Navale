#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE 10
#define TAILLEBAT 3
#define TAILLEFLOTTE 5

typedef struct cellule{
    int x;
    int y;
}cellule;

typedef struct bateau{
    cellule pos[TAILLEBAT];
}bateau;

typedef struct flotte{
    bateau nav[TAILLEFLOTTE];
}flotte;

enum BOOL{
    Vrai,Faux
};

//prototype
void initcellule(cellule *cel);
void Feu(cellule *tir);
void createcellule(cellule *cel);
void createbateau(bateau *navire);
void modifflotte(flotte *flot,cellule *cel);
void modifbateau(bateau *navire,cellule *cel);
void modifcellule(cellule *cel1,cellule *cel2);
void initJoueur(flotte *flot);
void createflotte(flotte *flot);

int verifsortie(cellule *cel);
int verifcase(cellule *cel1,cellule *cel2);
int verifbateau(bateau *navire,cellule *cel);
int verifflotte(flotte *flot,cellule *cel);


int main(){

flotte J1,J2;
cellule tir;
cellule victoire;

victoire.x=-1;
victoire.y=-1;

    do{
        printf("J1\n");
        initJoueur(&J1);
        createflotte(&J1);

        printf("J2\n");
        initJoueur(&J2);
        createflotte(&J2);

        printf("J1\n");
        Feu(&tir);
        if(verifflotte(&J2,&tir)==Vrai){
            modifflotte(&J2,&tir);
        }

        printf("J2\n");
        Feu(&tir);
        if(verifflotte(&J1,&tir)==Vrai){
            modifflotte(&J1,&tir);
        }

    }while((verifflotte(&J1,&victoire)==Faux)||(verifflotte(&J2,&victoire)==Faux));

    if(verifflotte(&J1,&victoire)==Faux){
        printf("J2 gagner !!!!!\n");
    }else{
        printf("J1 gagner !!!!!\n");
    }

    return 0;
}

void initcellule(cellule *cel){

    cel->x=0;
    cel->y=0;
}

//BUT:Demande a l'utilisateur ou il veut tirer
//ENTREE:Une variable cellule
//SORTIE:Les coordonne du tir
void Feu(cellule *tir){

    do{
        printf("Ou voulez vous tirer, coordonner X(Entre 0 et %d)\n",TAILLE);
        scanf("%p",&tir->x);
        printf("Ou voulez vous tirer, coordonner Y(Entre 0 et %d)\n",TAILLE);
        scanf("%p",&tir->y);
        verifsortie(tir);
    }while((tir->x>TAILLE)&&(tir->x<0)&&(tir->y>TAILLE)&&(tir->y<0));
}

void modifflotte(flotte *flot,cellule *cel){

int i;

    for(i=0;i<TAILLEFLOTTE;i++){
        modifbateau(&flot->nav[i],cel);
    }
}

void modifbateau(bateau *navire,cellule *cel){

int i;

    for(i=0;i<TAILLEFLOTTE;i++){
        modifcellule(&navire->pos[i],cel);
    }
}

void modifcellule(cellule *cel1,cellule *cel2){

    if((cel1->x==cel2->x)&&(cel1->y==cel2->y)){
        cel1->x=(-1);
        cel1->y=(-1);
    }
}

//BUT:Demande a l'utilisateur ou il veut placer son bateaux
//ENTREE:Cellule du bateau vide, entree utilisateur
//SORTIE:1 Cellule du bateau remplit
void createcellule(cellule *cel){

    do{
        printf("Ou voulez vous placer le bateaux, coordonner X(Entre 0 et %d)\n",TAILLE);
        scanf("%p",&cel->x);
        printf("Ou voulez vous placer le bateaux, coordonner Y(Entre 0 et %d)\n",TAILLE);
        scanf("%p",&cel->y);
        verifsortie(cel);
    }while((cel->x>TAILLE)&&(cel->x<0)&&(cel->y>TAILLE)&&(cel->y<0));
}

//BUT:Crée un bateau
//ENTREE:Une variable bateau
//SORTIE:1 variable bateau remplit corectemment
void createbateau(bateau *navire){

int i=0;

    for(i=1;i<TAILLEBAT;i++){
        srand(time(NULL));
        if(rand()%2==0){
            navire->pos[i].x=navire->pos[0].x+1;
            if(verifsortie(&navire->pos[i])==Vrai){
                navire->pos[i].x=navire->pos[0].x-1;
            }
        }else{
            navire->pos[i].y=navire->pos[0].y+1;
            if(verifsortie(&navire->pos[i])==Vrai){
                navire->pos[i].y=navire->pos[0].y-1;
            }
        }
    }
}

//BUT:Verifie si la cellule est dans le terrain
//ENTREE:Une variable cellule
//SORTIE:Affiche si la coordonne est valide
int verifsortie(cellule *cel){
    if((cel->x<TAILLE)&&(cel->x>=0)&&(cel->y<TAILLE)&&(cel->y>=0)){
        printf("Coordonné valider\n");
        return Vrai;
    }else{
        printf("Coordonné non valide\n");
        return Faux;
    }
}

//BUT:Verifie si deux cellule sont au méme endroit
//ENTREE:Les deux cellule a comparer
//SORTIE:Vrai si les cellule ont les mêmes coordonnee
int verifcase(cellule *cel1,cellule *cel2){

    if((cel1->x==cel2->x)&&(cel1->y==cel2->y)){
        return Vrai;
    }else{
        return Faux;
    }
}

//BUT:Verifie si une cellule appartien a un bateau
//ENTREE:1 variable Cellule et une variable bateau
//SORTIE:Vrai si une Cellule appartien au bateau
int verifbateau(bateau *navire,cellule *cel){

int i=0;

    for(i=0;i<TAILLEBAT;i++){
        if(verifcase(&navire->pos[i],cel)==Vrai){
            return Vrai;
        }
    }
    return Faux;
}


//BUT:Verifie si une cellule appartien a une flotte
//ENTREE:1 variable Cellule et une variable flotte
//SORTIE:Vrai si une Cellule appartien a une flotte
int verifflotte(flotte *flot,cellule *cel){

int i=0;

    for(i=0;i<TAILLEFLOTTE;i++){
        if(verifbateau(&flot->nav[i],cel)==Vrai){
            return Vrai;
        }
    }
    return Faux;
}

void initJoueur(flotte *flot){

int i,j;
int test=0;

    for(i=0;i<TAILLEFLOTTE;i++){
        initcellule(&flot->nav[i].pos[0]);
        createcellule(&flot->nav[i].pos[0]);
        for(j=0;j<TAILLEBAT;j++){
            if(verifflotte(&flot,&flot->nav[i].pos[j])==Vrai){
                test+=1;
            }
        }
    }
}

void createflotte(flotte *flot){

int i,j;
int test=0;

    for(i=0;i<TAILLEFLOTTE;i++){
        createbateau(&flot->nav[i]);
        for(j=0;j<TAILLEBAT;j++){
            if(verifflotte(&flot,&flot->nav[i].pos[j])==Vrai){
                test+=1;
            }
            if(test!=0){
                printf("Bateaux superposer\n");
            }
        }
    }
}
