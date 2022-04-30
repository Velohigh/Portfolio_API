#include "GameManager.h"
// IconID를 사용하기 위해서 포함시킨다.
#include "resource.h"

DEFINITION_SINGLE(CGameManager)
bool CGameManager::m_Loop = true;


CGameManager::CGameManager()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(100); //Leak남았을때 찾기 위한 함수
}

CGameManager::~CGameManager()
{


}

bool CGameManager::Init(HINSTANCE hInst)
{
	m_hInst = hInst;

	// 윈도우클래스 구조체를 만들어주고 등록한다.
	Register();

	// 윈도우 창을 생성하고 보여준다.
	Create();

	return true;
}

int CGameManager::Run()
{
    // 운영체제가 만들어준 메세지를 얻어오기 위한 구조체이다.
    MSG msg;

    // GetMessage : 메세지 큐에서 메세지를 꺼내오는 함수이다.
    // 단, 메세지 큐가 비어있을 경우 메세지가 들어올때까지 이 함수를 빠져나올 수 없다.
    // 이렇게 멈춰서 대기하고 있는 것을 블로킹 모드 라고 한다.
    // 큐가 비어서 멈춰있는 시간을 윈도우의 데드타임이라고 부른다.
    while (m_Loop)
    {
        // PeekMessage : 이 함수도 메세지 큐에서 메세지를 꺼내오는
        // 함수이다. 단, 이 함수는 메세지 큐가 비어있을 경우 false
        // 를 반환하며 바로 빠져나오게 된다.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            // 메세지큐에서 꺼내온 메세지를 TranslateMessage 함수로 넘겨주면 문자 키인지 
            // F1, 방향키 같은 키인지를 판단해준다.
            // 이러한 키들은 WM_KEYDOWN으로 메세지가 인식이 되고
            // 문자 키는 WM_CHAR로 인식이 된다.
            // 키를 누르면 문자키의 경우 WM_CHAR도 만들어져야하기 때문에 WM_KEYDOWN
            // 이 일어나면 문자키의 경우 WM_CHAR메세지를 추가로 만들어서 메세지 큐에
            // 넣어준다.
            TranslateMessage(&msg);

            // DispatchMessage 함수는 메세지큐에서 꺼내온 메세지를 메세지 처리 함수에
            // 보내준다. WndProc로 보내주는 것이다.
            DispatchMessage(&msg);
        }

        // 메세지 큐가 비어있을 경우 동작된다. 즉, 윈도우의 데드타임시
        // 이 else 구문이 동작되기 때문에 여기에 실제 게임로직을
        // 작성하면 된다.
        else
        {
            Logic();
        }
    }

    return (int)msg.wParam;
}

void CGameManager::Logic()
{
    Input(0.f);
    Update(0.f);
    Collision(0.f);
    Render(0.f);
}

void CGameManager::Input(float DeltaTime)
{
}

void CGameManager::Update(float DeltaTime)
{
}

void CGameManager::Collision(float DeltaTime)
{
}

void CGameManager::Render(float DeltaTime)
{
}

void CGameManager::Register()
{
    // 레지스터에 등록할 윈도우 클래스 구조체를 만들어준다.
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;

    // 메세지큐에서 꺼내온 메세지를 인자로 전달하며 호출할 함수의 함수 주소를
    // 등록한다.
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;

    // 윈도우 인스턴스를 등록한다.
    wcex.hInstance = m_hInst;

    // 실행파일에 사용할 아이콘을 등록한다.
    wcex.hIcon = LoadIcon(m_hInst, MAKEINTRESOURCE(IDI_ICON1));

    // 마우스 커서 모양을 결정한다.
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    // 메뉴를 사용할지 말지를 결정한다.
    wcex.lpszMenuName = nullptr;// MAKEINTRESOURCEW(IDC_MY220428);

    // 등록할 클래스의 이름을 유니코드 문자열로 만들어서 지정한다.
    // TEXT 매크로는 프로젝트 설정이 유니코드로 되어있을 경우 유니코드 문자열로 만들어지고
    // 멀티바이트로 되어있을 경우 멀티바이트 문자열로 만들어지게 된다.
    wcex.lpszClassName = TEXT("GameFramework");

    // 윈도우창 좌상단에 표시할 작은 아이콘을 등록한다.
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    RegisterClassExW(&wcex);
}

bool CGameManager::Create()
{
    // 윈도우 창을 생성한다.
    // 1번 인자는 윈도우 클래스에 등록한 이름이다.
    // 2번 인자는 타이틀바에 표시할 이름이다.
    // 3번인자는 이 윈도우 창이 어떻게 생성될지를 지정하는 옵션이다.
    // 4, 5번 인자는 이 윈도우 창이 생성될 화면에서의 위치를 지정한다.
    // 픽셀로 지정한다. 예를 들어 1920, 1080 해상도라면 거기에서 원하는 값을 넣어주면
    // 해당 위치에 나오게 된다.
    // 4번은 가로좌표, 5번은 세로좌표로 사용이 된다.
    // 6번, 7번 인자는 윈도우창의 가로, 세로의 크기를 지정한다.
    // 픽셀단위로 지정을 해준다.
    // 8번 인자는 부모윈도우가 있다면 부모윈도우의 핸들을 지정한다.
    // 없으면 nullptr을 지정한다.
    // 9번 인자는 메뉴가 있다면 메뉴 핸들을 넣어주고 없으면 nullptr을 지정한다.
    // 10번 인자는 윈도우 인스턴스를 지정하여 이 윈도우 인스턴스에 속한 윈도우 창을
    // 만들어주게 된다.
    // 윈도우 창을 만들어주고 정상적으로 만들어졌다면 생성된 윈도우 창의 핸들을
    // 반환해준다.
    // HWND 가 윈도우 핸들을 의미한다.
    // 만약 생성이 제대로 안되었다면 0을 반환한다.
    m_hWnd = CreateWindowW(TEXT("GameFramework"),
        TEXT("GameFramework"), WS_OVERLAPPEDWINDOW,
        100, 0, 0, 0, nullptr, nullptr, m_hInst, nullptr);

    if (!m_hWnd)
    {
        return false;
    }

    // RECT : 사각형을 표현하기 위해서 지원하는 구조체이다.
    // left, top, right, bottom 값으로 이루어져 있다.
    // 윈도우 크기를 표현하는 Rect 구조체를 하나 만들어준다.
    RECT    rc = { 0, 0, 1280, 720 };

    // 위에서 지정한 크기만큼 클라이언트 영역의 크기로 잡기 위해서
    // 필요한 실제 윈도우의 크기를 얻어온다.
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    // 위에서 얻어온 크기로 윈도우 창의 크기를 변경한다.
    MoveWindow(m_hWnd, 50, 50, rc.right - rc.left,
        rc.bottom - rc.top, TRUE);

    // 윈도우 창을 보여준다. 1번인자에 들어간 핸들의 윈도우 창을 보여줄지 말지를
    // 결정해준다.
    ShowWindow(m_hWnd, SW_SHOW);

    // 이 함수를 호출하여 클라이언트 영역이 제대로 갱신되었다면 0이 아닌 값을 반환하고
    // 갱신이 실패했을 경우 0을 반환한다.
    UpdateWindow(m_hWnd);

    return true;
}

LRESULT CGameManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        // 윈도우가 종료될때 들어오는 메세지이다.
        m_Loop = false;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
