#pragma once
#include "CObj.h"

typedef void (*PARAM_0)(void);
typedef void (*PARAM_1)(DWORD_PTR);

typedef void (CBase::* DELEGATE_0)(void);
typedef void (CBase::* DELEGATE_1)(DWORD_PTR);
typedef void (CBase::* DELEGATE_2)(DWORD_PTR, DWORD_PTR);



class GUI :
    public CObj
{
private:
    bool m_MouseHover;              // UI ���� ���콺�� �ö�Դ��� üũ
    bool m_LBtnDown;                // UI ������ ���콺 ���� ��ư�� ������ �ִ��� üũ

    PEN_TYPE m_PenType;
    BRUSH_TYPE m_BrushType;

public:
    bool IsMouseHover() { return m_MouseHover; }
    bool IsLBtnDown() { return m_LBtnDown; }

    void AddChildUI(GUI* _ChildUI)
    {
        m_vecChild.push_back(_ChildUI);
        _ChildUI->m_Parent = this;
    }

    // UI������ ���� UI�� �ڽ����� �߰��� �� �ְ� �����Ѵ�.
    void SetParent(CObj* _Parent) = delete;
    void AddChild(CObj* _Child) = delete;

    void SetPenType(PEN_TYPE _Type) { m_PenType = _Type; }
    void SetBrushType(BRUSH_TYPE _Type) { m_BrushType = _Type; }

public:
    virtual void Begin() override;
    virtual void Tick() final;
    virtual void Render() final;

private:
    void MouseHoverCheck();

protected:

    virtual void Tick_UI() = 0;

    virtual void Render_UI();

    // ���콺 ���� ��ư�� ������ ��
    virtual void MouseLBtnDown() {}

    // �ش� UI �� ���Ȱ�, �ٽ� UI ������ ��ư�� ������ �� Ŭ������ �����Ѵ�.
    virtual void MouseLBtnClikced() {}

    // �ش� UI �� ������ �ʾ�����, UI ������ ��ư�� ������ ��, Drag Drop �� �� Ȱ��
    virtual void MouseReleased() {}
public:
    GUI();
    ~GUI();

    friend class GUIManager;
};

