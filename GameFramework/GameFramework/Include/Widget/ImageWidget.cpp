
#include "ImageWidget.h"
#include "../Resource/Texture/Texture.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "WidgetWindow.h"

CImageWidget::CImageWidget()
{
}

CImageWidget::CImageWidget(const CImageWidget& widget) :
	CWidget(widget)
{
}

CImageWidget::~CImageWidget()
{
}

void CImageWidget::SetTexture(const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, FileName, PathName);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

void CImageWidget::SetTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, FullPath);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

#ifdef UNICODE


void CImageWidget::SetTexture(const std::string& Name, const std::vector<std::wstring>& vecFileName, const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, vecFileName, PathName);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

void CImageWidget::SetTextureFullPath(const std::string& Name, const std::vector<std::wstring>& vecFullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, vecFullPath);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

#else

void CImageWidget::SetTexture(const std::string& Name, const std::vector<std::string>& vecFileName, const std::string& PathName)
{
	m_Scene->GetSceneResource()->LoadTexture(Name, vecFileName, PathName);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

void CImageWidget::SetTextureFullPath(const std::string& Name, const std::vector<std::string>& vecFullPath)
{
	m_Scene->GetSceneResource()->LoadTextureFullPath(Name, vecFullPath);
	m_Texture = m_Scene->GetSceneResource()->FindTexture(Name);
}

#endif // UNICODE

bool CImageWidget::Init()
{
	return true;
}

void CImageWidget::Update(float DeltaTime)
{
}

void CImageWidget::PostUpdate(float DeltaTime)
{
}

void CImageWidget::Render(HDC hDC, float DeltaTime)
{
	// 위젯의 위치는 위젯윈도우 위치를 기준으로 + 된다.
	Vector2	RenderPos = m_Pos + m_Owner->GetPos();

	// 텍스쳐가 있을경우
	if (m_Texture)
	{
		// 텍스쳐타입이 스프라이트 일경우
		if (m_Texture->GetTextureType() == ETexture_Type::Sprite)
		{
			if (m_Texture->GetEnableColorKey())
			{
				TransparentBlt(hDC, (int)RenderPos.x, (int)RenderPos.y,
					(int)m_Size.x, (int)m_Size.y,
					m_Texture->GetDC(),
					0, 0, (int)m_Size.x, (int)m_Size.y,
					m_Texture->GetColorKey());
			}

			else
			{
				BitBlt(hDC, (int)RenderPos.x, (int)RenderPos.y,
					(int)m_Size.x, (int)m_Size.y,
					m_Texture->GetDC(),
					0, 0, SRCCOPY);
			}
		}

		else
		{
		}
	}

	else
	{
		Rectangle(hDC, (int)RenderPos.x, (int)RenderPos.y,
			(int)(RenderPos.x + m_Size.x), (int)(RenderPos.y + m_Size.y));
	}
}

void CImageWidget::Render(HDC hDC, const Vector2& Pos, float DeltaTime)
{
}
