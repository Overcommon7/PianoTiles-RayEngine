#pragma once
class Controls
{
public:
    static inline const string NAME = "Controls";

    static void Init();
    static void Shutdown();
private:
public:
    Controls() = delete;
    Controls(const Controls& c) = delete;
    Controls(const Controls&& c) = delete;
    Controls& operator=(const Controls& c) = delete;
    Controls& operator=(const Controls&& c) = delete;

};

