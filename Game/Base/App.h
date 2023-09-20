#pragma once
class IGamemode;


class App
{
public:
    enum class Gamestate
    {
        Titlescreen,
        Retry,
        Controls,
        Gameplay,
    };
    enum class Gamemode
    {
        None = 0,
        Classic,
        Arcade,
        Relay    
    };

	static void Init();
	static void Shutdown();
    static void Draw();
    static void Update();

    static void LoadGamemode(Gamemode gamemode);
    static void SetGamestate(Gamestate state);

    inline static Gamestate CurrentGamestate() { return currentGamestate; }
    inline static Gamemode CurrentGamemode() { return currentGamemode; }
    static IGamemode* GetCurrentGamemodeManager();

    static vector<string*> GetGamemodeNames();
    static const string* const GetGamemodeName(Gamemode gamemode);

    inline static int debug = 0;
private:
    inline static std::map<Gamemode, string> gamemodeNames = {};
    inline static std::map<Gamemode, IGamemode*> gamemodes = {};

    inline static Gamestate currentGamestate = Gamestate::Titlescreen;
    inline static Gamemode currentGamemode = Gamemode::None;
public:
    App() = delete;
    App(const App& a) = delete;
    App(const App&& a) = delete;
    App& operator=(const App& a) = delete;
    App& operator=(const App&& a) = delete;
};

