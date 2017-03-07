#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct // To store the information of each player.
{
    char type[7];
    char name[41];
    float HP;
    int Smartness;
    float Strength;
    int Magic;
    int Luck;
    int Dexterity;
    int Position;

}defPlayer;
char Elf[] = {"Elf"};
char Human[] = {"Human"};
char Ogre[] = {"Ogre"};
char Wizard[] = {"Wizard"};

typedef struct // To store the information of each slot.
{
    int Num;
    char Type[13];

}defSlot;
char Ground[] = {"Level Ground"};
char Hill[] = {"Hill"};
char City[] = {"City"};

int main()
{
    srand(time(NULL));
    int playerNum;
    int i = 0;
    printf("How many player do you want to create(MAX 6): ");
    scanf("%d", &playerNum);
    getchar();

    // Assign the size to player array by users.
    defPlayer *Player;
    Player = (int*)malloc(playerNum * sizeof(defPlayer));

    while(i<playerNum)
    {
        char c;
        // Assign a type to each player.
  TYPE: printf("Please select player%d's type:\nA. Elf  B. Human    C. Ogre    D. Wizard\n", i+1);
        c = getchar();
        if(c == 'a' || c == 'A')
        {
            strcpy(Player[i].type , Elf);
        }
        else if(c == 'b' || c == 'B')
        {
            strcpy(Player[i].type , Human);
        }
        else if(c == 'c' || c == 'C')
        {
            strcpy(Player[i].type , Ogre);
        }
        else if(c == 'd' || c == 'D')
        {
            strcpy(Player[i].type , Wizard);
        }
        else
        {
            puts("Error!");
            goto TYPE;
        }

        // Get the name of each player from users.
        printf("Please input player%d's name(MAX 40): ", i+1);
        scanf("%s",Player[i].name);
        getchar();

        // Initialize all players' life points to 100.
        Player[i].HP = 100;

        // Part B starts here.
        if(strcmp(Human , Player[i].type) == 0)
        {
            int n;
          // Assign points to capabilities.
          A:Player[i].Smartness = 1 + rand()%100;
            Player[i].Strength = 1 + rand()%(100);
            Player[i].Magic = 1 + rand()%(100);
            n = Player[i].Smartness + (int)Player[i].Strength + Player[i].Magic;
            // If the sum is greater than 300, assign points again.
            if(n >= 300)
            {
                goto A;
            }
            else
            {
                Player[i].Luck = 1 + rand()%(300-n);
            }
            n = Player[i].Smartness + (int)Player[i].Strength + Player[i].Magic + Player[i].Luck;
            if(n >= 300)
            {
                goto A;
            }
            else
            {
                Player[i].Dexterity = 1 + rand()%(300-n);
            }
            n = Player[i].Smartness + (int)Player[i].Strength + Player[i].Magic + Player[i].Luck + Player[i].Dexterity;
            if(n >= 300)
            {
                goto A;
            }
        }
        if(strcmp(Ogre , Player[i].type) == 0) //Assigning capabilities to Ogres
        {
            int n;
            //Assigning points to capabilities
             Player[i].Magic = 0;
             Player[i].Strength=  rand()%(100 +1 -80)+80 ;
             Player[i].Dexterity= rand()%(100 +1 -80)+80;

           B:Player[i].Smartness=  rand()%20;
             Player[i].Luck= rand()%50;
             n= Player[i].Smartness + (int)Player[i].Luck;
             if(n>=50)
             {
                 goto B;
             }
         }

         if(strcmp(Elf, Player[i].type)==0)
         {
             Player[i].Luck= rand()%(100 +1 -60)+60;
             Player[i].Smartness= rand()%(100 +1 -70)+7;
             Player[i].Strength= rand()%(50 +1 -1)+1;
             Player[i].Magic = rand()%(79 +1 -51)+51;
             Player[i].Dexterity=rand()%100 +1;

         }
         if(strcmp (Wizard, Player[i].type)==0)
         {
             Player[i].Luck= rand()%(100 +1 -50)+50;
             Player[i].Smartness=rand()%(100 +1 -90)+90;
             Player[i].Strength= rand()%(20 +1 -1)+1;
             Player[i].Magic=rand()%(100 +1 -80)+1;
             Player[i].Dexterity= rand()%100;
         }
        i++;
        // Part B ends here.
    }
    // Get the total number of slots from users.
    printf("How many slots do you want(MAX 20): ");
    int slotNum;
    scanf("%d", &slotNum);
    // Assign the size to the slot array by users.
    defSlot *Slot;
    Slot = (int*)malloc(slotNum * sizeof(defSlot));

    i = 0;
    while(i < slotNum)
    {
        // Initialize slot number to -1. It makes it easy to mark the position of each player.
        Slot[i].Num = -1;

        // Assign a type to the slot randomly.
        int r = 1+ rand()%3;
        if(r == 1)
        {
            strcpy(Slot[i].Type , Ground);
        }
        else if(r == 2)
        {
            strcpy(Slot[i].Type , Hill);
        }
        else
        {
            strcpy(Slot[i].Type , City);
        }
        i++;
    }

    // Define a new array with size of the max size of slots, then it can be used to ensure
    // that only one player is assigned to a slot.
    int markArr[20];
    for(i=0; i<20; i++)
    {
        markArr[i] = 1;
    }
    // Assign players to slots randomly.
    for(i=0; i< playerNum; i++)
    {
        int r = rand()%slotNum;
        if(markArr[r] != 0)
        {
            Player[i].Position = r;
            Slot[r].Num = i;
            markArr[r] = 0;
        }
        else
        {
            i--;
        }
    }

    i = 0;
    while(i<playerNum)
    {
        int P = Player[i].Position;
        C:printf("What do you want to do on player%d?\nA. Move to previous slot\n"
               "B. Move to next slot\nC. attack\n",i+1);
        getchar();
        char c;
        c = getchar();
        // Part C. Players move.
        if(c == 'a' || c == 'A')
        {
            // If the previous slot does not exist or there is a player on that slot.
            if(P-1<0 || Slot[P-1].Num != -1)
            {
                puts("Error! You cannot move to that slot.");
                goto C;
            }
            else
            {
                Player[i].Position = P-1;
                Slot[P-1].Num = i;// To mark that player i is on this slot.
                if(strcmp(Hill , Slot[P-1].Type) == 0)
                {
                    if(Player[i].Dexterity < 50)
                    {
                        Player[i].Strength -= 10;
                    }
                    else if(Player[i].Dexterity <= 60)
                    {
                        Player[i].Strength += 10;
                    }
                }
                else if(strcmp(City , Slot[P-1].Type) == 0)
                {
                    if(Player[i].Smartness > 60)
                    {
                        Player[i].Magic += 10;
                    }
                    else if(Player[i].Smartness <= 50)
                    {
                        Player[i].Dexterity -= 10;
                    }
                }
            }

        }
        else if(c == 'b' || c == 'B')
        {
            // If the next slot does not exist or there is a player on that slot.
            if(P+1>slotNum || Slot[P+1].Num != -1)
            {
                puts("Error! You cannot move to that slot!\n");
                goto C;
            }
            else
            {
                Player[i].Position = P+1;
                Slot[P+1].Num = i;
                if(strcmp(Hill , Slot[P+1].Type) == 0)
                {
                    if(Player[i].Dexterity < 50)
                    {
                        Player[i].Strength -= 10;
                    }
                    else if(Player[i].Dexterity <= 60)
                    {
                        Player[i].Strength += 10;
                    }
                }
                else if(strcmp(City , Slot[P+1].Type) == 0)
                {
                    if(Player[i].Smartness > 60)
                    {
                        Player[i].Magic += 10;
                    }
                    else if(Player[i].Smartness <= 50)
                    {
                        Player[i].Dexterity -= 10;
                    }
                }
            }
        }
        // Part D. Attack action.
        else if(c == 'c' || c == 'C')
        {
            // Define an array to store the distance from each player to player i.
            unsigned int *distanceArr;
            distanceArr = (int*)malloc(playerNum * sizeof(int));

            // store the distance.
            for(int j=0; j<playerNum; j++)
            {
                distanceArr[j] = Player[j].Position - Player[i].Position;
            }

            // Sort the array to figure out the shortest distance excluding 0.
            for(int j=0; j<playerNum-1; j++)
            {
                for(int k=j+1; k<playerNum; k++)
                {
                    int tmp;
                    if(distanceArr[k] < distanceArr[j])
                    {
                        tmp = distanceArr[k];
                        distanceArr[k] = distanceArr[j];
                        distanceArr[j] = tmp;
                    }
                }
            }
            int closest = distanceArr[1];

            unsigned int n;
            int counter = 0;
            int mark[2];
            int *ptr = mark;
            // Figure out how many players hold the shortest distance.
            for(int j=0; j<playerNum; j++)
            {
                n = Player[j].Position - Player[i].Position;
                if(n == closest)
                {
                    *ptr++ = j;
                    counter += 1;
                }
            }

            // Only one player holds the shortest distance.
            if(counter == 1)
            {
                if(Player[mark[0]].Strength <= 70)
                {
                    Player[mark[0]].HP -= (0.5*Player[mark[0]].Strength);
                }
                else
                {
                    Player[i].HP -= (0.3*Player[mark[0]].Strength);
                }
            }
            // Two players hold the shortest distance.
            else if(counter == 2)
            {
                printf("Two closest players found. Who do you want to attack?\n"
                       "A. Player%d Name:%s Type:%s\nB. Player%d Name:%s Type:%s\n"
                       , mark[0]+1, Player[mark[0]].name, Player[mark[0]].type
                       , mark[1]+1, Player[mark[1]].name, Player[mark[1]].type);
                char c;
                c = getchar();

                if(c == 'a' || c == 'A')
                {
                    if(Player[mark[0]].Strength <= 70)
                    {
                        Player[mark[0]].HP -= (0.5*Player[mark[0]].Strength);
                    }
                    else
                    {
                        Player[i].HP -= (0.3*Player[mark[0]].Strength);
                    }
                }
                else if(c == 'b' || c == 'B')
                {
                    if(Player[mark[1]].Strength <= 70)
                    {
                        Player[mark[1]].HP -= (0.5*Player[mark[1]].Strength);
                    }
                    else
                    {
                        Player[i].HP -= (0.3*Player[mark[1]].Strength);
                    }
                }
            }
        }
        i++;
    }

    // Print out.
    for(i=0; i<playerNum; i++)
    {
        printf("%s (%s, %.2f)\n", Player[i].name, Player[i].type, Player[i].HP);
    }

    return 0;
}
