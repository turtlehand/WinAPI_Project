#include "pch.h"
#include "Component.h"

Component::Component(COMPONENT_TYPE _Type) :
	m_Owner(nullptr),
	m_Type(_Type)
{
}

Component::~Component()
{
}
