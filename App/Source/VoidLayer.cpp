#include "VoidLayer.h"

VoidLayer::VoidLayer()
{
	m_Name = "VoidLayer";

	m_EventTypesToHandle = {};
}

void VoidLayer::onEvent(Core::Event& event)
{
}

void VoidLayer::onUpdate(float ts)
{
}

void VoidLayer::onRender()
{
}
