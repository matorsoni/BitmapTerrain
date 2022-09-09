#include "Mesh.hpp"

using glm::vec3;

Vertex::Vertex():
    pos(vec3(0.0f))
{
}

Vertex::Vertex(float x, float y, float z):
    pos(vec3(x, y, z))
{
}

void createBitmapMesh(Mesh& mesh, unsigned char* bitmap, int width, int height)
{
    assert(width >= 1);
    assert(height >= 1);
    assert(mesh.vertices.empty());
    assert(mesh.indices.empty());

    constexpr float dx = 1.0f;
    constexpr float dz = 1.0f;

    // Add vertices to the list. Each vertex represents a pixel on the grid.
    const float x0 = (height - 1) * dx / 2.0f;
    const float z0 = -(width - 1) * dz / 2.0f;
    float x = x0;
    for (int j = 0; j < height; ++j) {
        float z = z0;
        for (int i = 0; i < width; ++i) {
            float y = *bitmap++ / 255.f;
            mesh.vertices.emplace_back(x, y, z);
            z += dz;
        }
        x -= dx;
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
