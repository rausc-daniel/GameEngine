#version 330

uniform sampler2D diffuse;
uniform sampler2D normalMap;

in vec2 uv;
in float brightness;
in float height;

out vec4 color;

void main() {
    vec4 simpleColor = vec4(0.1 + height / 4.0, 0.8, 0.6, 1);
    color = texture(normalMap, uv) * simpleColor * brightness;
}