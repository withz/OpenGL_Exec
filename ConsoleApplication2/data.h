#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

extern const float trangle_vertices[];
extern const float small_box_vertices[];
extern const float small_box_vertices_normal[];
extern const glm::vec3 cubePositions[];
extern const float trangle_vertices_color[];
extern const float trangle_vertices_color_texture[];
extern const float texCoords[];
extern const float square_vertices[];
extern const int square_indices[];
extern const float box_vertices_norm_tex[];
extern const char* vertex_shader_code;
extern const char* fragment_shader_code;

extern const int small_box_vertices_normal_size;
extern const int square_vertices_size;
extern const int box_vertices_norm_tex_size;


