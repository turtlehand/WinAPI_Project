#pragma once
#include "GUI.h"

class GPanel :
    public GUI
{
private:
    Vec2 m_DownPos;

public:
    virtual void Begin() override;

protected:
    virtual void Tick_UI() override;

    //virtual void Render_UI() override;

    // 마우스 왼쪽 버튼이 눌렸을 때
    virtual void MouseLBtnDown() override;

    // 해당 UI 가 눌렸고, 다시 UI 위에서 버튼이 떼졌을 때 클릭으로 판정한다.
    virtual void MouseLBtnClikced() override;

    // 해당 UI 가 눌리진 않았지만, UI 위에서 버튼이 떼졌을 때, Drag Drop 될 때 활용
    virtual void MouseReleased() override;
public:
    GPanel();
    ~GPanel();
};


