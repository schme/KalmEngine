/**
 *
 * Shader.cpp shaderloader
 *
 * Created: 03/05/2018
 */

#include "Shader.h"
#include "CommonIncludes.h"


void kShaderLoader::LoadShader( Shader * shader, const char *vertexCode, const char *fragmentCode ) {
    u32 vertex, fragment;

    /** vertex */
    vertex = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);
    CheckCompileErrors( vertex, "VERTEX");

    /** fragment */
    fragment = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fragment, 1, &fragmentCode, NULL);
    glCompileShader( fragment);
    CheckCompileErrors( fragment, "FRAGMENT");

    /** other shaders */

    /** shader program */
    shader->ID = glCreateProgram();
    glAttachShader( shader->ID, vertex);
    glAttachShader( shader->ID, fragment);
    glLinkProgram( shader->ID );
    CheckCompileErrors( shader->ID, "PROGRAM");

    glDeleteShader( vertex );
    glDeleteShader( fragment );

}

void kShaderLoader::CheckCompileErrors(GLuint shader, const char* type) const {
    GLint success;
    GLchar infoLog[1024];
    if( strcmp("PROGRAM", type) != 0) {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            printf( "Failed shader compilation: %u\t%s\n%s\n", shader, type, infoLog);
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            printf( "Failed shader linking: %u\t%s\n%s\n", shader, type, infoLog);
        }
    }
}


Shader kShaderLoader::GetShader( const u32 program_id ) const {
    ASSERT( program_id < SHADER_PROGRAMS_N );
    return programs[ program_id ];
}
