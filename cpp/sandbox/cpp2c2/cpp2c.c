/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
/******************************************************************************/
typedef struct animal      animal_s_ty;
typedef struct Centipede   Centipede_s_ty;
typedef struct Squirl      Squirl_s_ty;

typedef struct vtable_animal     vtable_animal_ty;
typedef struct vtable_centipede  vtable_centipede_ty;
typedef struct vtable_Squirl     vtable_Squirl_ty;
/****************************function declaration******************************/
void Ctor_Animal(animal_s_ty* ptr_animal);
void Dtor_Animal(animal_s_ty* ptr_animal); /*virtual*/
void CCtor_Animal(animal_s_ty* ptr_animal, animal_s_ty* other);
void Display_Animal(animal_s_ty *ptr_animal); /*virtual*/
void PrintCount(void);
int GetID(animal_s_ty *ptr_animal);

void Ctor_Centipede(Centipede_s_ty* ptr_centipede);
void CCtor_Centipede(Centipede_s_ty* ptr_centipede, Centipede_s_ty* other);
void Dtor_Centipede(Centipede_s_ty* ptr_centipede); /*virtual*/
void Display_Centipede(Centipede_s_ty *ptr_centipede); /*virtual*/
void BuyShues_Centipede(Centipede_s_ty *ptr_centipede);

void Ctor_Squirl(Squirl_s_ty* ptr_Squirl);
void CCtor_Squirl(Squirl_s_ty* ptr_Squirl, Squirl_s_ty* other);
void Dtor_Squirl(Squirl_s_ty* ptr_Squirl);/*virtual*/
void Display_Squirl(Squirl_s_ty *ptr_Squirl);/*virtual*/
/******************************helper functions********************************/
struct vtable_animal 
{
    void (*destructor)(animal_s_ty*);
    void (*display)(animal_s_ty*);
};
struct vtable_centipede 
{
    void (*destructor)(Centipede_s_ty*);
    void (*display)(Centipede_s_ty*);
};
struct vtable_Squirl
{
    void (*destructor)(Squirl_s_ty*);
    void (*display)(Squirl_s_ty*);
};
/******************************vtables instances*******************************/
vtable_animal_ty       vtable_animal_instance;
vtable_centipede_ty    vtable_centipede_instance;
vtable_Squirl_ty       vtable_Squirl_instance;


/******************************************************************************/
static int s_count_ANIMALS;
/***********************************animal<3***********************************/
struct animal
{
    void *vtable;
	int m_id;
};
void Ctor_Animal(animal_s_ty* ptr_animal)
{
    ptr_animal->vtable = &vtable_animal_instance;
    ptr_animal->m_id = ++s_count_ANIMALS;
    printf("Animal::Ctor()%d\n", ptr_animal->m_id);
}
void Dtor_Animal(animal_s_ty* ptr_animal)
{
    --s_count_ANIMALS;
    printf("Animal::Dtor()%d\n", ptr_animal->m_id);
}
void CCtor_Animal(animal_s_ty* ptr_animal, animal_s_ty* other)
{
    ptr_animal->m_id = ++s_count_ANIMALS;
    ptr_animal->vtable = other->vtable;
    printf("Animal::CCtor()%d\n", ptr_animal->m_id);
}

