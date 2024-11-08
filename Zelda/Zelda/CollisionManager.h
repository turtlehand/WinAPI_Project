#pragma once

#include "GCollider.h"

class GRigidBody;
union COLLISION_ID
{
	struct
	{
		UINT Left;
		UINT Right;
	};

	ULONGLONG ID;
};

class CollisionManager
{
	SINGLE(CollisionManager);
private:
	UINT m_Matrix[(UINT)LAYER_TYPE::END];
	map<ULONGLONG, bool> m_ColInfo;
public:
	void CollisionCheck(LAYER_TYPE _Left, LAYER_TYPE _Right);
	void CollisionCheckClear() { memset(m_Matrix, 0, sizeof(UINT) * (UINT)LAYER_TYPE::END); m_ColInfo.clear(); }

private:
	void CollisionBtwLayer(LAYER_TYPE _Left, LAYER_TYPE _Right);
	void CollisionBtwCollider(GCollider* _LeftCol, GCollider* _RightCol);

	bool IsCollision(GCollider* _LeftCol, GCollider* _RightCol);

	bool IsCollision_BoxBtwBox(GCollider* _LeftCol, GCollider* _RightCol);
	//bool IsCollision_BoxBtwCircle(GCollider* _LeftCol, GCollider* _RightCol);
	//bool IsCollision_BoxBtwEdge(GCollider* _LeftCol, GCollider* _RightCol);

	//bool IsCollision_CircleBtwCircle(GCollider* _LeftCol, GCollider* _RightCol);
	//bool IsCollision_CircleBtwEdge(GCollider* _LeftCol, GCollider* _RightCol);
	
	//bool IsCollision_EdgeBtwEdge(GCollider* _LeftCol, GCollider* _RightCol);

	void Collision(GRigidBody* _LeftRigid, GRigidBody* _RightRigid);

public:
	void Tick();
};

