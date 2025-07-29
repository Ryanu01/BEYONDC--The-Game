#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include<map>
#include<string>
#include<memory>
#include<functional>
#include "Object/GameObject.h"

class ObjectFactory
{
private:
    ObjectFactory(){}
    static ObjectFactory* s_Instance;
    std::map<std::string, std::function<GameObject* (Properties* props)>> m_TypeRegistry;

public:
    GameObject* CreateObject(std::string type, Properties* props);
    void RegisterType(std::string className, std::function<GameObject* (Properties* props)> type);
    static ObjectFactory* GetInstance(){return s_Instance = (s_Instance != nullptr) ? s_Instance : new ObjectFactory();}
    
};

template<class Type>
class Registrar{
    public:
        Registrar(std::string className){
            ObjectFactory::GetInstance()->RegisterType(className, [](Properties* props)->GameObject* {return new Type(props);});
        }
};

#endif