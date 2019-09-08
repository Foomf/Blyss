#version 330 core
layout (location = 0) in vec2 aPos;

uniform mat3 model;
uniform mat3 view;
uniform mat4 ortho;

void main()
{
    vec3 world_pos = view * model * vec3(aPos, 1);
    gl_Position = ortho * vec4(world_pos.x, world_pos.y, 0.5, 1.0);
}