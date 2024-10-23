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
    GUI* m_ParentUI;              // 자신을 소유한 부모UI 를 가리키는 포인터, nullptr, 인 경우 본인이 최상위 부모 UI라는 뜻
    vector<GUI*> m_vecChild;    // 소유하고 있는 자식 UI들 포인터

    bool m_MouseHover;          // UI 위에 마우스가 올라왔는지 체크
    bool m_LBtnDown;            // UI 위에서 마우스 왼쪽 버튼이 눌리고 있는지 체크

    PEN_TYPE m_PenType;
    BRUSH_TYPE m_BrushType;

public:
    bool IsMouseHover() { return m_MouseHover; }
    bool IsLBtnDown() { return m_LBtnDown; }
    Vec2 GetGlobalPos() { 
        if(m_ParentUI)
            return m_ParentUI->GetGlobalPos() + this->GetPos();
        return this->GetPos();
    }
    void AddChildUI(GUI* _ChildUI)
    {
        m_vecChild.push_back(_ChildUI);
        _ChildUI->m_ParentUI = this;
    }

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

    // 마우스 왼쪽 버튼이 눌렸을 때
    virtual void MouseLBtnDown() {}

    // 해당 UI 가 눌렸고, 다시 UI 위에서 버튼이 떼졌을 때 클릭으로 판정한다.
    virtual void MouseLBtnClikced() {}

    // 해당 UI 가 눌리진 않았지만, UI 위에서 버튼이 떼졌을 때, Drag Drop 될 때 활용
    virtual void MouseReleased() {}
public:
    GUI();
    ~GUI();

    friend class GUIManager;
};

