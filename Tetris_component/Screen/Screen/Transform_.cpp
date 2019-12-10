#include "Transform_.h"



Transform_::Transform_()(GameObject* gameObject,
	const Vector2& position,
	const Vector2& rotation,
	const Vector2& scale)
	: position(position),
	rotation(rotation),
	scale(scale),
	Component(gameObject)
{
}


Transform_::~Transform_()
{
}
