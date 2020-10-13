#include "EventHandler.hpp"

void CG::EventHandler::registerCallback(unsigned int key, void (*callback)(GLFWwindow* window, int key, int scancode, int action, int mods))
{
	auto key_index = _keyCallbacks.find(key);

	if (key_index == _keyCallbacks.end())
		_keyCallbacks.emplace(key, callback);
	else {
		CG_CONSOLE_WARN("callback '{}' already bound. overriding it.", key);
		_keyCallbacks[key] = callback;
	}
}

void CG::EventHandler::executeCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	for (auto& [callbackKey, callback] : _keyCallbacks)
		if (key == callbackKey)
			callback(window, key, scancode, action, mods);
}
