#pragma once
#include "../../Core/Public/CData.h"

class HInput
{
    static std::vector<KeyCallBack> _keyRegisterDefault;
    static std::vector<KeyCallBack> _keyRegisterRepeat;
    //
    static std::vector<MouseCallBack> _mouseRegisterDefault;
    static std::vector<MouseCallBack> _mouseRegisterRepeat;

public:
	//Keyboard	注册当前帧反馈按键

	static inline bool GetKey(KeyCode key) {
		return FindRepeatKey(key) != nullptr;
	}

	static inline bool GetKeyDown(KeyCode key) {
		return FindDefaultKeyDown(key, Action::PRESS) != nullptr;
	}

	static inline bool GetKeyUp(KeyCode key) {
		return FindDefaultKey(key, Action::RELEASE) != nullptr;
	}

	static inline bool GetMouse(MouseButton button) {
		return FindRepeatMouse(button) != nullptr;
	}

	static inline bool GetMouseDown(MouseButton button) {
		return FindDefaultMouseDown(button, Action::PRESS) != nullptr;
	}

	static inline bool GetMouseUp(MouseButton button) {
		return FindDefaultMouse(button, Action::RELEASE) != nullptr;
	}

    static inline void SetCursorPos(glm::vec2 pos)
    {
        SDL_WarpMouseGlobal(pos.x, pos.y);
    }

    static inline void SetCursorPosClient(SDL_Window* Window, glm::vec2 pos)
    {
        if (Window)
        {
            SDL_WarpMouseInWindow(Window, pos.x, pos.y);
        }
    }

    static inline void ShowCursor(bool bShow)
    {
        if (bShow)
            SDL_ShowCursor();
        else
            SDL_HideCursor();
    }

	static inline glm::vec2 GetMousePos()
	{
        glm::vec2 result(0);
        SDL_GetGlobalMouseState(&result.x, &result.y);
        //return _mousePos;
        return result;
	}

    static inline glm::vec2 GetMousePosClient()
    {
        glm::vec2 result(0);
        SDL_GetMouseState(&result.x, &result.y);
        //return _mousePosInWindow;
        return result;
    }

	//清空当前帧的输入缓存,其他时候不要主动调用该函数!
	static void ClearInput()
	{
		_keyRegisterDefault.clear();
		//_keyRegisterRepeat.clear();
		_mouseRegisterDefault.clear();
		//_mouseRegisterRepeat.clear();
		for (auto& i : _keyRegisterRepeat)
		{
			i.bKeyDown = false;
		}
		for (auto& i : _mouseRegisterRepeat)
		{
			i.bMouseDown = false;
		}
	}

	//键盘输入的回调函数中调用,记录当前帧按下的按键,其他时候不要主动调用该函数!
	static void KeyProcess(KeyCode key, KeyMod mod ,Action action);

	//鼠标输入的回调函数中调用,记录当前帧按下的按键,其他时候不要主动调用该函数!
	static void MouseProcess(MouseButton mouse, Action action);

private:

	static inline KeyCallBack* FindDefaultKey(KeyCode key , Action action)
	{
		auto it = std::find_if(_keyRegisterDefault.begin(), _keyRegisterDefault.end(), [key, action](KeyCallBack& callback) {
			return callback.key == key && callback.action == action;
			});
		if (it != _keyRegisterDefault.end())
			return &(*it);
		else
			return nullptr;
	}

	static inline KeyCallBack* FindDefaultKeyDown(KeyCode key, Action action)
	{
		auto it = std::find_if(_keyRegisterRepeat.begin(), _keyRegisterRepeat.end(), [key, action](KeyCallBack& callback) {
			return callback.key == key && callback.action == action && callback.bKeyDown ==true;
			});
		if (it != _keyRegisterRepeat.end())
			return &(*it); 
		else
			return nullptr;
	}

	static inline KeyCallBack* FindRepeatKey(KeyCode key)
	{
		auto it = std::find_if(_keyRegisterRepeat.begin(), _keyRegisterRepeat.end(), [key](KeyCallBack& callback) {
            return callback.key == key;
			});
		if (it != _keyRegisterRepeat.end())
			return &(*it);
		else
			return nullptr;
	}

	//
	static inline MouseCallBack* FindDefaultMouse(MouseButton mouse, Action action)
	{
		auto it = std::find_if(_mouseRegisterDefault.begin(), _mouseRegisterDefault.end(), [mouse, action](MouseCallBack& callback) {
			return callback.button == mouse && callback.action == action;
			});
		if (it != _mouseRegisterDefault.end())
			return &(*it);
		else
			return nullptr;
	}

	static inline MouseCallBack* FindDefaultMouseDown(MouseButton mouse, Action action)
	{
		auto it = std::find_if(_mouseRegisterRepeat.begin(), _mouseRegisterRepeat.end(), [mouse, action](MouseCallBack& callback) {
			return callback.button == mouse && callback.action == action && callback.bMouseDown == true;
			});
		if (it != _mouseRegisterRepeat.end())
			return &(*it);
		else
			return nullptr;
	}
	
	static inline MouseCallBack* FindRepeatMouse(MouseButton mouse)
	{
		auto it = std::find_if(_mouseRegisterRepeat.begin(), _mouseRegisterRepeat.end(), [mouse](MouseCallBack& callback) {
			return callback.button == mouse;
			});
        if (it != _mouseRegisterRepeat.end())
        {
            return &(*it);
        }
		else
			return nullptr;
	}
};