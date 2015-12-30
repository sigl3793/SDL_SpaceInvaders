#pragma once

/*
Suggested structure for a potential future InputManager
Init will create objects needed and shutdown will delete them.
Update will handle all the events with SDL_PollEvent update the
mouse and keyboard objects accordingly.
Other functions will return appropriate data from the mouse and keyboard.

class InputManager
{
public:
InputManager() {};
~InputManager() {};
void Initialize() {};
void Shutdown() {};
int GetMouseX() {};
int GetMouseY() {};
bool IsMouseButtonDown(int p_iIndex) { return false; }
bool IsKeyDown(int p_iIndex) { return false; }
void Update() {};
private:
Mouse* m_pxMouse;
Keyboard* m_pxKeyboard
};
*/