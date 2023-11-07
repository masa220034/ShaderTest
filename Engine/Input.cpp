#include "Input.h"

namespace Input
{
	LPDIRECTINPUT8   pDInput = nullptr;
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;
	BYTE keyState[256];        //現在の各キーの状態
	BYTE prevKeyState[256];    //前フレームでの各キーの状態
	XMVECTOR mousePosition;

	void Initialize(HWND hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);

		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);                 //デバイスオブジェクトを作成
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);                                    //デバイスの種類(今回はキーボード)を指定
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);  //協調レベルの設定
	}

	void Update()
	{
		memcpy(prevKeyState, keyState, sizeof(BYTE)*256);

		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState); 
	}

	bool IsKey(int keyCode)
	{
		if (keyState[keyCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	bool IsKeyDown(int keyCode)
	{
		//今は押してて、前回は押してない
		if (IsKey(keyCode) && !(prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		if (!IsKey(keyCode) && prevKeyState[keyCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	XMVECTOR GetMousePosition()
	{
		return mousePosition;
	}

	void SetMousePosition(int x, int y)
	{
		mousePosition = XMVectorSet((float)x, (float)y, 0, 0);
	}

	void Release()
	{
		SAFE_RELEASE(pDInput);
		SAFE_RELEASE(pKeyDevice);
	}

}