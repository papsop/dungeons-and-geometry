#include "PlayerControllerComponent.h"

#include "../../GameObject.h"

namespace Game
{
    PlayerControllerComponent::PlayerControllerComponent(GameObject &obj) : IUpdatableComponent(obj)
    {
        m_inputManager = SingletonManager::Instance().GetInputManager();
    }

    void PlayerControllerComponent::Init() 
    {
        m_actorComponent = m_owner.GetComponent<ActorComponent>();
    }

    void PlayerControllerComponent::Update(float dt)
    {
        if (auto tmpInput = m_inputManager.lock())
        {
            // keyboard
            sf::Vector2f movement(0.0f, 0.0f);

            if (tmpInput->IsKeyPressed(sf::Keyboard::Key::W))
                movement.y -= dt;
            if (tmpInput->IsKeyPressed(sf::Keyboard::Key::S))
                movement.y += dt;
            if (tmpInput->IsKeyPressed(sf::Keyboard::Key::A))
                movement.x -= dt;
            if (tmpInput->IsKeyPressed(sf::Keyboard::Key::D))
                movement.x += dt;

            // normalize myself since the library doesnt include it zZz
            float movementVecLength = sqrt(movement.x * movement.x + movement.y * movement.y);
            if (movementVecLength != 0)
                movement /= movementVecLength;

            if (auto tmp = m_actorComponent.lock())
            {
                tmp->RotateTo(tmpInput->GetMousePos());
                tmp->SetMovementVector(movement);
            }
        }
    }
};