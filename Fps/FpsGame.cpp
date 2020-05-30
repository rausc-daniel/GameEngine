#include "FpsGame.h"
#include "Sprite.h"
#include "VertexPositionUV.h"

FpsGame::FpsGame() : Game("Fps") {
    groundTexture = std::make_shared<Texture>("Ground.png");
    float levelWidth = 20;
    float levelHeight = 20;
    int uvTiles = 4;
    groundVertices.emplace_back(
            levelWidth, levelHeight, 0.0f,//pos
            0, 0, 1,//normal
            1, 0, 0,//tangent
            uvTiles, uvTiles);
    groundVertices.emplace_back(
            -levelWidth, levelHeight, 0.0f,
            0, 0, 1,//normal
            1, 0, 0,//tangent
            0.0f, uvTiles);
    groundVertices.emplace_back(
            -levelWidth, -levelHeight, 0.0f,
            0, 0, 1,//normal
            1, 0, 0,//tangent
            0.0f, 0.0f);
    groundVertices.emplace_back(
            levelWidth, -levelHeight, 0.0f,
            0, 0, 1,//normal
            1, 0, 0,//tangent
            uvTiles, 0.0f);

    wallTexture = std::make_shared<Texture>("Wall.png");
    normalTexture = std::make_shared<Texture>("NormalMap.png");
    AddBox(0, 0);
    AddBox(2, 1);

    // Load shader from disk
    groundShader = Shader::Load("./Shader/ground");
    wallShader = Shader::Load("./Shader/wall");

    glGenBuffers(1, &groundVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, groundVertexBuffer);
    auto sizeInBytes = sizeof(VertexPositionUV) * groundVertices.size();
    glBufferData(GL_ARRAY_BUFFER, sizeInBytes, groundVertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &wallVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, wallVertexBuffer);
    sizeInBytes = sizeof(VertexPositionUV) * wallVertices.size();
    glBufferData(GL_ARRAY_BUFFER, sizeInBytes, wallVertices.data(), GL_STATIC_DRAW);

    SetupProjection();
    glEnable(GL_TEXTURE_2D);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void FpsGame::SetupProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float zNear = 0.1f;
    float zFar = 100.0f;
    GLfloat aspect = static_cast<float>(viewportWidth) / static_cast<float>(viewportHeight);
    float fov = 60.0f;
    float fovH = std::tan(fov * DegreeToRadians / 2.0f) * zNear;
    float fovW = fovH * aspect;
    glFrustum(-fovW, fovW, -fovH, fovH, zNear, zFar);

    glGetFloatv(GL_PROJECTION_MATRIX, projection.m);
}

void FpsGame::UpdateCamera() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(yRotation, 1, 0, 0);
    glRotatef(xRotation, 0, 1, 0);
    glRotatef(-90, 1, 0, 0);
    xDelta = 0;
    yDelta = 0;
    glTranslatef(movement.x, movement.y, -2);

    glGetFloatv(GL_MODELVIEW_MATRIX, view.m);
}

void FpsGame::Input() {
    if (leftPressed)
        CalculateMovement(xRotation - 90);
    else if (rightPressed)
        CalculateMovement(xRotation + 90);
    else if (upPressed)
        CalculateMovement(xRotation);
    else if (downPressed)
        CalculateMovement(xRotation + 180);
    xRotation -= xDelta * RotationSpeed;
    yRotation -= yDelta * RotationSpeed;
    if (yRotation < -90)
        yRotation = -90;
    if (yRotation > 70)
        yRotation = 70;
}

void FpsGame::CalculateMovement(float angle) {
    movement.x -= std::sin(angle * DegreeToRadians) * MovementSpeed * static_cast<float>(timeThisTick);
    movement.y -= std::cos(angle * DegreeToRadians) * MovementSpeed * static_cast<float>(timeThisTick);
}

void
FpsGame::DrawVertices(const std::shared_ptr<Shader> &shader, const std::shared_ptr<Texture> &texture, int vertexBuffer,
                      int numberOfVertices) {
    // Step 1: Assign shader and texture
    shader->Use();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture->handle);
    // Specify vertex attributes to be used (position and uv), not really used, just for future use
    glGetAttribLocation(shader->GetHandle(), "vertexPosition_modelspace");
    glGetAttribLocation(shader->GetHandle(), "vertexNormal");
    glGetAttribLocation(shader->GetHandle(), "vertexTangent");
    glGetAttribLocation(shader->GetHandle(), "uv");

    // Step 2: Setup uniforms
    Matrix worldViewProjection = projection * view;
    auto worldViewProjectionLocation = glGetUniformLocation(shader->GetHandle(), "worldViewProjection");
    glUniformMatrix4fv(worldViewProjectionLocation, 1, false, worldViewProjection.m);
    auto timeLocation = glGetUniformLocation(shader->GetHandle(), "time");
    glUniform1f(timeLocation, (float) time);
    auto lightDirectionLocation = glGetUniformLocation(shader->GetHandle(), "lightDirection");
    glUniform3f(lightDirectionLocation, lightDirection.x, lightDirection.y, lightDirection.z);

    glActiveTexture(GL_TEXTURE0);
    auto diffuseLocation = glGetUniformLocation(shader->GetHandle(), "diffuse");
    glUniform1i(diffuseLocation, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, normalTexture->handle);
    auto normalMapLocation = glGetUniformLocation(shader->GetHandle(), "normalMap");
    glUniform1i(normalMapLocation, 1);

    glActiveTexture(GL_TEXTURE0);

    // Step 4: Assign vertexbuffer and location offsets
    //glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    // Set Vertex Format
    //position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionUV), 0);
    //normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionUV), reinterpret_cast<void *>(3 * 4));
    //tangent
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionUV), reinterpret_cast<void *>(6 * 4));
    //uv
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionUV), reinterpret_cast<void *>(9 * 4));

    // Step 5: Finally render with shader and vertexbuffer
    glDrawArrays(GL_QUADS, 0, numberOfVertices);
    // Restore crap
    glDisableVertexAttribArray(0);
    glEnable(GL_TEXTURE_2D);
    glUseProgram(0);
}

void FpsGame::DrawFPS() {
    float fps = 1 / GetTimeDelta();

    /*
     *  setup:
     *      load font atlas
     *      load shader file from disk
     *  once:
     *      switch into 2d mode
     *  for each digit:
     *      calculate offset in font atlas
     *      render quad using the uv offset to read atlas at correct position and corresponding shader
     *  once:
     *      switch back into 3d mode
    */

    printf("%f FPS\n", fps);
}

void FpsGame::RunGame() {
    Run([=]() {
        Input();
        SetupProjection();
        UpdateCamera();
        DrawVertices(groundShader, groundTexture, groundVertexBuffer, groundVertices.size());
        DrawVertices(groundShader, wallTexture, wallVertexBuffer, wallVertices.size());
        DrawCrosshair();

        DrawFPS();
    });
}

void FpsGame::DrawCrosshair() {
    // put camera back into 2d
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex3f(-0.02f, 0, 0);
    glVertex3f(0.02f, 0, 0);
    glVertex3f(0, -0.033f, 0);
    glVertex3f(0, 0.033f, 0);
    glEnd();
}
