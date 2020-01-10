#pragma once
#ifdef _DEBUG
#include "Windows.h"
#include <memory>

#define AST() {\
	CHAR ast_mes[256];\
	wsprintf(ast_mes, "%s %dçsñ⁄\0", __FILE__, __LINE__);\
	MessageBox(0, ast_mes, "±ª∞ƒï\é¶", MB_OK);\
	}

#define TRACE(fmt, ...) printf(fmt,__VA_ARGS__);

class _DebugConOut
{
public:
	static _DebugConOut &GetInstance(void)
	{
		return *sInstance;
	}

private:
	struct _DebugConOutDeleter
	{
		void operator()(_DebugConOut* _DebugConOut) const
		{
			delete _DebugConOut;
		}
	};

	_DebugConOut();
	~_DebugConOut();

	FILE* _debugFp = nullptr;
	static std::unique_ptr<_DebugConOut, _DebugConOutDeleter>sInstance;
};

#else  // DEBUG

#define TRACE(fmt, ...)
#endif // DEBUG
