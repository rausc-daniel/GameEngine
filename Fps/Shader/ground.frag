#version 330

uniform sampler2D diffuse;
uniform sampler2D normalMap;
uniform float time;

in vec3 tangentLightDirection;
in vec2 uv;

out vec4 color;

void main() {
    vec3 normal = texture(normalMap, uv).xyz * 2 - 1;
    float brightness = 0.2f + 0.8f * clamp(dot(normal, tangentLightDirection), 0, 1);
    color = texture(diffuse, uv) * brightness;
}