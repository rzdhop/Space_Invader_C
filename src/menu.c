#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "struct_def.h"
#include "key_pressed.h"

int menu_instance(Env *args)
{
    char key;
    int actualMode = EASY;
    int posYBase = args->ymax/2-10;
    int posXBase = args->xmax/2-15;
    GameTypePos easyMode, normalMode, impossibleMode, cursor;
    easyMode.coord.x = posXBase;
    easyMode.coord.y = posYBase;
    normalMode.coord.x = posXBase;
    normalMode.coord.y = posYBase+5;
    impossibleMode.coord.x = posXBase;
    impossibleMode.coord.y = posYBase+10;
    cursor.coord.x = easyMode.coord.x-5;
    cursor.coord.y = easyMode.coord.y;

    
    int externalBlinkCounter=0, internalBlinkCounter=0;
	
    printf("\033[%d;%dH EASY MODE", easyMode.coord.y, easyMode.coord.x);
    printf("\033[%d;%dH NORMAL MODE", normalMode.coord.y, normalMode.coord.x);
    printf("\033[%d;%dH IMPOSSIBLE MODE", impossibleMode.coord.y, impossibleMode.coord.x);
    printf("\033[%d;%dH 8==> ", cursor.coord.y, cursor.coord.x); //Position the cursor before to save it

    while (1)
    {
        switch (actualMode)
        {
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
            default:
                break;
        }
        key = key_pressed();

        //Below code is to make the selector blinking - increase to blink slower - decrease to blink faster
        externalBlinkCounter++;
        if (externalBlinkCounter % 200000 == 0) 
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
                printf(" 8==> ");
            }
        }
        /*end of blinking code*/

        if (key == DOWN)
        {        
            switch (actualMode)
            {
                case EASY:
                    printf("\033[%d;%dH", cursor.coord.y, cursor.coord.x);
                    printf("      ");
                    cursor.coord.x = normalMode.coord.x-5;
                    cursor.coord.y = normalMode.coord.y;
                    actualMode = NORMAL;
                    break;
                case NORMAL:
                    printf("\033[%d;%dH", cursor.coord.y, cursor.coord.x);
                    printf("      ");
                    cursor.coord.x = impossibleMode.coord.x-5;
                    cursor.coord.y = impossibleMode.coord.y;
                    actualMode = IMPOSSIBLE;
                    break;
                case IMPOSSIBLE:
                    printf("\033[%d;%dH", cursor.coord.y, cursor.coord.x);
                    printf("      ");
                    cursor.coord.x = easyMode.coord.x-5;
                    cursor.coord.y = easyMode.coord.y;
                    actualMode = EASY;
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
                    cursor.coord.x = impossibleMode.coord.x-5;
                    cursor.coord.y = impossibleMode.coord.y;
                    actualMode = IMPOSSIBLE;
                    break;
                case NORMAL:
                    printf("\033[%d;%dH", cursor.coord.y, cursor.coord.x);
                    printf("      ");
                    cursor.coord.x = easyMode.coord.x-5;
                    cursor.coord.y = easyMode.coord.y;
                    actualMode = EASY;
                    break;
                case IMPOSSIBLE:
                    printf("\033[%d;%dH", cursor.coord.y, cursor.coord.x);
                    printf("      ");
                    cursor.coord.x = normalMode.coord.x-5;
                    cursor.coord.y = normalMode.coord.y;
                    actualMode = NORMAL;
                    break;
                default:
                    break;
            }
        }

        if (key == FIRE)
        {
            switch (actualMode)
            {
            case EASY:
                system("clear");
                printf(" You selected EASY MODE\nLOADING....");
                sleep(2);
                return EASY;
                break;

            case NORMAL:
                system("clear");
                printf(" You selected NORMAL MODE\nLOADING....");
                sleep(2);
                return NORMAL;
                break;

            case IMPOSSIBLE:
                system("clear");
                printf(" You selected IMPOSSIBLE MODE\nLOADING....");
                sleep(2);
                return IMPOSSIBLE;
                break;

            default:
                system("clear");
				printf("Error: Please select a mode");
				break;
			}
		}
        if(key == QUIT){
            return QUIT;
        }
	}
	return 0;
}
