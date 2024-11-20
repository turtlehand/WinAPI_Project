#include "pch.h"
#include "GComponent.h"
#include "TaskManager.h"

GComponent::GComponent(COMPONENT_TYPE _Type) :
	m_Owner(nullptr),
	m_Type(_Type),
	m_Enabled(true),
	m_PrevEnabled(true)
{
}

GComponent::~GComponent()
{
}

void GComponent::SetEnabled(bool _Enabled)
{
	Task task = { 0.f, TASK_TYPE::ENABLED_COMPONENT, (DWORD_PTR)this, (DWORD_PTR)_Enabled };
	TaskManager::GetInst()->AddTask(task);
}
