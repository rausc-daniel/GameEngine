#ifndef GAME_H
#define GAME_H

#include <functional>

class Game {
private:
    void *window;
public:
    explicit Game(const char *title);

    ~Game();

    void Run(const std::function<void()> &renderFunction);

    void RunTriangle();

    int viewportWidth;
    int viewportHeight;
    static bool leftPressed;
    static bool upPressed;
    static bool rightPressed;
    static bool downPressed;
    static bool spacePressed;
    static float xDelta;
    static float yDelta;
    double time = 0;
    double lastTime = 0;
    double timeThisTick = 0.001;

    float GetTimeDelta() const { return static_cast<float>(timeThisTick); }
};

#endif