void Display_Animal(animal_s_ty *ptr_animal)
{
	printf("Animal::Display() : %d\n", ptr_animal->m_id);
}
void PrintCount(void) 
{
    printf("s_count: %d\n", s_count_ANIMALS);
}
int GetID(animal_s_ty *ptr_animal)
{
    return ptr_animal->m_id;
}
/***********************************Centipede**********************************/
struct Centipede
{
    animal_s_ty m_animal;
    int m_numLegs;
};
void Ctor_Centipede(Centipede_s_ty* ptr_centipede)
{
    Ctor_Animal(&ptr_centipede->m_animal);
    (ptr_centipede->m_animal).vtable = &vtable_centipede_instance;
    ptr_centipede->m_numLegs = 46;
    printf("Centipede::Ctor()\n");
}
void CCtor_Centipede(Centipede_s_ty* ptr_centipede, Centipede_s_ty* other)
{
    CCtor_Animal(&ptr_centipede->m_animal, &other->m_animal);
    (ptr_centipede->m_animal).vtable = (other->m_animal).vtable;
    ptr_centipede->m_numLegs = other->m_numLegs;
    printf("Centipede::CCtor()\n");
}
void Dtor_Centipede(Centipede_s_ty* ptr_centipede)
{
    printf("Centipede::dtor()\n");
	Dtor_Animal(&ptr_centipede->m_animal);
}
void Display_Centipede(Centipede_s_ty *ptr_centipede)
{
	printf("Centipede::Display() ID:%d", GetID(&ptr_centipede->m_animal));
    printf("  num legs:%d\n", ptr_centipede->m_numLegs);
}
void BuyShues_Centipede(Centipede_s_ty *ptr_centipede)
{
    printf("Centipede::BuyShues() ID:%d\n", GetID(&ptr_centipede->m_animal));
}
/*************************************Squirl***********************************/
struct Squirl
{
    animal_s_ty m_animal;
};
void Ctor_Squirl(Squirl_s_ty* ptr_Squirl)
{
    Ctor_Animal(&ptr_Squirl->m_animal);
    (ptr_Squirl->m_animal).vtable = &vtable_Squirl_instance;
    printf("Squirl::Ctor()\n");
}
void CCtor_Squirl(Squirl_s_ty* ptr_Squirl, Squirl_s_ty* other)
{
    CCtor_Animal(&ptr_Squirl->m_animal, &other->m_animal);
    (ptr_Squirl->m_animal).vtable = (other->m_animal).vtable;
    printf("Squirl::CCtor()\n");
}
void Dtor_Squirl(Squirl_s_ty* ptr_Squirl)
{
    printf("Squirl::dtor()\n");
	Dtor_Animal(&ptr_Squirl->m_animal);
}
void Display_Squirl(Squirl_s_ty *ptr_Squirl)
{
	printf("Squirl::Display() ID:%d", GetID(&ptr_Squirl->m_animal));
}

/******************************helper function*********************************/
void Foo(Centipede_s_ty* ptr_centipede)
{
    Display_Centipede(ptr_centipede);
}
/**************************************************************/
animal_s_ty Foo_INDEX(int i)
{
    animal_s_ty animal_instance;
    Centipede_s_ty instance;

    Ctor_Centipede(&instance);
    printf("Foo(int i)\n");
    Display_Centipede(&instance);
    CCtor_Animal(&animal_instance, &(instance.m_animal));
    Dtor_Centipede(&instance);

    return animal_instance;
}

vtable_animal_instance.destructor = Dtor_Animal;
vtable_animal_instance.display = Display_Animal;
vtable_centipede_instance.destructor = Dtor_Centipede;
vtable_centipede_instance.display = Display_Centipede;
vtable_Squirl_instance.destructor = Dtor_Squirl;
vtable_Squirl_instance.display = Display_Squirl;

/******************************************************************************/
int main()
{
   /*  Centipede_s_ty c;
    Ctor_Centipede(&c);
    Foo(&c);
    animal_s_ty tmp = Foo_INDEX(3);
    Display_Animal(&tmp); */

    /***/
    animal_s_ty *array[3];

    array[0] = (Centipede_s_ty *)malloc(sizeof(Centipede_s_ty));
    Ctor_Centipede((Centipede_s_ty *)array[0]);
    array[1] = (Squirl_s_ty *)malloc(sizeof(Squirl_s_ty));
    Ctor_Squirl((Squirl_s_ty *)array[1]);
    array[2] = (Centipede_s_ty *)malloc(sizeof(Centipede_s_ty));
    Ctor_Centipede((Centipede_s_ty *)array[2]);

    printf("here\n");
    vtable_animal_ty *vtable_animals;
    printf("here\n");

    for(int i=0; i < 3; ++i)
    {
        vtable_animals = array[i]->vtable;
        vtable_animals->display(array[i]); 
    }
    /***/
  /*   Dtor_Animal(&tmp);
    Dtor_Centipede(&c);  */
    return 0;
}
