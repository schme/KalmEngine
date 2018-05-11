const char *through_vert = R"foo(
#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

struct Material_t {
    vec3 color;
    float roughness;
};
uniform Material_t material = { vec3( 0.2, 0.8, 0.8), 32 };

uniform mat4 modelView;
uniform mat4 projection;

out vec3 Normal;
out vec2 TexCoord;

void main()
{
    gl_Position = projection * modelView * vec4(aPosition, 1.0);
    Normal = aNormal;
    TexCoord = aTexCoord;
}
)foo";
