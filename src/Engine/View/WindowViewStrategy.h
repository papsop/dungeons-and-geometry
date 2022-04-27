#pragma once
#include "IViewStrategy.h"

#include <SFML/Graphics.hpp>

namespace Engine
{
    namespace view
    {
        class WindowViewStrategy : public IViewStrategy
        {
        public:
            WindowViewStrategy(std::function<void(const sf::Event& event)> handleEvent);
            ~WindowViewStrategy();

            void PollEvents() override;

            void PreRender() override;
            void RenderRenderable(const Renderable& renderable) override;
            void Render(const Shape& shape) override;
            void Render(const Circle& circle) override;
            void Render(const Text& text) override;
            void Render(const Rectangle& rectangle) override;
            void Render(const Line& line) override;
            void PostRender() override;


			void DebugRenderLine(Engine::math::Vec2 a, Engine::math::Vec2 b, sf::Color color) override;
			void DebugRenderCircle(Engine::math::Vec2 center, float radius, sf::Color color) override;
            void DebugRenderRectangle(Engine::math::Vec2 center, Engine::math::Vec2 size, float angle, sf::Color color) override;

            void SetView(const CameraData& cameraData) override;
            sf::Vector2f GetMousePosition() override;
            

        private:
            // conversions
            sf::CircleShape     CircleToSFMLCircleShape(const view::Circle& circle);
			sf::CircleShape     ShapeToSFMLCircleShape(const view::Shape& shape);
            sf::RectangleShape  RectangleToSFMLRectangleShape(const view::Rectangle& rectangle);
            sf::Text            TextToSFMLText(const view::Text& text);
            float               Box2DRotationToSFML(float angle);
            // ==============

            sf::RenderWindow m_window;
            sf::Font m_font;
        };
    };
};


