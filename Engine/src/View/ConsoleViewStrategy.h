#pragma once
#include "IViewStrategy.h"

#include <SFML/Graphics.hpp>

namespace Engine
{
    namespace view
    {
        class ConsoleViewStrategy : public IViewStrategy
        {
        public:
            ConsoleViewStrategy(std::function<void(const sf::Event& event)> handleEvent);
            ~ConsoleViewStrategy() = default;

            void PollEvents() override;

            void PreRender() override;
            void Render(const Shape& shape) override;
            void PostRender() override;
            sf::Vector2i GetMousePosition() override { return { 0,0 }; }; // placeholder
        };
    };
};

