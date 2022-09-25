#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define maxdef 10000
#define maxmot 40
#define tailleDict 85829
/**Fonction de fichier : **/

//Fonction qui calcule le nombre de ligne d'un fichier:
int nbLighnes(FILE *f)
{
    int nb = 0;char s[maxmot+maxdef];
    if(f != NULL)
    {
        while (fgets(s,maxmot+maxdef,f) != NULL)    //Si la ligne n'est pas vide on incremante le nombres des lignes.
        {
            nb++;
        }
    }
    return nb;
}


/**FONCTION DE CHAINE DE CARACTERE : **/

//Fonction verifie si le caractere c existe dans la chaine s.

int exist(char c, char *s, int p)
{
    int i;
    for(i = 0 ; i < p ; i++)
    {
        if(s[p] == s[i])
            return 1;
    }
    return 0;
}

//Fonction compte le nombre d'occurences du caractere c dans une chaine s :
int freqChar(char* M, char c)
{
    int i, frq = 0;
    for ( i = 0; i <strlen(M); i++)
    {
        if(M[i]==c)    //Si le i eme element de la chaine est c on incremante le compteur frq.
        {
            frq++;
        }
    }
    return frq;
}

//Fonction qui retourne le nombre de caracteres qui diffèrent entre les mots s1 et s2.
int Distance(char *s1, char *s2)
{
    int i, nbr = 0;
    for(i = 0 ; i < strlen(s1) ; i++)
    {
        if(freqChar(s2,s1[i]) == 0 && exist(s1[i],s1,i) == 0)  //Si la frequence de chaque caractere de s1 dans s2 est 0 et ce caractere exist une seul fois dans s1.
        {
            nbr++;                                             //alors on incremante le compteur nbr.
        }
    }
    for(i = 0 ; i < strlen(s2) ; i++)
    {
        if(freqChar(s1,s2[i]) == 0 && exist(s2[i],s2,i) == 0)             //Si la frequence de chaque caractere de s2 dans s1 est 0 et ce caractere exist une seul fois dans s2.
        {
            nbr++;                                                         //alors on incremante le compteur nbr.
        }
    }

    return nbr;
}

/**FONCTION DE DICTIONNAIRE***/
//FONCTION DE HACHAGE :
int hachage(char *M, int htablesize)
{
    int l = strlen(M), s = 0, i;
    for(i = 0 ; i < l ; i++)
    {
        s = s + pow(i+1,4)*M[i] ;  //premiere fonction de hachage(code de hachage) =  On fait la somme de produit de :   la position de chaque caractere dans dans le mot puissance 4 et le code ASCII de chaque lettre du mot

    }
    return ((s % htablesize) + l) % htablesize ;     //deuxieme fonction (fonction de compression = on prend le rest de la  devisionde  la premiere fonction sur la taille de la table de hachage et on lui ajoute la taille de mot, on prend le rest de devision de ce dernier sur la taille de la table de hachage
    /** On ajoute la longueure du mot pour eviter les collisions entre les mots qui ont le meme premier resultat avec ceux qui ont une longueur deffirente**/
    /**Nombre total de collisions = 9**/
}

//STRUCTURE D'UN MOT :
typedef struct Mot Mot;  //La structure d'un mot contient trois case :
struct Mot
{
    char *mot;           // la premiere case contient le mot.
    char *def;           // la deuxieme case contient sa definition.
    Mot *svt;            //la troisieme case contient un pointeur sur une structure (un autre element) d'un autre mot.
};

//STRUCTURE D'UN DICTIONNAIRE :
typedef struct Dictionnaire Dictionnaire;   //La structure d'un dictionnaire contient un poiteur sur un mot.
struct Dictionnaire
{
    Mot *motD;      //La structure d'un dictionnaire contient un poiteur sur un mot.
};

