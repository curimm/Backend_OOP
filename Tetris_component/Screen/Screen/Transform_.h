#pragma once
#include "Component.h"
#include "Utils.h"

class Transform_ : public Component
{
	Vector2 position;
	Vector2 rotation;
	Vector2 scale;
public:



	Transform_(GameObject* gameObject,
		const Vector2& position = Vector2::zero,
		const Vector2& rotation = Vector2::zero,
		const Vector2& scale = Vector2::ones);

protected:
	void start() {}

	void update() {}

	virtual ~Transform_();
};

