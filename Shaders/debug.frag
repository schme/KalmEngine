const char *debug_frag = R"foo(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4( 0.8f, 0.0f, 0.8f, 1.0f);
}

)foo";
