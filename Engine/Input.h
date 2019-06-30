#include <dinput.h>
#include <vector>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


class DirectInput
{
public:

	DirectInput();

	~DirectInput();

	bool Init(HWND, HINSTANCE, int, int);

	bool Frame();

	void GetMousePosition(int&, int &);

	bool IsKeyPressed(unsigned int);

	bool IsMouseButtonPressed(short);

	void Shutdown();

	DirectInput& operator=(const DirectInput);

	std::vector<unsigned char> GetKeyboardState();

	DIMOUSESTATE GetMouseState();

private:

	bool ReadKeyboard();

	bool ReadMouse();

	void ProcessInput();

private:

	IDirectInput* mInput;

	IDirectInputDevice* mKeyboard;

	IDirectInputDevice* mMouse;

	unsigned char keyboardState[256];

	DIMOUSESTATE mouseState;

	int screenWidth, screenHeight;

	int mouseX, mouseY;


};