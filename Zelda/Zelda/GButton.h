#pragma once
#include "GUI.h"
class GButton :
    public GUI
{
private:
    //PARAM_0 m_Func;
    // Delegate

    CBase* m_Inst;
    DELEGATE_0 m_MemFunc;
    DELEGATE_1 m_MemFunc_1;
    DELEGATE_2 m_MemFunc_2;

public:
    //void AddCallBack(PARAM_0 _Func) { m_Func = _Func; }
    void AddDelegate(CBase* _Inst, DELEGATE_0 _MemFunc) { m_Inst = _Inst, m_MemFunc = _MemFunc; }
    void AddDelegate(CBase* _Inst, DELEGATE_1 _MemFunc_1) { m_Inst = _Inst, m_MemFunc_1 = _MemFunc_1; }
    void AddDelegate(CBase* _Inst, DELEGATE_2 _MemFunc_2) { m_Inst = _Inst, m_MemFunc_2 = _MemFunc_2; }

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
    GButton();
    ~GButton();
};
