/**
 *
 * Shader.h shaderloader
 *
 * TODO(Kasper): ERROR CHECKING
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 03/05/2018 
 */
#ifndef SHADER_H_
#define SHADER_H_

#define SHADER_FOLDER "../../Shaders"

#include "glad/glad.h"
#include "kalm_shared.h"
#include "SystemsLocal.h"

enum ShaderType_t { SHADER_VERTEX, SHADER_FRAGMENT, SHADER_GEOMETRY, SHADER_TESSEVAL, SHADER_TESSCNTRL };

typedef const char ShaderName[50];

struct kShader_t {
    ShaderName names[5];
    u32 ID;
    b32 loaded[5];
};

class kShaderLoader {
    public:
    void LoadShader( kShader_t *shader, const char *filename, ShaderType_t type );
    private:
    void CompileShader( const char *shaderCode, u32 ID );
    void CheckCompileErrors( u32 ID, ShaderType_t type);
    void CheckLinkErrors( u32 ID );
};


#endif /* end of include guard: SHADER_H_ */
