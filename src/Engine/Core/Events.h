#pragma once
#include "EventData.h"
#include "../Managers/EventManager.h"

#include <stdint.h>


namespace Engine
{

    template<typename T>
    class IEventDispatcher
    {
    public:

        IEventDispatcher() = default;
        virtual ~IEventDispatcher() = default;

        virtual void DispatchEvent(const T eventData)
        {
            EventManager::Get().DispatchEvent<T>(eventData);
        };
    };

    template<typename T>
    class IEventListener
    {
    public:
        IEventListener() = default;
        ~IEventListener() = default;

        void OnInit()
        {
            EventManager::Get().RegisterEventListener<T>(this);
        }
        
        void OnDestroy()
        {
            EventManager::Get().UnregisterEventListener<T>(this);
        }

        virtual void ReceiveEvent(const T& eventData) = 0;
    };
}


