#pragma once
#include "IManager.h"
#include "../Core/Scene/Scene.h"

#include <vector>
#include "../Debug/IDebuggable.h"

namespace Engine
{
    class Application;

    class SceneManager : public IManager
    {
    public:
        static SceneManager& Get();
        
        Scene& CreateScene();
        //Scene& GetActiveScene();
        Scene& GetSceneByIndex(uint32_t index);

        // Loads all objects and adds them to already loaded ones
        void LoadSceneByIndex(uint32_t index);


        // Unloads all objects from this particular scene
        void UnloadSceneByIndex(uint32_t index);
        void UnloadAllScenes();

        void Update(float dt);

        ~SceneManager() = default;

        void SaveAllScenes();
    private:
        SceneManager() = default;

        std::vector< std::unique_ptr<Scene> > m_scenes;
        uint32_t m_nextSceneID = 0;

    friend class Application;
    };
}


