#version 450 core
// Taking in position
layout (location = 0) in vec4 position;

uniform mat4 translation;
uniform mat4 scale;
uniform mat4 ori;
uniform mat4 camera;
uniform mat4 perspective;


out vec4 fragColor;

void main() {
   gl_Position =  (perspective * camera * ori * scale * position) / position.w;
   fragColor = vec4(  1.0f, 1.0f - position.x / 10.0f, 1.0f - position.z / 10.0f, 1.0f);
}
