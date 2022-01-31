#include "SceneManager.h"
#include "../Debug/Logger.h"
#include "../Application.h"

namespace Engine
{
    SceneManager& SceneManager::Get()
    {
        return Application::Instance().GetSceneManager();
    }

    Scene& SceneManager::CreateScene()
    {
        Scene newScene(m_nextSceneID++);
        m_scenes.emplace_back(newScene);
        return m_scenes[m_nextSceneID - 1];
    }

    Scene& SceneManager::GetSceneByIndex(uint32_t index)
    {
        DD_ASSERT(index < m_scenes.size(), "Scene with ID '%d' doesn't exist", index);
        return m_scenes[index];
    }

    void SceneManager::LoadSceneAdditively(uint32_t index)
    {
        auto scene = GetSceneByIndex(index);
        scene.Load();
    }

    void SceneManager::SetActiveScene(uint32_t index)
    {
        UnloadAllScenes();
        LoadSceneAdditively(index);
    }

    void SceneManager::UnloadSceneObjects(uint32_t index)
    {
        auto scene = GetSceneByIndex(index);
        scene.Unload();
    }

    void SceneManager::UnloadAllScenes()
    {
        for (auto& s : m_scenes)
            if (s.IsLoaded())
                s.Unload();
    }
}