#pragma once

#include <glm/glm.hpp>

namespace Luna
{
enum class ProjectionType
{
    ORTHOGONAL,
    PERSPECTIVE
};

struct Frustum
{
    float Near;
    float Far;

    float O_Width;
    float O_Height;

    float P_FOV;
    float P_AspectRatio;
};

struct Projection
{
    Projection(ProjectionType type, const Frustum& frustum);

    void UpdateMatrix();
    void UpdateFrustum(float viewportWidth, float viewportHeight);

    ProjectionType Type;
    Frustum ProjFrustum;
    glm::mat4 Matrix;
};
}
