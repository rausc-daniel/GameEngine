#version 330

layout(location = 0) in vec4 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec3 vertexTangent;
layout(location = 3) in vec2 texCoord;

uniform mat4 worldViewProjection;
uniform float time;
uniform vec3 lightDirection;

out vec2 uv;
out float brightness;
out float height;

void main(){
    vec4 pos = vertexPosition_modelspace;
    brightness = 0.2f + 0.8f * clamp(dot(lightDirection, vertexNormal), 0, 1);
    height = pos.z;
    uv = texCoord;
    gl_Position = worldViewProjection * pos;
}