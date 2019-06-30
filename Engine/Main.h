#pragma once

#ifndef MAIN_H
#define MAIN_H_

#include <Windows.h>
#include <string>

extern "C"
{

	__declspec(dllexport) void ReleaseMemory(void* &ptr);

	__declspec(dllexport) bool ChechPointerIsCorrect(void* ptr);

	__declspec(dllexport) void InitD3D(HWND hWnd, int width, int height);
	__declspec(dllexport) bool InitInput(HINSTANCE hInstance);
	__declspec(dllexport) void Render();
	__declspec(dllexport) void Update();
	__declspec(dllexport) void Cleanup();
	__declspec(dllexport) void InitWorld();

	__declspec(dllexport) void TestUpdate(int command, float x, float y);

	__declspec(dllexport) void CreateObject(int type);

	__declspec(dllexport) void MoveObject(float x, float y, float z);

	__declspec(dllexport) void SelectObject1(int index);

	__declspec(dllexport) void ResizeObject(float x, float y, float z);

	__declspec(dllexport) void DeleteEntity();

	__declspec(dllexport) void ResizeViewport(float to);

	__declspec(dllexport) void SetTexture(char* t);

	__declspec(dllexport) void Translate(float x, float y, float z);

	__declspec(dllexport) void ChangeName(const char* name);

	__declspec(dllexport) void StartAnimation();

	__declspec(dllexport) void CreateFromModel(char* path);

	__declspec(dllexport) void Rotate(float x, float y, float z);

	__declspec(dllexport) void Next();
	__declspec(dllexport) void Prev();

	__declspec(dllexport) void IncreaseDecrease(float x, float y, float z);

	__declspec(dllexport) void ChangeColor(int r, int g, int b);

	__declspec(dllexport) void Clone();

	__declspec(dllexport) void IsDrawGraph(bool state);
	__declspec(dllexport) void SetType(int type);
	__declspec(dllexport) void AddGraph3DVertex(float x, float y, float z, float r, float g, float b);
	__declspec(dllexport) void InitializeGraph();
	__declspec(dllexport) void ResetGraph3D();
	
	__declspec(dllexport) void BuildGraph3D(const float *x, const float *y, const float *z, int size);

	///Animation language

	__declspec(dllexport) void AddKey(int type, int start, float duration, float x, float y, float z);

	__declspec(dllexport) void Reset();

	__declspec(dllexport) void SetProperty(int _property, int value);

	//Retrieve an object`s data

	__declspec(dllexport) int EntityNumber();

	__declspec(dllexport) float* GetPosition(int index);

	__declspec(dllexport) void ChangeCameraSpeed(float to);

	////UI Editor

	__declspec(dllexport) void ClearUI();

	__declspec(dllexport) void InitUI();

	__declspec(dllexport) void AddLabel(const wchar_t* text, const char* fontName, int posX, int posY, int sizeX, int sizeY, int fontSize);

	__declspec(dllexport) void AddSprite(const char* path, int posX, int posY, int sizeX, int sizeY);

	__declspec(dllexport) void SetPlaying();
}

#endif