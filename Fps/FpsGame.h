#ifndef FPS_GAME_H
#define FPS_GAME_H

#include <Shader.h>
#include <Game.h>
#include <Texture.h>
#include <memory>
#include <Vector3.h>
#include <Matrix.h>
#include <vector>
#include <VertexPositionUV.h>

class FpsGame : public Game {
    std::vector<VertexPositionUV> groundVertices = std::vector<VertexPositionUV>();
    GLuint groundVertexBuffer;
    std::vector<VertexPositionUV> wallVertices = std::vector<VertexPositionUV>();
    GLuint wallVertexBuffer;
    std::shared_ptr<Texture> groundTexture;
    std::shared_ptr<Shader> groundShader;
    std::shared_ptr<Texture> wallTexture;
    std::shared_ptr<Texture> normalTexture;
    std::shared_ptr<Shader> wallShader;
    Matrix projection;
    Matrix view;
    float xRotation = 0;
    float yRotation = 0;
    Vector3 lightDirection = Vector3(-0.707f, 0, 0.707f);
    Vector3 movement = Vector3(0, 0, 0);
    float MovementSpeed = 10.0f;
    float RotationSpeed = 0.3f;
    float DegreeToRadians = (1.0f / 180.0f) * 3.14159f;

    void SetupProjection();

    void UpdateCamera();

    void CalculateMovement(float angle);

    void Input();

    void DrawFPS();

public:
    FpsGame();

    ~FpsGame() = default;

    void RunGame();

    static void DrawCrosshair();

    void DrawVertices(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture, int vertexBuffer,
                      int numberOfVertices);

    void AddBox(float x, float y) {
        float size = 4;
        float x0 = x * size;
        float x1 = (x + 1) * size;
        float y0 = y * size;
        float y1 = (y + 1) * size;
        float z0 = 0;
        float z1 = size;

        //front
        wallVertices.emplace_back(x1, y0, z1, 0, -1, 0, 1, 0, 0, 1.0f, 1.0f);
        wallVertices.emplace_back(x0, y0, z1, 0, -1, 0, 1, 0, 0, 0.0f, 1.0f);
        wallVertices.emplace_back(x0, y0, z0, 0, -1, 0, 1, 0, 0, 0.0f, 0.0f);
        wallVertices.emplace_back(x1, y0, z0, 0, -1, 0, 1, 0, 0, 1.0f, 0.0f);

        //left
        wallVertices.emplace_back(x0, y0, z1, -1, 0, 0, 0, -1, 0, 1.0f, 1.0f);
        wallVertices.emplace_back(x0, y1, z1, -1, 0, 0, 0, -1, 0, 0.0f, 1.0f);
        wallVertices.emplace_back(x0, y1, z0, -1, 0, 0, 0, -1, 0, 0.0f, 0.0f);
        wallVertices.emplace_back(x0, y0, z0, -1, 0, 0, 0, -1, 0, 1.0f, 0.0f);

        //back
        wallVertices.emplace_back(x1, y1, z1, 0, 1, 0, -1, 0, 0, 1.0f, 1.0f);
        wallVertices.emplace_back(x0, y1, z1, 0, 1, 0, -1, 0, 0, 0.0f, 1.0f);
        wallVertices.emplace_back(x0, y1, z0, 0, 1, 0, -1, 0, 0, 0.0f, 0.0f);
        wallVertices.emplace_back(x1, y1, z0, 0, 1, 0, -1, 0, 0, 1.0f, 0.0f);

        //right
        wallVertices.emplace_back(x1, y0, z1, 1, 0, 0, 0, 1, 0, 1.0f, 1.0f);
        wallVertices.emplace_back(x1, y1, z1, 1, 0, 0, 0, 1, 0, 0.0f, 1.0f);
        wallVertices.emplace_back(x1, y1, z0, 1, 0, 0, 0, 1, 0, 0.0f, 0.0f);
        wallVertices.emplace_back(x1, y0, z0, 1, 0, 0, 0, 1, 0, 1.0f, 0.0f);
    }
};

#endif
