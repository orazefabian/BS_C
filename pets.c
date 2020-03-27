
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char* name;
    char  owner[7];
} Pet;


Pet* createPet(char* name, const char* owner)
{
    Pet pet;
    pet.name = name;
    strcpy(pet.owner, owner);

    return &pet;
}


int main()
{
    Pet* dog = createPet("Buddy", "Brian Kernighan");
    Pet* cat = createPet("Kitty", "Dennis Ritchie");

    Pet dog2 = *dog;

    printf("%s belongs to %s\n", dog->name, dog->owner);
    printf("%s belongs to %s\n", cat->name, cat->owner);
    printf("%s belongs to %s\n", dog2.name, dog2.owner);

    free(dog);
    free(cat);
}
