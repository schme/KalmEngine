const char *phong_frag = R"foo(
#version 330 core

#define LIGHTS_N 1

#define LIGHT_COLOR_I 0
#define LIGHT_POSITION_I 1

vec3 saturate( vec3 color ) {
    return clamp( color, 0.0, 1.0f);
}

in vec3 Normal;
in vec2 TexCoord;
in vec4 FragPosition;   /** world space */

out vec4 FragColor;

/** Lights */
struct Light {
    vec4 color;
    vec4 position;
};
uniform Light lights[ LIGHTS_N ];

/** Default: 1 white light at origo */

/** Material */
struct Material_t {
    vec3 color;
    float roughness;
};
uniform Material_t material = { vec3( 1.0, 1.0, 0.0), 0.0 };

uniform vec3 viewPos;


/** Main */
void main()
{
    float ambS = 0.1;
    float specularS = 0.5;
    vec3 ambient = vec3(0.0);
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);
    vec3 norm = normalize(Normal);

    for( int i=0; i < LIGHTS_N; i++ ) {
        ambient = ambS * lights[i].color.rgb;
        vec3 lightDir = normalize( (lights[i].position - FragPosition).xyz);
        float diff = max(dot(norm, lightDir), 0.0);
        diffuse = diff * lights[i].color.xyz;
        vec3 viewDir = normalize(viewPos - FragPosition.xyz);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.roughness);
        specular = specularS * spec * lights[i].color.rgb;
    }

    vec3 result = saturate( material.color * (ambient + diffuse + specular));
    FragColor =  vec4( result, 1.0f);
}

)foo";
