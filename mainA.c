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

    return 0;
}
