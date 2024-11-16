#pragma once
class TaskManager
{
private:
	SINGLE(TaskManager)
private:
	vector<Task> m_Task;
	vector<Task> m_TimeTask;
	vector<CObj*> m_Garbage;
public:
	void Tick();

public:
	void AddTask(const Task& _task) { m_Task.push_back(_task); }

};

