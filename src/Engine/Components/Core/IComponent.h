#pragma once
#include "Transform.h"
#include "../../View/Renderables.h"
#include "../../View/IViewStrategy.h"
#include "../../Core/ColliderData.h"
#include "../../Debug/Logger.h"
#include "../../Core/Messaging/MessageTypes.h"
#include "../../Managers/ViewLayers.h"

#include <functional>
#include <iostream>
#include <stdint.h>
#include <type_traits>
#include <type_traits>
namespace Engine
{

    class GameObject; 
    struct CollisionData;

    class IComponent
    {
    public:
        using TRequiredFunc = std::function<void(const GameObject&)>;

        IComponent(GameObject& obj) : Owner(obj) {};
        virtual ~IComponent() = default;

        void Activate();
        void Deactivate();
        bool IsActive() { return m_isActive; }

        virtual void OnCreate() {};
        virtual void Update(float dt) {};
        virtual void OnCollisionStart(CollisionData& collision) {};
        virtual void OnCollisionEnd(CollisionData& collision) {};
        virtual void ProcessMessage(const Message& message) { };

		GameObject& Owner;

        void CheckRequiredComponents()
        {
            if(m_requiredFunction != nullptr)
                m_requiredFunction(Owner);
        }

    protected:
        template<typename... Ts>
        struct requires_impl;

        template<typename T>
        struct requires_impl<T>;
        
        template<typename T, typename... Ts>
        struct requires_impl<T, Ts...>;

        // This function asserts required components on the Owner gameObject.
        // Function call gets stored and called every time a component
        // is removed from the owner
		template<typename... Ts>
		void SetRequiredComponents();

        TRequiredFunc m_requiredFunction = nullptr;


        virtual void VirtualOnActivated() {};
        virtual void VirtualOnDeactivated() {};
        bool m_isActive = false;
    };

    // Views
    class IRenderableShapeComponent : public IComponent
    {
    public:
        IRenderableShapeComponent(GameObject& obj, view::Renderable_Type renderableType, view::Layer layer);
         
        ~IRenderableShapeComponent() = default;

        const view::Renderable& GetRenderable() { return m_renderable; };
        view::Renderable& GetMutableRenderable() { return m_renderable; };
        const view::Layer c_Layer;
    protected:
        view::Renderable m_renderable;
        Transform m_renderableTransform;
    };

    class IRenderableTextComponent : public IComponent
    {
    public:
        IRenderableTextComponent(GameObject& obj);

        ~IRenderableTextComponent() override = default;

        virtual const view::Text& GetRenderableText() = 0;
    protected:
        Transform& m_ownerTransform;
    };

	template<typename T>
	using enable_if_base_of_component = std::enable_if_t< std::is_base_of<IComponent, T>::value >;
};

#include "IComponent.inl"