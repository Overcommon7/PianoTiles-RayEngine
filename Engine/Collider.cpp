#include "pch.h"
#include "Collider.h"

#include "Transform.h"
#include "Bounds.h"

RayEngine::Bounds RayEngine::Collider::Bounds() const
{
	return RayEngine::Bounds(transform->Position(), size, transform->Scale());
}
