 #include "SplashController.h"
#include <Engine/Managers/ComponentManager.h>
#include <Engine/Managers/GameObjectManager.h>

#include <Engine/Core/Scene/Scene.h>

#include "SplashShape.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

namespace Game
{

    SplashController::SplashController(Engine::GameObject& obj)
        : IComponent(obj)
    {
        srand((unsigned)time(NULL));
        Engine::ComponentManager::Get().RegisterComponent(this);
    }
    
    void SplashController::OnCreate()
    {
        Engine::ComponentManager::Get().RegisterComponent(this);
    }

    SplashController::~SplashController()
    {
        Engine::ComponentManager::Get().UnregisterComponent(this);
    }

    void SplashController::Update(float dt)
    {
        m_lastTriangleSpawned -= dt;
        if (m_lastTriangleSpawned <= 0.0f)
        {
   //         auto& scene = Owner.GetScene();

   //         auto newTriangle = Engine::GameObjectManager::Get().CreateGameObject(Engine::GameObject::FilterTag::UI, "SplashShape");
   //         newTriangle->AddComponent<SplashShape>(rand() % 7 + 3, GetRandomColor(), m_triangleZIndex++);
   //         newTriangle->GetTransform().Position = GetRandomPositionOutsideWindow();
   //         newTriangle->GetTransform().Rotation = static_cast<float>(rand() % 366);

   //         //newTriangle->AddComponent<Engine::RigidbodyComponent>();

			//auto dir = GetRandomPositionInsideWindow() - newTriangle->GetTransform().Position;
			////newTriangle->GetComponent<Engine::RigidbodyComponent>()->Velocity = dir;
   //         

   //         scene.AddGameObject(newTriangle->ID);
   //         m_lastTriangleSpawned = m_triangleSpawnCooldown;
        }
    }

    // ===============
    // Private helpers
    // ===============

    sf::Vector2f SplashController::GetRandomPositionOutsideWindow()
    {
        int rq = rand() % 4;
        float chosenX = 0.0f;
        float chosenY = 0.0f;
        // 4 quadrants outside of window
        //    0
        //   +--+
        // 3 |  | 1
        //   +--+
        //    2

        // == 0 ==
        if (rq == 0)
        {
            chosenY = -75.0f;
            // shouldn't be a number, change into config window width etc.. same for next quadrants
            chosenX = static_cast <float> (rand() % 1025);
        }
        // == 1 ==
        else if (rq == 1)
        {
            chosenY = static_cast <float> (rand() % 769);
            chosenX = 1024.0f + 75.0f;
        }
        // == 2 ==
        else if (rq == 2)
        {
            chosenY = 768.0f + 75.0f;
            chosenX = static_cast <float> (rand() % 1025);
        }
        // == 3 ==
        else if (rq == 3)
        {
            chosenY = static_cast <float> (rand() % 769);
            chosenX = -75.0f;
        }

        return { chosenX, chosenY };
    }

    sf::Vector2f SplashController::GetRandomPositionInsideWindow()
    {
        float chosenX = static_cast <float> (rand() % 1025);
        float chosenY = static_cast <float> (rand() % 769);

        return { chosenX, chosenY };
    }

    sf::Color SplashController::GetRandomColor()
    {
        return sf::Color::Color(rand() % 255, rand() % 255, rand() % 255, 25);
    }

}