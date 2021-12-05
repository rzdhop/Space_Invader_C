#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "struct_def.h"
#include "key_pressed.h"
#include "colors.h"

//partie de code affchant l'ecran de defaite 
void looseScreen(Env *args)
{
    system("clear");
    char key;
    int posYBase = args->ymax/2-10;
    int posXBase = args->xmax/2-2;
    afficheCadre(posXBase, posYBase);
    printf(MAGENTA);
    printf("\033[%d;%dH Vous avez perdu !", posYBase+2, posXBase-5);
    printf("\033[%d;%dH Votre Score : %d", posYBase+4, posXBase-5, args->score);
    printf("\033[%d;%dH Pressez 'ESC' pour quitter", posYBase+10, posXBase-7);
    printf("\033[%d;%dH Ou pressez 'j' pour rejouer", posYBase+11, posXBase-7);
    printf(RESET);
    fflush(stdout);
    while (1)
    {
      key = key_pressed();
        switch (key)
        {
        case QUIT:
            system("reset");
            *(args->isGameDone_ptr) = 1;
            return;
        case 'j':
            *(args->isGameDone_ptr) = 2;
            return;
        default:
            break;
        }
    }
}

//Partie de Code afichant l'ecran de victoire
void winScreen(Env *args)
{
    system("clear");
    int posYBase = args->ymax/2-10;
    int posXBase = args->xmax/2-2;
    afficheCadre(posXBase, posYBase);
    printf(GREEN);
    printf("\033[%d;%dH Vous avez Gagné !", posYBase+2, posXBase-5);
    printf("\033[%d;%dH Votre Score : %d", posYBase+4, posXBase-5, args->score);
    printf("\033[%d;%dH Pressez 'ESC' pour quitter", posYBase+10, posXBase-7);
    printf("\033[%d;%dH Ou pressez 'j' pour rejouer", posYBase+11, posXBase-7);
    printf(RESET);
    char key;
    fflush(stdout);
    while(1)
    {
        key = key_pressed();
        switch (key)
        {
        case QUIT:
            system("reset");
            *(args->isGameDone_ptr) = 1;
            return;
        case 'j':
            *(args->isGameDone_ptr) = 2;
            return;
        default:
            break;
        }
    }
}

void afficheCadre(int posXBase, int posYBase)
{
    printf(RED);
    printf("\033[%d;%dH +=======================================+", posYBase-3, posXBase-15);
    for (int i=0; i < 20; i++)
    {
        printf("\033[%d;%dH +", posYBase-(2 -i), posXBase-15);
    }
    printf("\033[%d;%dH +=======================================+", posYBase+18, posXBase-15);
    for (int i=0; i < 20; i++)
    {
        printf("\033[%d;%dH +", posYBase-(2 -i), posXBase+25);
    }

    printf("\033[%d;%dH +===========================================+", posYBase-4, posXBase-17);
    for (int i=0; i < 23; i++)
    {
        printf("\033[%d;%dH +", posYBase-(4 -i), posXBase-17);
    }
    printf("\033[%d;%dH +===========================================+", posYBase+19, posXBase-17);
    for (int i=0; i < 22; i++)
    {
        printf("\033[%d;%dH +", posYBase-(3 -i), posXBase+27);
    }
    printf(RESET);
}

int menu_option(int posXBase, int posYBase)
{
    system("clear");
    afficheCadre(posXBase, posYBase);
    printf("\033[%d;%dH Credit ", posYBase+5, posXBase);
    printf("\033[%d;%dH Aide ", posYBase+10, posXBase+1);
    fflush(stdout);
    return OPTION_CREDIT;
    
}
int menu_credit(int posXBase, int posYBase)
{
    system("clear");
    printf("\033[%d;%dH Jeux fait par Tanous et Rida...", posYBase, posXBase-10);
    printf("\033[%d;%dH Retour (Press 'r')", posYBase+2, posXBase-5);
    fflush(stdout);
    char key;
    while (key != 'r')
    {
        key = key_pressed();
    }
    system("clear");
    return RETURN;
}
int menu_aide(int posXBase, int posYBase)
{
    system("clear");
    printf("\033[%d;%dH Voici l'aide :", posYBase, posXBase-10);
    printf("\033[%d;%dH SPACE = Tire", posYBase+2, posXBase-11);
    printf("\033[%d;%dH ZQSD  = Mouvement.", posYBase+3, posXBase-11);
    printf("\033[%d;%dH ESC   = QUIT", posYBase+4, posXBase-11);
    
    printf("\033[%d;%dH Retour (Press 'r')", posYBase+6, posXBase-5);
    fflush(stdout);
    char key;
    while (key != 'r')
    {
        key = key_pressed();
    }
    system("clear");
    return RETURN;
}

