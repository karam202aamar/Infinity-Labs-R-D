#include <iostream>

using namespace std;
/******************************************************************************/
typedef struct Person 
{
    int key;
    int age;

}person_t;

typedef struct List 
{
    person_t *person[3];
}list_t;
/******************************************************************************/
/*find & return person by the key*/
void *ll_find(list_t ll, int key);
void foo(list_t *ll, int key, int age);
/******************************************************************************/
int main()
{
    person_t dana, karam, gil;
    list_t list;

    karam.age = 25;
    karam.key = 1;
    list.person[0] = &karam;

    dana.age = 27;
    dana.key = 2;
    list.person[1] = &dana;

    gil.age = 30;
    gil.key = 3;
    list.person[2] = &gil;

    foo(&list, 2, 28);

    return 0;
}
/******************************************************************************/
void *ll_find(list_t *ll, int key)
{
    int i = 0;
    person_t *bird_person = ll->person[i];

    while(bird_person)
    {
        if(bird_person->key == key)
        {
            return bird_person;
        }
        bird_person = ll->person[++i];
    }
    return (void*)0;
}
/******************************************************************************/
void foo(list_t *ll, int key, int age)
{
    void *vv = ll_find(ll, key);
    /*it's a wrong the compiler trust the programmer that the casting is valid*/
    person_t *p = static_cast<person_t*>(vv); 
    p->age = age;

    cout << ll->person[2]->age << endl;
    cout << ll->person[1]->age << endl;
    cout << ll->person[0]->age << endl;
}
/******************************************************************************/

