#include "Input.h"


DirectInput::DirectInput()
{
	
}


bool DirectInput::Init(HWND hwnd, HINSTANCE hInstance, int width, int height)
{
	
	HRESULT result;

	screenWidth = width;
	screenHeight = height;

	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mInput, NULL);


	if (FAILED(result))
	{
		return false;
	}


	//create keyboard
	result = mInput->CreateDevice(GUID_SysKeyboard, &mKeyboard, NULL);

	if (FAILED(result))
	{
		return false;
	}

	result = mKeyboard->SetDataFormat(&c_dfDIKeyboard);

	if (FAILED(result))
	{
		return false;
	}

	result = mKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	if (FAILED(result))
	{
		return false;
	}

	result = mKeyboard->Acquire();


	if (FAILED(result))
	{
		return false;
	}

	//mouse create

	result = mInput->CreateDevice(GUID_SysMouse, &mMouse, NULL);

	if (FAILED(result))
	{
		return false;
	}

	result = mMouse->SetDataFormat(&c_dfDIMouse);

	if (FAILED(result))
	{
		return false;
	}

	result = mMouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	if (FAILED(result))
	{
		return false;
	}

	result = mMouse->Acquire();

	if (FAILED(result))
	{
		return false;
	}

	ShowCursor(true);

	return true;
}

DirectInput::~DirectInput()
{
	Shutdown();
}

void DirectInput::Shutdown()
{
	if (mKeyboard)
	{
		mKeyboard->Unacquire();
		mKeyboard->Release();

		delete mKeyboard;
	}

	if (mMouse)
	{
		mMouse->Unacquire();
		mMouse->Release();

		delete mMouse;
	}

	if (mInput)
	{
		mInput->Release();

		delete mInput;
	}
}

bool DirectInput::Frame()
{
	bool result;

	result = ReadKeyboard();

	if (!result)
	{
		return false;
	}

	result = ReadMouse();

	if (!result)
	{
		return false;
	}

	ProcessInput();

	return true;
}

bool DirectInput::ReadKeyboard()
{
	HRESULT result;

	result = mKeyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);

	if (FAILED(result))
	{
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
		{
			mKeyboard->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool DirectInput::ReadMouse()
{
	HRESULT result;

	result = mMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouseState);

	if (FAILED(result))
	{
		if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
		{
			mMouse->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

void DirectInput::ProcessInput()
{
	mouseX += mouseState.lX;

	mouseY += mouseState.lY;

	if (mouseX < 0)
		mouseX = 0;

	if (mouseY < 0)
		mouseY = 0;

	if (mouseX > screenWidth)
		mouseX = screenWidth;

	if (mouseY > screenHeight)
		mouseY = screenHeight;


}

void DirectInput::GetMousePosition(int &x, int &y)
{
	x = mouseX;
	y = mouseY;
}

bool DirectInput::IsKeyPressed(unsigned int key)
{
	return keyboardState[key] & 0x80;
}

DirectInput& DirectInput::operator=(const DirectInput b)
{
	for (int i = 0; i < 256; i++)
	{
		this->keyboardState[i] = b.keyboardState[i];
	}

	this->mouseState = b.mouseState;

	return *this;
}

bool DirectInput::IsMouseButtonPressed(short key)
{
	return (mouseState.rgbButtons[key] & 0x80);
}

std::vector<unsigned char> DirectInput::GetKeyboardState()
{
	std::vector<unsigned char> v(256);

	for (int i = 0; i < 256; i++)
	{
		v[i] = keyboardState[i];
	}
	return v;
}

DIMOUSESTATE DirectInput::GetMouseState()
{
	return mouseState;
}