#include "Projection.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Luna
{
Projection::Projection(ProjectionType type, const Frustum& frustum)
    : Type(type), ProjFrustum(frustum)
{
    UpdateMatrix();
}

void Projection::UpdateMatrix()
{
    switch (Type)
    {
    case ProjectionType::PERSPECTIVE:
	Matrix = glm::perspective(
	    glm::radians(ProjFrustum.P_FOV),
	    ProjFrustum.P_AspectRatio,
	    ProjFrustum.Near,
	    ProjFrustum.Far
	);
	break;

    case ProjectionType::ORTHOGONAL:
	Matrix = glm::ortho(
	    0.0f,
	    ProjFrustum.O_Width,
	    0.0f,
	    ProjFrustum.O_Height,
	    ProjFrustum.Near,
	    ProjFrustum.Far
	);
	break;
    }
}

    void Projection::UpdateFrustum(float frustumWidth, float frustumHeight)
    {
	ProjFrustum.O_Width = frustumWidth;
	ProjFrustum.O_Height = frustumHeight;

	ProjFrustum.P_AspectRatio = frustumWidth / frustumHeight;

	UpdateMatrix();
    }
}
