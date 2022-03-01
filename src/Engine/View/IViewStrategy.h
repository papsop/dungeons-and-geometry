#pragma once
#include "../View/Renderables.h"

#include <SFML/window.hpp>
#include <functional>

namespace Engine
{
    class Application;
    namespace view
    {
        class IViewStrategy
        {
        public:
            IViewStrategy(std::function<void(const sf::Event& event)> handleEvent)
            {
                m_handleEventLambda = handleEvent;
            }

            virtual ~IViewStrategy() = default;

            virtual void PollEvents() = 0;
            virtual void PreRender() = 0;
            virtual void Render(const Shape& shape) = 0;
            virtual void Render(const Circle& circle) = 0;
            virtual void Render(const Text& text) = 0;
            virtual void Render(const Line& line) = 0;
            virtual void PostRender() = 0;

            virtual sf::Vector2i GetMousePosition() = 0;
        protected:
            std::function<void(const sf::Event& event)> m_handleEventLambda;
        };
    }
}