//CREATION D'UN MOT :
Mot *creerMot()
{
    Mot *m = malloc(sizeof(*m));   //On alloue une espace dans la memoire d'une taille d'un mot.
    if ( m == NULL )
        exit(EXIT_FAILURE);
    m->mot = NULL;                              //On initialise toutes les case de la structure mot par NULL.
    m->def = NULL;
    m->svt = NULL;
    return m;
}

//Fonction de remplissage d'une structure d'un mot
Mot *remplirMot(char *word, char *de)
{

    Mot *m = creerMot();    //On creer une structure vide  d'un mot
    m->mot = malloc(maxmot*sizeof(char));   //On alloue l'espace nécessaire pour le  mot.
    m->def = malloc(maxdef*sizeof(char));   //On alloue l'espace nécessaire pour sa definition.
    strcpy(m->mot,word);                    //On copie le mot donné dans la case du mot dans la structure.
    m->mot[strlen(word)] = '\0';
    strcpy(m->def,de);                      //On copie la definition donnée dans la case du definition dans la structure.
    m->def[strlen(de)] = '\0';
    return m;
}

//CREATION D'UN DICTIONNAIRE :
Dictionnaire* creerDic(int tailleDic)
{
    Dictionnaire *d = malloc(tailleDic*sizeof(*d));  //On alloue  une espace pour un table de dictionnaire d'une taille =tailleDic.
    int i;
    for(i = 0 ; i < tailleDic ; i++)
    {
        d[i].motD = NULL;           //On initiaise toutes les cases par NULL.
    }
    return d;
}

//FONCTION D'AJOUT D'UN MOT A UNE POSITION i DANS LE DICTIONNAIRE :
void addMot(Dictionnaire *d, int i, char *mot, char *def)
{
    if(d[i].motD == NULL)
        {
            d[i].motD = remplirMot(mot,def);        //Ajout en tete.
        }
        else
        {
            Mot *m = d[i].motD;              //Ajout en  fin.
            while(m->svt != NULL && stricmp(m->mot,mot) != 0)   //Tant que on n'arrive pas au fin de la liste & le mot dans l'element et le mot donné ne sont pas les mêmes alors:
            {
                m = m->svt;            //On depace au prochain element dans la liste.
            }
            if(m->svt == NULL)    //Si le mot dans l'element et le mot donné ne sont pas les mêmes alors: On affiche le message:
            {
                m->svt = remplirMot(mot,def);  //On ajoute le mot au dictionnaire

            }
            else //Sinon :
            {
                printf("Attention! Le mot existe deja dans le dictionnaire.\n");//Si le mot dans l'element et le mot donné ne sont pas les mêmes alors: On affiche le message:
            }

        }
}


//FONCTION DE REMPLISSAGE D'UN TABLEAU A PARTIR UN FICHIER F :
Dictionnaire* remplirDico()
{
    FILE *f = fopen("dictionnaire.txt","r");   //On ouvrire le fichier qui contient le dictionnaire en mode lecture
    int i;
    rewind(f);
    Dictionnaire *d = creerDic(tailleDict);     //On crée un dictionnaire vide (allouer l'espace necessaire
    char mot[maxmot]="", def[maxdef] = "" , ligne[maxdef+maxmot], c;
    while(fgets(ligne,maxdef+maxmot,f) != NULL)
    {

        c = fgetc(f);   //On lire le fichier caractere par caractere
        while(c != ':' ) //Tant que le caractere n'est pas un ":"
        {
            sprintf(mot,"%s%c",mot,c);   //On concatine le caractere avec mot
            c = fgetc(f);    //On lit le caractere suivant

        }
        c = fgetc(f);
        while(c != '.' )  //Tant que que ce n'est pas la fin de la ligne
        {
            sprintf(def,"%s%c",def,c);    //On concatine le caractere avec la definition
            c = fgetc(f);   //On lit le caractere suivant

        }
        i = hachage(mot,tailleDict);  //On calcule le code de hachage de mot
        addMot(d,i,mot,def);    //On met le mot dans le dictionnaire
        strcpy(def,"");             //On vide la chaine def
        strcpy(mot,"");              //On vide la chaine mot

    }

    fclose(f);

    return d; //On retourne le dictionnaire
}


