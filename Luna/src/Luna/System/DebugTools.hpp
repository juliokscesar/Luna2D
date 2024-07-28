#pragma once

#define LunaDebugCheckGLError(msg) Luna::Debug::_CheckGLError(__FILE__, __LINE__, (msg))

#include <string>

namespace Luna::Debug
{
    void _CheckGLError(const char* file, int line, const std::string& msg);
}

