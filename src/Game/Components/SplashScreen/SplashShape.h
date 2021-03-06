#pragma once
#include <Engine/Components/Core/IComponent.h>
#include <Engine/View/Renderables.h>
#include <Engine/Core/GameObject/GameObject.h>

namespace Game
{
    class SplashShape : public Engine::IRenderableShapeComponent
    {
    public:
        SplashShape(Engine::GameObject& obj, size_t pointCount, sf::Color color, int zIndex);
        ~SplashShape();

        void OnCreate() override;
        void Update(float dt) override;
    private:
        Engine::view::Shape m_shape;
        float m_timeToDie = 5.0f;
    };
}