void afficheMainMenu(GameTypePos easyMode, GameTypePos normalMode, GameTypePos impossibleMode, GameTypePos optionMode, GameTypePos cursor, int posXBase, int posYBase)
{
    printf("\033[%d;%dH MODE FACILE", easyMode.coord.y, easyMode.coord.x);
    printf("\033[%d;%dH MODE NORMAL ", normalMode.coord.y, normalMode.coord.x);
    printf("\033[%d;%dH MODE PROGRESSIF", impossibleMode.coord.y, impossibleMode.coord.x);
    printf("\033[%d;%dH Option", optionMode.coord.y, optionMode.coord.x);
    afficheCadre(posXBase, posYBase);
}

//Affiche le menu principale et retourne une valeur qui depend du choix du joueur 
int menu_instance(Env *args)
{
    char key;
    int actualMode = EASY;
    int posYBase = args->ymax/2-10;
    int posXBase = args->xmax/2-2;
    GameTypePos easyMode, normalMode, impossibleMode, cursor, optionMode;
    easyMode.coord.x = posXBase;
    easyMode.coord.y = posYBase;
    normalMode.coord.x = posXBase-1;
    normalMode.coord.y = posYBase+5;
    impossibleMode.coord.x = posXBase-3;
    impossibleMode.coord.y = posYBase+10;
    optionMode.coord.x = posXBase+2;
    optionMode.coord.y = impossibleMode.coord.y+5;
    cursor.coord.x = easyMode.coord.x-5;
    cursor.coord.y = easyMode.coord.y;

    
    int externalBlinkCounter=0, internalBlinkCounter=0;
	
    afficheMainMenu(easyMode, normalMode, impossibleMode, optionMode, cursor, posXBase, posYBase);
    printf("\033[%d;%dH <==> ", cursor.coord.y, cursor.coord.x); //Position the cursor before to save it
    
    fflush(stdout);
    while (1)
    {
        switch (actualMode)
        {
            case RETURN:
                afficheMainMenu(easyMode, normalMode, impossibleMode, optionMode, cursor, posXBase, posYBase);
                actualMode = EASY;
            case EASY:
                cursor.coord.x = easyMode.coord.x-5;
                cursor.coord.y = easyMode.coord.y;
                break;
            case NORMAL:
                cursor.coord.x = normalMode.coord.x-5;
                cursor.coord.y = normalMode.coord.y;
                break;
            case IMPOSSIBLE:
                cursor.coord.x = impossibleMode.coord.x-5;
                cursor.coord.y = impossibleMode.coord.y;
                break;
            case OPTION:
                cursor.coord.x = optionMode.coord.x -5;
                cursor.coord.y = optionMode.coord.y;
                break;
            case OPTION_CREDIT:
                cursor.coord.x = posXBase-5;
                cursor.coord.y = posYBase+5;
                break;
            case OPTION_AIDE:
                cursor.coord.x = posXBase-4;
                cursor.coord.y = posYBase +10;
                break;

            default:
                break;
        }
        key = key_pressed();

        //Cette partie de code permet de faire clignotter le curseur
        externalBlinkCounter++;
        if (externalBlinkCounter % 100000 == 0) 
        {
            internalBlinkCounter++;
            if (internalBlinkCounter % 2 == 0)
            {

                printf("\033[%d;%dH", cursor.coord.y, cursor.coord.x);
                printf("      ");
            }
            else
            {
                printf("\033[%d;%dH", cursor.coord.y, cursor.coord.x);
                printf(" <==> ");
            }
        }
        /*Find du code de clignotement du curseur*/

        if (key == DOWN)
        {        
            switch (actualMode)
            {
                case EASY:
                    printf("\033[%d;%dH", cursor.coord.y, cursor.coord.x);
                    printf("      ");
                    actualMode = NORMAL;
                    break;
                case NORMAL:
                    printf("\033[%d;%dH", cursor.coord.y, cursor.coord.x);
                    printf("      ");
                    actualMode = IMPOSSIBLE;
                    break;
                case IMPOSSIBLE:
                    printf("\033[%d;%dH", cursor.coord.y, cursor.coord.x);
                    printf("      ");
                    actualMode = OPTION;
                    break;
                case OPTION:
                    printf("\033[%d;%dH", cursor.coord.y, cursor.coord.x);
                    printf("      ");
                    actualMode = EASY;
                    break;


                case OPTION_CREDIT:
                    printf("\033[%d;%dH", cursor.coord.y, cursor.coord.x);
                    printf("      ");
                    actualMode = OPTION_AIDE;
                    break;
                case OPTION_AIDE:
                    printf("\033[%d;%dH", cursor.coord.y, cursor.coord.x);
                    printf("      ");
                    actualMode = OPTION_CREDIT;
                    break;

                default:
                    break;
            }
        }

        if (key == UP)
        {
            switch (actualMode)
            {
                case EASY:
                    printf("\033[%d;%dH", cursor.coord.y, cursor.coord.x);
                    printf("      ");
                    actualMode = OPTION;
                    break;
                case NORMAL:
                    printf("\033[%d;%dH", cursor.coord.y, cursor.coord.x);
                    printf("      ");
                    actualMode = EASY;
                    break;
                case IMPOSSIBLE:
                    printf("\033[%d;%dH", cursor.coord.y, cursor.coord.x);
                    printf("      ");
                    actualMode = NORMAL;
                    break;
                case OPTION:
                    printf("\033[%d;%dH", cursor.coord.y, cursor.coord.x);
                    printf("      ");
                    actualMode = IMPOSSIBLE;
                    break;


                case OPTION_CREDIT:
                    printf("\033[%d;%dH", cursor.coord.y, cursor.coord.x);
                    printf("      ");
                    actualMode = OPTION_AIDE;
                    break;
                case OPTION_AIDE:
                    printf("\033[%d;%dH", cursor.coord.y, cursor.coord.x);
                    printf("      ");
                    actualMode = OPTION_CREDIT;
                    break;

                default:
                    break;
            }
        }

        if (key == FIRE)
        {
            system("clear");
            afficheCadre(posXBase, posYBase);
            switch (actualMode)
            {
            case EASY:
                printf("\033[%d;%dH Vous avez séléctionné le mode FACILE", normalMode.coord.y, posXBase-12);
                fflush(stdout);
                sleep(2);
                system("clear");
                return EASY;
                break;

            case NORMAL:
                printf("\033[%d;%dH Vous avez séléctionné le mode NORMAL", normalMode.coord.y, posXBase-12);
                fflush(stdout);
                sleep(2);
                system("clear");
                return NORMAL;
                break;

            case IMPOSSIBLE:
                printf("\033[%d;%dH Vous avez séléctionné le mode PROGRESSIF", normalMode.coord.y, posXBase-15);
                fflush(stdout);
                sleep(2);
                system("clear");
                return IMPOSSIBLE;
                break;

            case OPTION:
                printf("\033[%d;%dH Vous avez séléctionné OPTION.", normalMode.coord.y, posXBase-10);
                fflush(stdout);
                sleep(1);
                system("clear");
                actualMode = menu_option(posXBase, posYBase);
                break;

            case OPTION_CREDIT:
                printf("\033[%d;%dH Vous avez séléctionné CREDIT.", normalMode.coord.y, posXBase-10);
                fflush(stdout);
                sleep(1);
                system("clear");
                actualMode = menu_credit(posXBase, posYBase);
                break;
            case OPTION_AIDE:
                printf("\033[%d;%dH Vous avez séléctionné AIDE.", normalMode.coord.y, posXBase-10);
                fflush(stdout);
                sleep(1);
                system("clear");
                actualMode = menu_aide(posXBase, posYBase);;
                break;

            default:
                system("clear");
				printf("\033[%d;%dH Error: Please select a mode", normalMode.coord.y, posXBase-5);
				break;
			}
		}
        if (key == 'r'){
            system("clear");
            actualMode = RETURN;
        }
        if(key == QUIT){
            return QUIT;
        }
	}
	return 0;
}
