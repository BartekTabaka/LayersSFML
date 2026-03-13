#include "VoidLayer.h"

VoidLayer::VoidLayer()
{
	m_Name = "VoidLayer";

	m_EventTypesToHandle = {};
}

void VoidLayer::OnEvent(Core::Event& event)
{
}

void VoidLayer::OnUpdate(float ts)
{
}

void VoidLayer::OnRender()
{
}
