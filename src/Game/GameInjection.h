#pragma once
#include <Engine/Core/ApplicationInjection.h>
#include <Engine/Application.h>
#include <Engine/Core/GameObject.h>
#include <Engine/Debug/Backend/WindowBackendStrategy.h>
#include <Engine/Debug/Backend/ConsoleBackendStrategy.h>
#include <Engine/Core/StateMachine/BasicSceneState.h>
#include <Engine/Core/Serializing/SceneSerializer.h>

#include <Engine/Components/View.h>
#include <Engine/Components/Physics.h>
#include <Engine/Utils/VectorUtils.h>

#include "Components/Player/InputComponent.h"
#include "Components/Actor/ActorComponent.h"
#include "Components/SplashScreen/SplashBackground.h"
#include "Components/SplashScreen/SplashTitle.h"
#include "Components/SplashScreen/SplashController.h"
#include "Components/SplashScreen/SplashShape.h"
#include "Components/Actor/WeaponComponent.h"
#include "Components/Actor/Weapons/PistolWeapon.h"
#include "Components/Actor/BulletComponent.h"
#include "Physics/Filters.h"

namespace Game
{
    class Engine::Application;
    class GameInjection : public Engine::ApplicationInjection
    {
    public:
        void RegisterGameComponents(Engine::Application& app) override
        {
            // Order is important
            Engine::ComponentManager::Get().RegisterComponentType<SplashShape>();
            Engine::ComponentManager::Get().RegisterComponentType<SplashController>();
            Engine::ComponentManager::Get().RegisterComponentType<InputComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<WeaponComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<BulletComponent>();
            Engine::ComponentManager::Get().RegisterComponentType<ActorComponent>();
        }

        void BeforeGameLoop(Engine::Application& app) override
        {
            // setup logger
            Engine::Logger::Instance().AddBackend(std::make_unique<Engine::ConsoleBackendStrategy>());
            Engine::Logger::Instance().AddBackend(std::make_unique<Engine::WindowBackendStrategy>());
            Engine::Logger::Instance().SetLevel(Engine::LOGGER_LEVEL::DEBUG);

            // Scene 0 ==============================================================================
            //auto& scene0 = Engine::SceneManager::Get().CreateScene();
            //
            //auto splashScreen = Engine::GameObjectManager::Get().CreateGameObject(Engine::GameObject::FilterTag::UI, "SplashScreen");
            //splashScreen->GetTransform().Position = sf::Vector2f(512.0f, 384.0f);
            //splashScreen->AddComponent<SplashBackground>();
            //splashScreen->AddComponent<SplashTitle>();
            //splashScreen->AddComponent<SplashController>();

            //scene0.SetState(std::make_unique<Engine::BasicSceneState>(&scene0));
            //scene0.AddGameObject(splashScreen->c_ID);

            Engine::ShapeViewDef shapeViewDef;
            shapeViewDef.Color = sf::Color::Green;
            shapeViewDef.PointCount = 3;
            shapeViewDef.Radius = 2;

            Engine::PhysicsBodyDef physBodyDef;
            physBodyDef.BodyType = b2_dynamicBody;
            physBodyDef.CategoryBits = 0x1;
            physBodyDef.MaskBits = 0x1;

            // Scene 1 ==============================================================================
            auto& scene1 = Engine::SceneManager::Get().CreateScene();

            //auto centerCamera = Engine::GameObjectManager::Get().CreateGameObject(Engine::GameObject::FilterTag::UI, "MainCamera");
            //centerCamera->GetTransform().SetPosition({ 0.0f, 0.0f });
            //centerCamera->AddComponent<Engine::CameraComponent>();

			physBodyDef.CategoryBits = physics::EntityCategory::PLAYER;
			physBodyDef.MaskBits = physics::EntityMask::M_PLAYER;
            auto player = Engine::GameObjectManager::Get().CreateGameObject("Player");
            player->GetTransform().SetPosition({ 5.0f, 0.0f });
            player->AddComponent<Engine::PhysicsBodyComponent>(physBodyDef);
            player->AddComponent<Engine::ShapeViewComponent>(0, shapeViewDef);
            player->AddComponent<Engine::CircleFixtureComponent>(2.0f);
            player->AddComponent<ActorComponent>();
            player->AddComponent<InputComponent>();
            player->AddComponent<WeaponComponent>();
            auto weaponComp = player->GetComponent<WeaponComponent>();
            weaponComp->EquipWeapon(std::make_unique<PistolWeapon>(weaponComp));
            player->AddComponent<Engine::CameraComponent>();



			physBodyDef.CategoryBits = physics::EntityCategory::ENEMY;
			physBodyDef.MaskBits = physics::EntityMask::M_ENEMY;
            shapeViewDef.PointCount = 3;
            auto enemy = Engine::GameObjectManager::Get().CreateGameObject("Enemy");
            enemy->AddComponent<Engine::PhysicsBodyComponent>(physBodyDef);
            enemy->AddComponent<Engine::ShapeViewComponent>(1, shapeViewDef);
            enemy->AddComponent<Engine::CircleFixtureComponent>(2.0f);

			Engine::RectangleViewDef rectangleViewDef;
            rectangleViewDef.Color = sf::Color::Cyan;
            rectangleViewDef.Size = {10.0f, 1.0f};
            physBodyDef.BodyType = b2_staticBody;

			physBodyDef.CategoryBits = physics::EntityCategory::WALL;
			physBodyDef.MaskBits = physics::EntityMask::M_WALL;
            auto bottomBox = Engine::GameObjectManager::Get().CreateGameObject("BottomBox");
            bottomBox->GetTransform().SetPosition({ 0.0f, -15.f });
            bottomBox->AddComponent<Engine::PhysicsBodyComponent>(physBodyDef);
            bottomBox->AddComponent<Engine::RectangleFixtureComponent>();
            bottomBox->AddComponent<Engine::RectangleViewComponent>(2, rectangleViewDef);

           // scene1.AddGameObject(centerCamera->c_ID);
            scene1.AddGameObject(player->c_ID);
            scene1.AddGameObject(enemy->c_ID);
            scene1.AddGameObject(bottomBox->c_ID);

            Engine::SceneManager::Get().LoadSceneByIndex(scene1.c_ID);
        }
    };
}


