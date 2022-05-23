
#include "Monster.h"
#include "../Scene/Scene.h"
#include "Bullet.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderCircle.h"


CMonster::CMonster() :
	m_HP(100)
{
	SetTypeID<CMonster>();
}

CMonster::CMonster(const CMonster& Obj) :
	CCharacter(Obj),
	m_Dir(Obj.m_Dir),
	m_FireTime(Obj.m_FireTime),
	m_FireCount(Obj.m_FireCount)
{
}

CMonster::~CMonster()
{
}

bool CMonster::Init()
{
	CGameObject::Init();

	m_MoveSpeed = 300.f;
	m_FireTime = 0.f;
	m_Dir = Vector2(0.f, 1.f);
	m_FireCount = 0;

	SetPos(900.f, 100.f);
	SetSize(100.f, 100.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Monster", TEXT("teemo.bmp"));

	//// 충돌체 생성, 씬 ColliderList에도 추가
	//CColliderBox* Box = AddCollider<CColliderBox>("Body");

	//// 충돌체 크기 설정
	//Box->SetExtent(100.f, 100.f);
	//// 충돌체 프로파일 설정
	//Box->SetCollisionProfile("Monster");

	//// 충돌체와 부딪혔을때 일어날 함수 지정
	//Box->SetCollisionBeginFunction<CMonster>(this, &CMonster::CollisionBegin);
	//Box->SetCollisionEndFunction<CMonster>(this, &CMonster::CollisionEnd);


	// 원 충돌
	CColliderCircle* Circle = AddCollider<CColliderCircle>("Body");

	Circle->SetRadius(50.f);
	Circle->SetCollisionProfile("Monster");

	Circle->SetCollisionBeginFunction<CMonster>(this, &CMonster::CollisionBegin);
	Circle->SetCollisionEndFunction<CMonster>(this, &CMonster::CollisionEnd);

	return true;
}

void CMonster::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	//MoveDir(m_Dir);

	if (m_Pos.y + (1.f - m_Pivot.y) * m_Size.y >= 720.f)
	{
		m_Pos.y = 720.f - (1.f - m_Pivot.y) * m_Size.y;
		m_Dir *= -1;
	}

	else if (m_Pos.y - m_Pivot.y * m_Size.y <= 0.f)
	{
		m_Pos.y = m_Pivot.y * m_Size.y;
		m_Dir *= -1;
	}

	m_FireTime += DeltaTime;

	if (m_FireTime >= 0.5f)
	{
		m_FireTime -= 0.5f;

		++m_FireCount;

		CBullet* Bullet = m_Scene->CreateObject<CBullet>("Bullet");

		CCollider* BulletCol = Bullet->FindCollider("Body");

		BulletCol->SetCollisionProfile("MonsterAttack");

		float	BulletX = m_Pos.x - m_Pivot.x * m_Size.x -
			(1.f - Bullet->GetPivot().x) * Bullet->GetSize().x;

		Bullet->SetPos(BulletX, m_Pos.y);
		Bullet->SetDamage(20.f);

		if (m_FireCount == 3)
		{
			m_FireCount = 0;

			// 플레이어 방향으로 나갈 각도를 구한다.
			float Angle = Bullet->GetPos().Angle(m_Scene->GetPlayer()->GetPos());
			Bullet->SetAngle(Angle);
		}
	}
}

void CMonster::PostUpdate(float DeltaTime)
{
	CCharacter::PostUpdate(DeltaTime);
}

void CMonster::Render(HDC hDC, float DeltaTime)
{
	CCharacter::Render(hDC, DeltaTime);

	//Vector2	RenderLT;

	//RenderLT = m_Pos - m_Pivot * m_Size;

	//Rectangle(hDC, (int)RenderLT.x, (int)RenderLT.y,
//		(int)(RenderLT.x + m_Size.x), (int)(RenderLT.y + m_Size.y));
}

float CMonster::InflicitDamage(float Damage)
{
	Damage = CCharacter::InflicitDamage(Damage);

	m_HP -= (int)Damage;

	if (m_HP <= 0)
	{
		SetActive(false);
	}

	return Damage;
}

void CMonster::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	//MessageBox(nullptr, TEXT("죽어라!!!"), TEXT("^모^"), MB_OK);
}

void CMonster::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	//MessageBox(nullptr, TEXT("관통!!!"), TEXT("^모^"), MB_OK);
}
