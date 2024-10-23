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

    // ���콺 ���� ��ư�� ������ ��
    virtual void MouseLBtnDown() override;

    // �ش� UI �� ���Ȱ�, �ٽ� UI ������ ��ư�� ������ �� Ŭ������ �����Ѵ�.
    virtual void MouseLBtnClikced() override;

    // �ش� UI �� ������ �ʾ�����, UI ������ ��ư�� ������ ��, Drag Drop �� �� Ȱ��
    virtual void MouseReleased() override;
public:
    GPanel();
    ~GPanel();
};


