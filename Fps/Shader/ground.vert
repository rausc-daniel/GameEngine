#version 330

layout(location = 0) in vec4 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec3 vertexTangent;
layout(location = 3) in vec2 texCoord;

uniform mat4 worldViewProjection;
uniform float time;
uniform vec3 lightDirection;

out vec3 tangentLightDirection;
out vec2 uv;

void main() {
    vec4 pos = vertexPosition_modelspace;
    uv = texCoord;
    mat3 TBN = transpose(mat3(vertexTangent, cross(vertexNormal, vertexTangent), vertexNormal));
    tangentLightDirection = TBN * lightDirection;
    gl_Position = worldViewProjection * pos;
}