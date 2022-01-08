#include "GameObjectFactories.h"
#include "../Components/AllComponents.h"
#include "../Core/Scene.h"
#include "../Application.h"

namespace Game
{
    // DebugGO impl
    uint32_t DebugGOFactory::CreateGameObject() const
    {
        auto obj = Application::Instance().GetEntityManager().CreateEntityReturnEntity("Debug");
        uint32_t objID = 0;
        if (auto tmp = obj.lock())
        {
            objID = tmp->ID;
            tmp->GetTransform().Position = sf::Vector2f(50.0f, 50.0f);
            tmp->AddComponent<FpsCounterComponent>(*tmp);
            return tmp->ID;
        }
    }
    // PlayerFactory impl
    uint32_t PlayerFactory::CreateGameObject() const
    {
        auto obj = Application::Instance().GetEntityManager().CreateEntityReturnEntity("Player");
        uint32_t objID = 0;
        if (auto tmp = obj.lock())
        {
            objID = tmp->ID;
            tmp->GetTransform().Position = sf::Vector2f(400.0f, 200.0f);
            tmp->AddComponent<SquareComponent>(*tmp, sf::Color::Red, 1);
            tmp->AddComponent<RigidbodyComponent>(*tmp);
            tmp->AddComponent<ActorComponent>(*tmp);
            tmp->AddComponent<InputComponent>(*tmp);
            return tmp->ID;
        }
    }
    // /PlayerFactory

    // RotatingEnemyFactory impl
    uint32_t SeekingEnemyFactory::CreateGameObject() const
    {
        auto obj = Application::Instance().GetEntityManager().CreateEntityReturnEntity("Enemy1");
        uint32_t objID = 0;
        if (auto tmp = obj.lock())
        {
            objID = tmp->ID;
            tmp->GetTransform().Position = sf::Vector2f(500.0f, 350.0f);
            tmp->AddComponent<SquareComponent>(*tmp, sf::Color::Blue, 0);
            tmp->AddComponent<RigidbodyComponent>(*tmp);
            tmp->AddComponent<ActorComponent>(*tmp);
            //tmp->AddComponent<InputComponent>(*tmp);
            return tmp->ID;
        }
    }
    // /RotatingEnemyFactory

};