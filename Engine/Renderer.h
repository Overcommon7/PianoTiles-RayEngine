#pragma once
#include "Component.h"
#include "Interfaces.h"
#include "Delegate.h"

namespace RayEngine
{
	struct Bounds;

	class Renderer : public Component, public IDraw
	{
	public:
		void Draw() override;

		int SortingLayer() const { return sortingLayer; }
		Color GetColor() const { return color; }

		void SetSortingLayer(int layer) { sortingLayer = layer; }
		void SetColor(Color color) { this->color = color; }
		Delegate& OnDraw() { return onDraw; }

		static void StaticDraw();
		virtual Bounds Bounds() const = 0;
	protected:
		int sortingLayer;
		Color color;
		Delegate onDraw;

		virtual void InternalDraw() const = 0;
		Renderer(RayEngine::GameObject* gameObject, int sortingLayer, Color color, const string& name);
		Renderer() = default;
		
	private:
		static inline vector<Renderer*> entries = {};
	};
}


