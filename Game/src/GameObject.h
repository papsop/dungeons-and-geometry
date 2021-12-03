#pragma once
#include "Components/IComponent.h"

#include <unordered_map>
#include <map>
#include <queue>
#include <memory>
#include <assert.h>
#include <type_traits>

namespace Game
{
    class GameObject
    {
    public:
        // Components Management
        template<typename T>
        bool HasComponent() { return m_components.find(typeid(T).name()) != m_components.end(); }

        template<typename T>
        void AddComponent(T component) 
        {
            if constexpr(IComponent::is_derived<T>())
                m_components[typeid(T).name()] = std::make_shared<T>(component);
            if constexpr(IRenderableComponent::is_derived<T>())
                m_renderableComponents[typeid(T).name()] = std::make_shared<T>(component);
        }
        
        template<typename T>
        std::weak_ptr<T> GetComponent()
        {
            if constexpr (IComponent::is_derived<T>())
            {
                auto component = m_components[typeid(T).name()];
                return std::static_pointer_cast<T>(component);
            }
            else if constexpr (IRenderableComponent::is_derived<T>())
            {
                auto renderableComponent = m_renderableComponents[typeid(T).name()];
                return std::static_pointer_cast<T>(renderableComponent);
            }
        }

        template<typename T>
        void RemoveComponent()
        {
            if constexpr (IComponent::is_derived<T>())
                m_components.erase(typeid(T).name());
            else if constexpr (IRenderableComponent::is_derived<T>())
                m_renderableComponents.erase(typeid(T).name());
        }
        // --------------------------
        GameObject(uint32_t id, const char* debugName) : ID(id), DebugName(debugName) {};
        ~GameObject() = default;

        const uint32_t ID;
        const char* DebugName;

        void Update(float dt);
        void Render();

        void Destroy() { m_shouldDestroy = true; }
        bool ShouldDestroy() const { return m_shouldDestroy; }

    private:
        std::unordered_map<const char*, std::shared_ptr<IComponent>> m_components = {};
        std::map<const char*, std::shared_ptr<IRenderableComponent>> m_renderableComponents = {};
        bool m_shouldDestroy = false;
    };
};