//FONCTION DE RECHERCHE D'UN MOT DANS LE DICTIONNAIRE :
int rechercheMoT(Dictionnaire *T,int tailleD, char* M)
{
    int hach = hachage(M,tailleD);    //On recupére la clé du mot dans hach.
    if(T[hach].motD == NULL)     //Si la case pointe sur le NULL alors.
        return 0;                //le mot n'existe pas.
    else
    {
        Mot *m = T[hach].motD;
        while(m != NULL)     //On parcourt la liste de la case hach.
      {
        if(stricmp(m->mot,M) == 0)    //Si le contenue du mot  d'un element de la liste et le mot donné sont les mêmes.
            return 1;                  //On retourne vrai "1".
        else
            m = m->svt;            //Sinon on fait un deplacement au prohain element.
      }                            //et on refait la boucle .
    return 0;                //Si aucun element est le meme mot donné alors le mot n'existe pas dans la table et on returne faux "0".
    }

}
/**La compléxité est O(n)**/

//FONCTION RETURNE L'ENSEMBLE DE MOTS DISTANCE D'UN MOT D'AU PLUS K CARACTERES :
char **ensembleDistant(Dictionnaire *d,int tailleD, char *m, int k)
{
    int i = 0 , j = -1, l = 0;   //On initialise la taille du tableau par 0
    char **ensemble = malloc(l*sizeof(char*));    //On alloue une espace pour un tableau de mots qui peut contenir un seul mot au debut.
    Mot *M;
    while( i < tailleD)   //Tant que i est strictement inferieur a la taille de la table on refait la boucle.
    {
        if(d[i].motD != NULL)     //Si la lisle dans chaque case  n'est pas vide alors
        {
            M = d[i].motD;
            while(M != NULL)      //On parcourt cette liste.
            {
                if(Distance(m,M->mot) <= k)   //Si le nombre de caracteres qui diffèrent entre le mot donné et le mot de ce element est inferieur ou egal a k  alors:
                {
                    l++;j++;                             //On incremante la taille de tableau et la position courante.
                    realloc(ensemble,l*sizeof(char*));    //On ajoute une case au tableau.
                    ensemble[j] = malloc(strlen(M->mot)*sizeof(char));   //On alloue l'espace necessaire pour le mot qui on veut l'ajouter
                    strcpy(ensemble[j],M->mot);           //On copie le mot au tabeau a partir l'element..
                    printf("  %s\n",ensemble[j]);
                }
                M = M->svt;    //On deplace au prochain element.
            }//On refait la boucle.
        }
        i++;
    }

    if(j == -1)  //Si la taille de tableau reste la  meme alors AUCUN MOT DE CE DICTIONNAIRE DISTANT Du MOT DONNE D'AU PLUS k CARACTERE.
    {
        printf("AUCUN MOT DE CE DICTIONNAIRE DISTANT DE %s D'AU PLUS %d CARACTERE.\n",m,k);
        free(ensemble);  //On liberer l'espace allouée au debut
    }
    return ensemble;
}



//FONCTION D'AJOUT UN MOT DANS LI DICTIONNAIRE :
void ajoutMot(Dictionnaire *d, char *mot, char *def)
{
    int hach = hachage(mot,tailleDict);  //One met la clé de mot dans hach
    addMot(d,hach,mot,def);   //On ajout le mot dans le dictionnaire
    printf("Le mot a ete ajoute au dictionnaire, merci!\n\n");
}

