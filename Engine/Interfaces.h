#pragma once

class IUpdate
{
public:
	virtual void Update() = 0;
};

class IDraw
{
public:
	virtual void Draw() = 0;
};

class ILateUpdate
{
public:
	virtual void LateUpdate() = 0;
};

class ILateDraw
{
public:
	virtual void LateDraw() = 0;
};


