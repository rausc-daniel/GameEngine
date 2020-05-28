#include <iostream>
#include "Game.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

bool Game::leftPressed;
bool Game::upPressed;
bool Game::rightPressed;
bool Game::downPressed;
bool Game::spacePressed;
float Game::xDelta;
float Game::yDelta;

void OnKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_A)
        Game::leftPressed = action != GLFW_RELEASE;
    if (key == GLFW_KEY_W)
        Game::upPressed = action != GLFW_RELEASE;
    if (key == GLFW_KEY_D || key == GLFW_KEY_E)
        Game::rightPressed = action != GLFW_RELEASE;
    if (key == GLFW_KEY_S || key == GLFW_KEY_O)
        Game::downPressed = action != GLFW_RELEASE;
    if (key == GLFW_KEY_SPACE)
        Game::spacePressed = action != GLFW_RELEASE;

    if (key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(window, true);
}

float oldPosX, oldPosY;
void OnMouse(GLFWwindow* window, double posX, double posY)
{
    Game::xDelta = oldPosX - posX;
    Game::yDelta = oldPosY - posY;
    oldPosX = posX;
    oldPosY = posY;
}

Game::Game(const char* title)
{
    if (!glfwInit()){
        printf("GLFW init failed\n");
        exit(1);
    }
    window = glfwCreateWindow(1280, 720, title, NULL, NULL);
    if (window == NULL) {
        printf("GLFW window creation failed\n");
        exit(1);
    }
    auto glfwWindow = (GLFWwindow*)window;
    glfwMakeContextCurrent(glfwWindow);
    glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(glfwWindow, OnKeyboard);
    glfwSetCursorPosCallback(glfwWindow, OnMouse);
    glfwGetWindowSize(glfwWindow, &viewportWidth, &viewportHeight);
    glEnable(GL_DEPTH_TEST);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cout << "GLEW init failed " << glewGetErrorString(err) << "\n";
        exit(1);
    }
}

Game::~Game() 
{
    glfwTerminate();
}

void Game::Run(std::function<void()> renderFunction)
{
    auto glwWindow = (GLFWwindow*)window;
    while (!glfwWindowShouldClose(glwWindow))
    {
        glfwGetWindowSize(glwWindow, &viewportWidth, &viewportHeight);
        glViewport(0, 0, viewportWidth, viewportHeight);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        time = glfwGetTime();
        timeThisTick = time - lastTime;
        lastTime = time;
        renderFunction();
        glfwSwapBuffers(glwWindow);
        glfwPollEvents();
    }
}

void Game::RunTriangle()
{
    Run([=]()
    {
        glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();
    });
}
