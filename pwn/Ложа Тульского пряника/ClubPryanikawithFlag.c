#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void win()
{
    printf("TulaCTF{Da_Zdravstvuet_Tula_Da_Zdravstvuet_71}\n");
    _exit(0);
}

void next_level()
{
    char buffer[64];

    fgets(buffer, sizeof(buffer), stdin);

    printf(buffer);

    exit(1);
}

int main(int argc, char **argv)
{
    int target = 71;
    char buffer[64];

    printf("Hi, what's the passphrase?\n");
    fgets(buffer, sizeof(buffer), stdin);
    printf(buffer);
  
    if(target == 71) 
    {
        printf("NEXT\n");
        next_level();
    }
    else
    {
        printf("ALAS...\n");

    }
    
}