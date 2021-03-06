#include "PhysicsBodyComponent.h"

#include "../../Managers/PhysicsManager.h"
#include "../../Core/GameObject/GameObject.h"
#include "../../Utils/AllUtils.h"

#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>

namespace Engine
{

	PhysicsBodyComponent::PhysicsBodyComponent(GameObject& obj, PhysicsBodyDef& def)
		: IComponent(obj)
		, m_categoryBits(def.CategoryBits)
		, m_maskBits(def.MaskBits)
		, m_isBullet(def.IsBullet)
		, m_bodyType(def.BodyType)
	{
		b2BodyDef bodyDef;
		bodyDef.type = m_bodyType;
		bodyDef.position = Owner.GetTransform().Position;
		bodyDef.bullet = m_isBullet;
		bodyDef.angle = Owner.GetTransform().Rotation;
		bodyDef.enabled = false; // default always false, activate it in function VirtualOnActivated
		//bodyDef.fixedRotation = true;
		bodyDef.userData.pointer = Owner.ID;
		m_b2Body = PhysicsManager::Get().CreateBody(&bodyDef);
	}

	void PhysicsBodyComponent::OnCreate()
	{
		PhysicsManager::Get().RegisterComponent(this);
	}

	void PhysicsBodyComponent::VirtualOnActivated()
	{
		m_b2Body->SetEnabled(true);
	}

	void PhysicsBodyComponent::VirtualOnDeactivated()
	{
		m_b2Body->SetEnabled(false);
	}

	void PhysicsBodyComponent::ApplyImpulseToCenter(const math::Vec2& impulse)
	{
		m_b2Body->ApplyLinearImpulse(impulse, m_b2Body->GetWorldCenter(), true);
	}

	void PhysicsBodyComponent::ApplyTorque(float torque)
	{
		m_b2Body->ApplyTorque(torque, true);
	}

	PhysicsBodyComponent::~PhysicsBodyComponent()
	{
		PhysicsManager::Get().UnregisterComponent(this);
		PhysicsManager::Get().DeleteBody(m_b2Body);
	}

	void PhysicsBodyComponent::Update(float dt)
	{
		Owner.GetTransform().SetPosition(m_b2Body->GetPosition());
		Owner.GetTransform().SetRotationRad(m_b2Body->GetAngle());
	}
};