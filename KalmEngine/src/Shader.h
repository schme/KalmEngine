/**
 *
 * Shader.h shaderloader
 *
 * Adapted from Joey de Vries' (@JoeyDeVriez in twitter)
 * Shader class from http://learnopengl.com
 *
 * Created: 03/05/2018
 */
#ifndef SHADER_H_
#define SHADER_H_

#include "../include/glad/glad.h"
#include "Types.h"
#include "kVector.h"

#define SHADER_PROGRAMS_N 1

class Shader {
    public:
    u32 ID;
    void Use() {
        glUseProgram(ID);
    }
    void SetInt( const char *name, s32 value ) const {
        glUniform1i( glGetUniformLocation(this->ID, name), value);
    }
    void SetFloat( const char *name, f32 value ) const {
        glUniform1f( glGetUniformLocation(this->ID, name), value);
    };
    void SetVec2( const char *name, vec2 value ) const {
        glUniform2fv( glGetUniformLocation(this->ID, name), 1, value.Q);
    };
    void SetVec3( const char *name, vec3 value ) const {
        glUniform3fv( glGetUniformLocation(this->ID, name), 1, value.Q);
    };
    void SetVec4( const char *name, vec4 value ) const {
        glUniform4fv( glGetUniformLocation(this->ID, name), 1, value.Q);
    };
    void SetMat4( const char *name, mat4 value ) const {
        glUniformMatrix4fv( glGetUniformLocation(this->ID, name), 1, GL_FALSE, (f32*)value.A);
    };
};


class kShaderLoader {
    Shader programs[ SHADER_PROGRAMS_N ];
    public:
    void LoadShader( Shader * shader, const char *vertexCode, const char *fragmentCode );
    Shader GetShader( const u32 program_id ) const;
    private:
    void CheckCompileErrors( u32 ID, const char* type) const ;
};

#include "../../Shaders/through.frag"
#include "../../Shaders/through.vert"

#endif /* end of include guard: SHADER_H_ */
