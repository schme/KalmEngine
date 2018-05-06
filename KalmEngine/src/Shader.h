/**
 *
 * Shader.h shaderloader
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 03/05/2018
 */
#ifndef SHADER_H_
#define SHADER_H_

#include "glad/glad.h"
#include "Types.h"
#include "kVector.h"

enum ShaderType_t { SHADER_VERTEX, SHADER_FRAGMENT };

struct kShader_t {
    u32 ID;
    void Use() {
        glUseProgram(ID);
    }
    void SetInt( const char *name, s32 value ) const {
        glUniform1i( glGetUniformLocation(ID, name), value);
    }
    void SetFloat( const char *name, f32 value ) const {
        glUniform1f( glGetUniformLocation(ID, name), value);
    };
    void SetVec2( const char *name, vec2 value ) const {
        glUniform2fv( glGetUniformLocation(ID, name), 1, value.Q);
    };
    void SetVec3( const char *name, vec3 value ) const {
        glUniform3fv( glGetUniformLocation(ID, name), 1, value.Q);
    };
    void SetVec4( const char *name, vec4 value ) const {
        glUniform4fv( glGetUniformLocation(ID, name), 1, value.Q);
    };
};


class kShaderLoader {
    static kShader_t shaders[5];

    public:
    kShader_t LoadShaders();
    void LoadShader( kShader_t * shader, const char *vertexCode, const char *fragmentCode );
    private:
    void CheckCompileErrors( u32 ID, const char* type) const ;
};

#include "../../Shaders/through.frag"
#include "../../Shaders/through.vert"

#endif /* end of include guard: SHADER_H_ */
