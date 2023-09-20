#include "pch.h"
#include "Renderer.h"

void RayEngine::Renderer::Draw()
{
	entries.push_back(this);
}

void RayEngine::Renderer::StaticDraw()
{
	std::sort(entries.begin(), entries.end(), [](Renderer const* a, Renderer const* b) {
		return a->SortingLayer() < b->SortingLayer();
		});

	for (auto entry : entries)
	{
		entry->InternalDraw();
		entry->onDraw.Invoke();
	}
		
	entries.clear();
}

RayEngine::Renderer::Renderer(RayEngine::GameObject* gameObject, int sortingLayer, Color color, const string& name)
	: Component(gameObject, name), sortingLayer(sortingLayer), color(color)
{
    
}
