#pragma once
class DeBugRenderManager
{
	SINGLE(DeBugRenderManager);
private:
	list<DeBugRenderInfo>	m_DeBugInfo;
	bool					m_Show;

public:
	void AddDeBugInfo(const DeBugRenderInfo& _DeBugInfo) 
	{ 
		if (m_Show == false)
			return;
		m_DeBugInfo.push_back(_DeBugInfo); 
	}
	
	void ShowDeBugRender(bool _Show) { m_Show = _Show; }
	bool GetShow() { return m_Show; }

public:
	void Progress();
	void Render();

};

