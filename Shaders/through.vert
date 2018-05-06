const char *through_vert = R"foo(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aTexCoord;

out vec2 TexCoord;

uniform mat4 modelView;
uniform mat4 perspective;

void main()
{
    gl_Position = perspective * modelView * vec4(aPos, 1.0);
    TexCoord = vec2( aTexCoord.xy );
}
)foo";
