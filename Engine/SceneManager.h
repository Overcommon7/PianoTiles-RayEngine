#pragma once
#include "Scene.h"

namespace RayEngine
{
    class EventSystem;

    class SceneManager
    {
    public:
        static size_t CreateScene(const string& name);
        static void LoadScene(const string& name);
        static void LoadScene(size_t id);
        static void UnloadScene(size_t id = ULLONG_MAX);
        static void CloseScene();
        static size_t GetSceneID(const string& name);
        static size_t CurrentSceneID();
        static string_view GetSceneName(size_t id);
        static bool IsCurrentScene(Scene const* scene) { return currentScene != nullptr && scene == currentScene; }
        static EventSystem* GetCurrentSceneEventSystem();
        static void PauseScene(size_t id = ULLONG_MAX);

        template<class ComponentType>
        inline static ComponentType* GetObjectOfType()
        {
            if (currentScene == nullptr) return nullptr;
            return currentScene->GetObjectOfType<ComponentType>();
        }

        template<class ComponentType>
        inline static vector<ComponentType*> GetObjectsOfType()
        {
            if (currentScene == nullptr) return {};
            return currentScene->GetObjectsOfType<ComponentType>();
        }
        
#ifdef ENGINEDLL 
    public:
#else
    private:
#endif
        static void DestroyGameObject(GameObject* object, size_t sceneID);
        static GameObject* CreateGameObject(GameObject* gameObject, string sceneName);

        static void Update();
        static void LateUpdate();
        static void Draw();
        static void LateDraw();
        static void Shutdown();

        static void SetPriority(GameObject* object);
        static EventSystem* GetEventSystem(size_t id);

    private:
        static vector<Scene*>::iterator GetScene(const string& name);
        static vector<Scene*>::iterator GetScene(size_t id);
        static void InternalUnload();
        static void MoveTransitionalGameObjects();


        static inline vector<Scene*> unloadQuries = {};
        static inline vector<GameObject*> transtionalGameObjects = {};
        static inline vector<Scene*> scenes = {};
        static inline Scene* currentScene = nullptr;
        static inline bool sceneTransitionFrame = false;
    public:
        SceneManager() = delete;
        SceneManager(const SceneManager& s) = delete;
        SceneManager(const SceneManager&& s) = delete;
        SceneManager& operator=(const SceneManager& s) = delete;
        SceneManager& operator=(const SceneManager&& s) = delete;

    };
}