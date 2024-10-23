#include "pch.h"
#include "GComponent.h"

GComponent::GComponent(COMPONENT_TYPE _Type) :
	m_Owner(nullptr),
	m_Type(_Type)
{
}

GComponent::~GComponent()
{
}
