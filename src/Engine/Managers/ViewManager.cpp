#include "ViewManager.h"

#include "../Application.h"
#include "../Core/GameObject/GameObject.h"
#include "../Debug/Logger.h"

namespace Engine
{
	ViewManager::ViewManager()
		: m_shapes()
		, m_texts()
		, m_viewStrategy()
	{
	}

	ViewManager& ViewManager::Get()
	{
		return Application::Instance().GetViewManager();
	}

	void ViewManager::VirtualOnDestroy()
	{
		m_viewStrategy = nullptr;
	}

	void ViewManager::SetViewStrategy(view::IViewStrategy* viewStrategy)
	{
		m_viewStrategy.reset(viewStrategy);
	}

	void ViewManager::PollEvents()
	{
		m_viewStrategy->PollEvents();
	}

	sf::Vector2f ViewManager::GetMousePosition()
	{
		return m_viewStrategy->GetMousePosition();
	}

	sf::Vector2f ViewManager::coordsToPixels(b2Vec2 coords)
	{
		return { coords.x * PIXELS_PER_METER, -coords.y * PIXELS_PER_METER };
	}

	b2Vec2 ViewManager::pixelsToCoords(sf::Vector2f pixels)
	{
		return { pixels.x / PIXELS_PER_METER, -pixels.y / PIXELS_PER_METER };
	}

	float ViewManager::coordToPixel(float coord)
	{
		return coord * PIXELS_PER_METER;
	}

	float ViewManager::pixelToCoord(float pixel)
	{
		return pixel / PIXELS_PER_METER;
	}

	// ==================================================================

	void ViewManager::RegisterComponent(IRenderableShapeComponent* component)
	{
		m_shapes.insert({ component->c_Layer, component });
	}

	void ViewManager::RegisterComponent(IRenderableTextComponent* component)
	{
		m_texts.emplace_back(component);
	}

	void ViewManager::RegisterComponent(IDebuggable* component)
	{
		m_debugs.emplace_back(component);
	}

	void ViewManager::RegisterComponent(CameraComponent* component)
	{
		m_cameras.emplace_back(component);
	}

	// ==================================================================

	void ViewManager::UnregisterComponent(IRenderableShapeComponent* component)
	{
		for (auto iter = m_shapes.begin(); iter != m_shapes.end(); /* */ )
		{
			auto erase_iter = iter++;

			if (erase_iter->second == component)
				m_shapes.erase(erase_iter);
		}
		
	}

	void ViewManager::UnregisterComponent(IRenderableTextComponent* component)
	{
		m_texts.erase(std::remove(m_texts.begin(), m_texts.end(), component), m_texts.end());
	}

	void ViewManager::UnregisterComponent(IDebuggable* component)
	{
		m_debugs.erase(std::remove(m_debugs.begin(), m_debugs.end(), component), m_debugs.end());
	}

	void ViewManager::UnregisterComponent(CameraComponent* component)
	{
		m_cameras.erase(std::remove(m_cameras.begin(), m_cameras.end(), component), m_cameras.end());
	}

	// ==================================================================

	void ViewManager::Update(float dt)
	{
		if (InputManager::Get().GetAction(InputManager::Action::ShowDebugDraw).PressedThisFrame)
			m_shouldDrawDebug = !m_shouldDrawDebug;

		m_viewStrategy->PreRender();

		for (auto c : m_cameras)
			if (c->Owner.ShouldUpdate())
				c->Update(dt);

		for (auto r : m_shapes)
		{
			auto component = r.second;
			if (component->Owner.ShouldUpdate())
			{
				component->Update(dt);
				m_viewStrategy->RenderRenderable(component->GetRenderable());
			}
		}

		for (auto t : m_texts)
			if (t->Owner.ShouldUpdate())
				m_viewStrategy->Render(t->GetRenderableText());

		// debug draws for registered components
		if (m_shouldDrawDebug)
		{
			for (auto d : m_debugs)
				d->Debug(m_viewStrategy.get());
		}

		m_viewStrategy->PostRender();
	}
};