#pragma once


class Retry
{
public:
    static void Init();
    static void OnStart(const string& score, const string& gamemode);
    static void Shutdown();

    static inline const string NAME = "Retry";
private:
    inline static TextRenderer* score = nullptr;
    inline static TextRenderer* mode = nullptr;
    inline static GameObject* proModeText = nullptr;
    inline static Button* retry = nullptr;
    inline static Button* exit = nullptr;

    static Button* CreateButton(float xPosition, const string& name);
    class OnClick : public IObservable1<Selectable>
    {
        void OnInvoke(Selectable& arg1) override;
    };
    inline static OnClick* onClick = nullptr;
public:
    Retry() = delete;
    Retry(const Retry& r) = delete;
    Retry(const Retry&& r) = delete;
    Retry& operator=(const Retry& r) = delete;
    Retry& operator=(const Retry&& r) = delete;

};

