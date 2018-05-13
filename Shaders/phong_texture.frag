const char *phong_texture_frag = R"foo(
#version 430 core

#define LIGHTS_N 1

/** Material */
struct Material_t {
    sampler2D diffuseTexture;
    sampler2D specularTexture;
    vec3 diffuse;
    vec3 specular;
    float roughness;
};
layout( location = 0) uniform Material_t material;

/** Lights */
struct Light {
    vec4 position;
    vec4 diffuse;
    vec4 ambient;
    vec4 specular;
};
layout( location = 5) uniform Light lights[ LIGHTS_N ];

uniform vec3 viewPos;

/** Default: 1 white light at origo */

vec3 saturate( vec3 color ) {
    return clamp( color, 0.0, 1.0f);
}

in vec3 Normal;
in vec2 TexCoord;
in vec4 FragPosition;   /** world space */

out vec4 FragColor;


/** Main */
void main()
{
    vec3 ambient = vec3(0.0);
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);
    vec3 norm = normalize(Normal);

    vec3 viewDir = normalize(viewPos - FragPosition.xyz);
    vec3 diffuseTextureColor = vec3( texture( material.diffuseTexture, TexCoord));
    vec3 specularTextureColor = vec3( texture( material.specularTexture, TexCoord));

    for( int i=0; i < LIGHTS_N; i++ ) {

        ambient += diffuseTextureColor * lights[i].ambient.rgb;
        vec3 lightDir = normalize( (lights[i].position - FragPosition).xyz);
        float diff = max(dot(norm, lightDir), 0.0);
        diffuse += lights[i].diffuse.rgb * diff * diffuseTextureColor;
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.roughness);
        specular += lights[i].specular.rgb * spec * specularTextureColor;
    }

    vec3 result = saturate(ambient + diffuse + specular);
    FragColor =  vec4( result, 1.0f);
}

)foo";