//Suppression d'un mot du dictionnaire:
void suppMot(Dictionnaire *d, char *mot)
{
    int hach = hachage(mot,tailleDict);
    if(d[hach].motD == NULL)              //Si la case de la table est vide alors le mot n'exite pas
        printf("Le mot n'existe pas dans le dictionnaire.\n ");
    else
    {
        Mot *m, *suiv, *prc;
        m = d[hach].motD;
        if(stricmp(m->mot,mot) == 0)   //suppression du tête.
        {
            suiv = m->svt;
            d[hach].motD = suiv;
            free(m);
        }
        else                     //Suppression d'autres éléments.
        {
            prc = m;
            m = m->svt;
            while(m != NULL && stricmp(m->mot,mot) != 0)
            {
                prc = m;
                m = m->svt;
            }
            if(m == NULL)    //Si on arrive à la fin de liste donc le mot n'existe pas dans le dictionnare.
                printf("Le mot n'existe pas dans le dictionnaire.\n ");
            else
            {
                suiv = m->svt;
                prc->svt = suiv;
                free(m);
            }
        }

    }
}

Dictionnaire *creerIndex(FILE *f)   //fopen fclose dans le main
{
    Dictionnaire *I = creerDic(tailleDict);
    char ligne[maxdef], mot[50]; int i, k, j;
    while(fgets(ligne,maxdef,f) != NULL)
    {
       i = 0;
       while(i < strlen(ligne))
       {
           while(ligne[i] == ' ' && i < strlen(ligne))
           {
               i++;
           }
           if(i < strlen(ligne))
           {
               j = 0;
               while(ligne[i] != ' ')
               {
                   while(ligne[i] == '.' || ligne[i] == ',' || ligne[i] == ';' || ligne[i] == '!' || ligne[i] == '?' || ligne[i] == '"' || ligne[i] == '(' || ligne[i] == ')' || ligne[i] == ':' )
                   {
                       i++;
                   }

                    mot[j] = ligne[i];
                    j++; i++;
               }
               mot[j] = '\0';
               printf("%s ",mot);
               ajoutMot(I,mot,"nodef");
           }
       }
    }
    return I;
}
typedef struct positionMotIndex positionMotIndex;
struct positionMotIndex
{
    int posTableHach;
    int tailleTab;
    int *tab;
};
positionMotIndex *retournPosMotIndex(Dictionnaire *I, char *mot)
{
    positionMotIndex *p = malloc(sizeof(*p));
    int pos = hachage(mot,tailleDict),i;
    if(I[pos].motD == NULL)
    {
        printf("Le mot n'existe pas dans l'index.\n");
    }
    else
    {
        Mot *m = I[pos].motD;
        int posLst = 1;i=0;
        p->tab = malloc(sizeof(int));
        while(m != NULL)
        {
            if(stricmp(m->mot,mot)==0)
            {
                realloc(p->tab,(i+1)*sizeof(int));
                p->tab[i] =  posLst;
                i++;

            }
            posLst++;
            m = m->svt;
        }
        p->tailleTab = i;
    }
    if(i==0)
    {
        printf("Le mot n'existe pas dans l'index.\n");
    }
    p->posTableHach = pos;
    return p;
}


