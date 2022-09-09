#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <glm/vec3.hpp>

// Every piece of data contained in a vertex (position, color, normal...).
struct Vertex
{
    Vertex();
    Vertex(float x, float y, float z);
    glm::vec3 pos;
};

struct Mesh
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
};

// Create a mesh from input Bitmap, centered at the origin on ZX plane.
// Input Mesh object must be empty (implemeted to avoid copying the object on function return).
void createBitmapMesh(Mesh& mesh, unsigned char* bitmap, int width, int height);

#endif // MESH_HPP