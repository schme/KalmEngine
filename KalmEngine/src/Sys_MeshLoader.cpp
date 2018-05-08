/**
 *
 * Sys_MeshLoader.cpp
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 07/05/2018
 */

#define MESH_FOLDER "Assets/Models/"

#include <fstream>
#include <iostream>

#include "../../tinyply/tinyply.h"

#include "kcl.hpp"
#include "Sys_MeshLoader.h"
#include "Sys_Shared.h"

/**
 * TODO(Kasper): Check if we're trying to load a PLY file and error if not
 */
kMesh_t * MeshLoader::LoadMesh( const char *filename) const {
    kMesh_t *result = this->LoadPLY( filename);
    return result;
}


/**
 * Adapted from tinyplys example.cpp
 */
kMesh_t * MeshLoader::LoadPLY( const char *filename) const {

    kMesh_t *result = nullptr;

    try {
        std::string fname(filename);
        std::ifstream ss(filename, std::ios::binary);

        if( ss.fail()) {
            throw std::runtime_error("failed to open " + fname);
        }

        tinyply::PlyFile file;
        file.parse_header(ss);

        std::cout << "\n\nMeshLoader::LoadPLY:\n-------------------------\n";

        for (auto e : file.get_elements())
        {
            std::cout << "element - " << e.name << " (" << e.size << ")" << std::endl;
            for (auto p : e.properties)
            {
                std::cout << "\tproperty - " << p.name << " (" << tinyply::PropertyTable[p.propertyType].str << ")" << std::endl;
            }
        }

        std::shared_ptr<tinyply::PlyData> vertices, normals, colors, faces, texcoords;

        // The header information can be used to programmatically extract properties on elements
        // known to exist in the file header prior to reading the data. For brevity of this sample, properties
        // like vertex position are hard-coded:
        try { vertices = file.request_properties_from_element("vertex", { "x", "y", "z" }); }
        catch (const std::exception & e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

        try { normals = file.request_properties_from_element("vertex", { "nx", "ny", "nz" }); }
        catch (const std::exception & e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

        try { colors = file.request_properties_from_element("vertex", { "red", "green", "blue", "alpha" }); }
        catch (const std::exception & e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

        try { faces = file.request_properties_from_element("face", { "vertex_indices" }); }
        catch (const std::exception & e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

        try { texcoords = file.request_properties_from_element("face", { "texcoord" }); }
        catch (const std::exception & e) { std::cerr << "tinyply exception: " << e.what() << std::endl; }

        /* readtime */
        f64 before = g_Common->GetTime() * 1000.0;
        file.read(ss);
        f64 after = g_Common->GetTime() * 1000.0;

        // Good place to put a breakpoint!
        std::cout << "Parsing took " << after - before << " ms: " << std::endl;
        if (vertices) std::cout << "\tRead " << vertices->count << " total vertices "<< std::endl;
        if (normals) std::cout << "\tRead " << normals->count << " total vertex normals " << std::endl;
        if (colors) std::cout << "\tRead " << colors->count << " total vertex colors "<< std::endl;
        if (faces) std::cout << "\tRead " << faces->count << " total faces " << std::endl;
        if (texcoords) std::cout << "\tRead " << texcoords->count << " total texcoords " << std::endl;

        /** Fit in a kMesh_t */
        {
            /** we don't handle meshes without indices or vertices, so just bail out screaming for now*/
            ASSERT( faces && vertices);

            result = (kMesh_t*)g_Memory->Alloc( sizeof( kMesh_t));
            ASSERT( result );

            u32 vert_n = 0; size_t vert_bytes = 0;
            u32 norm_n = 0; size_t norm_bytes = 0;
            u32 texc_n = 0; size_t texc_bytes = 0;
            u32 indx_n = 0; size_t indx_bytes = 0;

            b32 hasVertices = 0;
            b32 hasNormals = 0;
            b32 hasTexcoords = 0;

            struct float3 { f32 x,y,z; };
            struct float2 { f32 x,y; };

            float3 *norm_buffer = nullptr;
            float3 *vert_buffer = nullptr;
            float2 *texc_buffer = nullptr;

            if( vertices ) {
                hasVertices = 1;
                vert_n = (u32)vertices->count;
                vert_bytes = vertices->buffer.size_bytes();
                vert_buffer = (float3*)vertices->buffer.get();
            }
            if( normals ) {
                hasNormals = 1;
                norm_n = (u32)normals->count;
                norm_bytes = normals->buffer.size_bytes();
                norm_buffer = (float3*)normals->buffer.get();
            }
            if( faces ) {
                indx_n = (u32)faces->count * 3;
                indx_bytes = faces->buffer.size_bytes();
            }
            if( texcoords ) {
                hasTexcoords = 1;
                texc_n = (u32)texcoords->count;
                texc_bytes = texcoords->buffer.size_bytes();
                texc_buffer = (float2*)texcoords->buffer.get();
            }

            result->vertices_n = vert_n + norm_n + texc_n;
            result->indices_n = indx_n;

            result->vertices = (f32*)g_Memory->Alloc( u32(vert_bytes + norm_bytes + texc_bytes) );
            result->indices = (u32*)g_Memory->Alloc( u32(indx_bytes) );

            u32 bufferSize = (3*hasVertices + 3*hasNormals + 2*hasTexcoords) * sizeof(f32);

            MemorySystem::Marker stackMark = g_Memory->GetMarker();
            f32 *buffer = (f32*)g_Memory->Alloc( bufferSize );


            for( u32 i=0; i < vert_n; ++i) {
                *(float3*)buffer = *(vert_buffer + i);
                if( hasNormals) {
                    *(float3*)(buffer+3) = *(norm_buffer + i);
                }
                if( hasTexcoords) {
                    *(float2*)(buffer+ 3*hasNormals + 3) = *(texc_buffer + i);
                }
                std::memcpy( (result->vertices) + (bufferSize / sizeof(f32)) * i,
                                buffer, bufferSize );
            }

            g_Memory->Free( stackMark);
            std::memcpy( result->indices, faces->buffer.get(), indx_bytes);

            result->hasVertices = hasVertices;
            result->hasNormals = hasNormals;
            result->hasTexcoords = hasTexcoords;
        }
        std::cout << "\nENDOF MeshLoader::LoadPLY\n-------------------------\n";

    }
    catch (const std::exception & e)
    {
        std::cerr << "Caught tinyply exception: " << e.what() << std::endl;
    }

    return result;
}
