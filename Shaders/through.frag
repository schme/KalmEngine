const char *through_frag = R"foo(
#version 330 core

out vec4 FragColor;

struct Material_t {
    vec3 color;
    float roughness;
};
uniform Material_t material = { vec3( 1.0, 0.0, 1.0), 32 };

in vec3 Normal;
in vec2 TexCoord;

void main()
{
    FragColor =  vec4( material.color, 1.0f);
}

)foo";
