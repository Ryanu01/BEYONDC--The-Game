#include "ObjectFactory.h"
#include "Characters/Enemy.h"
#include "Characters/Warrior.h"

ObjectFactory* ObjectFactory::s_Instance = nullptr;

void ObjectFactory :: RegisterType(std::string className, std::function<GameObject* (Properties* props)> type)
{
    m_TypeRegistry[className] = type;
}

GameObject* ObjectFactory :: CreateObject(std::string type, Properties* props)
{
    GameObject* object = nullptr;
    auto it = m_TypeRegistry.find(type);
    if(it != m_TypeRegistry.end())
    {
        object = it->second(props);
    }
    return object;
}