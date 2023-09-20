#pragma once
class Titlescreen
{
public:
    static inline const string NAME = "Titlescreen";
    static void Init();
    static void Shutdown();
private:
    class OnClick : public IObservable1<Selectable>
    {
        void OnInvoke(Selectable& arg1) override;
    };
    inline static OnClick* onMenuButtonClicked = nullptr;
    static void CreateButton(Color color, Vector2 position, Vector2 size, string* text);
public:
    Titlescreen() = delete;
    Titlescreen(const Titlescreen& t) = delete;
    Titlescreen(const Titlescreen&& t) = delete;
    Titlescreen& operator=(const Titlescreen& t) = delete;
    Titlescreen& operator=(const Titlescreen&& t) = delete;

};

