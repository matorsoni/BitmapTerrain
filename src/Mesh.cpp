#include "Mesh.hpp"

using glm::vec2;
using glm::vec3;

Vertex::Vertex():
    pos(vec3(0.0f)), tex(vec2(0.0f))
{
}

Vertex::Vertex(float x, float y, float z):
    pos(vec3(x, y, z)), tex(vec2(0.0f))
{
}

Vertex::Vertex(float x, float y, float z, float u, float v):
    pos(vec3(x, y, z)), tex(vec2(u, v))
{
}

void createBitmapMesh(Mesh& mesh,
                      unsigned char* bitmap,
                      int width,
                      int height,
                      float scale)
{
    assert(width >= 1);
    assert(height >= 1);
    assert(mesh.vertices.empty());
    assert(mesh.indices.empty());

    // Spatial displacement.
    constexpr float dx = 0.2f;
    constexpr float dz = 0.2f;
    // Texture space displacement.
    const float du = 1.0f / width;
    const float dv = 1.0f / height;

    // Add vertices to the list. Each vertex represents a pixel on the grid centered at the origin.
    const float x0 = (height - 1) * dx / 2.0f;
    const float z0 = -(width - 1) * dz / 2.0f;
    float x = x0;
    // Texture coords U and V.
    float v = 0.0f;
    for (int i = 0; i < height; ++i) {
        float z = z0;
        float u = 0.0f;
        for (int j = 0; j < width; ++j) {
            float y = scale * static_cast<float>(*bitmap++) / 255.f;
            mesh.vertices.emplace_back(x, y, z, u, v);
            z += dz;
            u += du;
        }
        x -= dx;
        v += dv;
    }

    // Triangulate patch.
    // For each vertex position, append the corresponding right-hand oriented triangles.
    for (int i = 0; i < height - 1; ++i) {
        for (int j = 0; j < width - 1; ++j) {
            auto current     = static_cast<unsigned int>(i*width + j);
            auto right       = current + 1;
            auto below       = current + width;
            auto right_below = current + width + 1;

            // First triangle.
            mesh.indices.emplace_back(below);
            mesh.indices.emplace_back(right_below);
            mesh.indices.emplace_back(current);
            // Second triangle.
            mesh.indices.emplace_back(right_below);
            mesh.indices.emplace_back(right);
            mesh.indices.emplace_back(current);
        }
    }
}