//FONCTION D'AFFICHAGE
void affichage()
{
    printf("**    **    ********   ********   **    **   *******                                    PROJET TP 1 D'ALGO\n");
    printf("**    **    ********   ********   **    **   **    **\n");
    printf("**    **    **            **      **    **   **    **                                   REALISE PAR ANOUAR AISSANI\n");
    printf("**    **    ********      **      ********   ******                                     \n");
    printf("**    **    ********      **      ********   ******                                     ISIL L2 / SECTION B / GROUPE 04 \n");
    printf("**    **          **      **      **    **   **    **                                    \n");
    printf("********    ********      **      **    **   **    **                                   L'annee : 2019/2020\n");
    printf("********    ********      **      **    **   ******* \n");
    printf("******************************************************************************* BIENVENUE **********************************************************************************\n");
    printf("                                            _~~_~~__~~__~~__~~__~~__~~__~~__~~_ /(^_^)/ _~~__~~__~~__~~__~~__~~__~~__~~__~~_ \n\n\n");
    char m[maxmot],def[maxdef], **ensemble;
    int choix,stop=0,i,k,nbr;
    FILE *f;
    Dictionnaire *I;
     Dictionnaire *T;

    while(!stop)
    {
        printf("                                                                 *   *   ****  *    *   *  *\n");
        printf("                                                                 ** **   *     **   *   *  *\n");
        printf("                                                                 * * *   ****  * *  *   *  *\n");
        printf("                                                                 * * *   *     *  * *   *  *\n");
        printf("                                                                 *   *   ****  *   **   ****\n\n");

               /*MENU*/
        printf("                                                            >>VOICI LES FONCTIONALITEES DISPONIBLE:<<\n\n\n");
        printf("                                                     =====>> 1.CREER UN DICTONNAIRE .\n\n");
        printf("                                                     =====>> 2.CHERCHER UN MOT DANS LE DICTIONNAIRE.\n\n");
        printf("                                                     =====>> 3.RETOURNER L'ENSEMBLE DE MOTS DISTANTS D'UN MOT DONNER.\n\n");
        printf("                                                     =====>> 4.AJOUTER UN MOT AU DICTIONNAIRE.\n\n");
        printf("                                                     =====>> 5.SUPPRIMER UN MOT.\n\n");
        printf("                                                     =====>> 6.CREER UN INDEX.\n\n");
        printf("                                                     =====>> 7.RETOUENER TOUS LES POSITIONS D'UN MOT M DANS L'INDEX.\n\n");
        printf("                                                     =====>> 0.QUITTER.\n\n");

        printf("                                                                   Votre choix s'il vous plait ?\n\n ");
        scanf("%d",&choix);
        switch (choix)  /*les choix*/
           {
               case 0 : stop = 1;
               break;

               case 1:

                      T = remplirDico();
                      printf("Votre dictionnaire a ete cree! ^_^\n");

               break;

               case 2:

                      printf("Veuillez entrer le mot que vous voullez chercher s'il vous plait :\n");
                      scanf("%s",m);
                      printf("%d\n",rechercheMoT(T,tailleDict,m));
                      if(rechercheMoT(T,tailleDict,m) == 0)
                      {
                          printf("Desole, le mot n'existe pas dans le dictionnaire!\n");
                      }
                      else
                      {
                          printf("Le mot existe dans le dictionnaire, sa position est : %d.\n",hachage(m,tailleDict));
                      }

               system("pause");
               break;

               case 3:

                      printf("Veuillez entrer un mot s'il vous plait :\n");
                      scanf("%s",m);
                      printf("Veuillez entrer un seuil s'il vous plait :\n");
                      scanf("%d",&k);
                      ensemble = ensembleDistant(T,tailleDict,m,k);

               system("pause");
               break;

               case 4 :
                       printf("Veuillez entrer le mot que vous voullez ajouter au dictionnaire et sa definition s'il vous plait :\n");
                       scanf("%s %s",m,def);
                       ajoutMot(T,m,def);
               system("pause");
			   break;
               case 5 :
                       printf("Veuillez entrer le mot que vous voullez supprimer du dictionnaire s'il vous plait :\n");
                       scanf("%s",m);
                       suppMot(T,m);
               system("pause");
			   break;
			   case 6 :
			           f = fopen("novel.txt","r");
                       I =creerIndex(f);
                       fclose(f);
                       printf("Votre index a ete cee! ^_^\n");
               system("pause");
			   break;
               case 7 :
                   printf("Veuillez entrer le mot que vous voullez retourner ses positions dans l'index s'il vous plait :\n");
                   scanf("%s",m);
                   positionMotIndex *p = retournPosMotIndex(I,m);
               system("pause");
			   break;

			   default:
                printf("Ressayer une autre fois\n\n");  system("pause");
                break;
           }
           printf("\n\n\n");
       }
    }

    main()
{
    affichage();
}
