/******************************************************************************/
#include <iostream> //std::cout
#include <string>   //std::string
#include <memory>   //std::shared_ptr
#include <cstring>  
/******************************************************************************/
#include "factory.hpp"
/******************************************************************************/
using namespace ilrd::hrd26;
/******************************************************************************/
class Animals
{
    public: 
        virtual ~Animals(){}
        virtual std::string AnimalsName() = 0;
};
/******************************************************************************/
class Snake : public Animals
{
    public:
        Snake(std::string name_): m_animalname(name_)
        {
            //empty
        }
        std::string AnimalsName()
        {
            return m_animalname; 
        }
        static std::shared_ptr<Snake> CreateSnake(std::string animal_name_)
        {
            return std::shared_ptr<Snake>(new Snake(animal_name_));
        }
    private:
        std::string m_animalname;
};
/******************************************************************************/
class Dog : public Animals
{
    public:
        Dog(std::string name_): m_animalname(name_)
        {
            //empty
        }
        
        std::string AnimalsName()
        {
            return m_animalname; 
        }
        static std::shared_ptr<Dog> CreateDog(std::string animal_name_)
        {
            return std::shared_ptr<Dog>(new Dog(animal_name_));
        }
    private:
        std::string m_animalname;
};
/******************************************************************************/
int main()
{
    /*Define factory*/
    Factory<std::string, Animals, std::string>* my_factory = Singleton
                    <Factory<std::string, Animals, std::string>>::GetInstance();

    /*ADD TO HASHTABLE - name is the key, Create is CreateFunc*/
    my_factory->Add("Snake", Snake::CreateSnake);
    std::shared_ptr<Animals> SH_P_snake = my_factory->Create("Snake","Snake");

    /*ADD TO HASHTABLE - name is the key, Create is CreateFunc*/
    my_factory->Add("Dog", Dog::CreateDog);
    std::shared_ptr<Animals> SH_P_dog = my_factory->Create("Dog","Dog");

    /*Check TEST*/
    if(!(SH_P_dog->AnimalsName() == "Dog" && SH_P_snake->AnimalsName() == "Snake"))
    {
        std::cout<<"TEST FAILED"<<std::endl;
    }
    return 0;
}
/******************************************************************************/

