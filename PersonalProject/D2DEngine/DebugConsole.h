#pragma once

struct {
	HANDLE m_hConsole;
	FILE* m_fCout;

	HANDLE Get_HCONS() { return m_hConsole; }

	// 콘솔창을 출력합니다.
	bool Get_Console()
	{
		if (!AllocConsole())
		{
			return false;
		}
		else
		{
			SetConsoleTitle(TEXT("Debug Console"));
			m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			_wfreopen_s(&m_fCout, L"CONOUT$", L"w", stdout);
			Log("Get_Console : Ok");
			return true;
		}
	}

	// 콘솔창을 닫습니다.
	bool Close_Console()
	{
		if (!FreeConsole())
		{
			return false;
		}
		else
		{
			fclose(m_fCout);
		}
		return true;
	}

	// 콘솔 창에 문자를 출력합니다.
	bool Log(const char* _log)
	{
		if (printf_s(_log) <= 0) return false;
		else
		{
			printf_s("\n");
			return true;
		}
	}
	bool Log(const wchar_t* _log)
	{
		if (wprintf_s(_log) <= 0) return false;
		else
		{
			printf_s("\n");
			return true;
		}
	}
	bool Log(std::string _log)
	{
		if (printf_s(_log.c_str()) <= 0) return false;
		else
		{
			printf_s("\n");
			return true;
		}
	}

	//콘솔창에 int,double,float값을 출력합니다.
	bool Log(double _log)
	{
		if (printf_s("%f\n", _log) <= 0) return false;
		return true;
	}

	bool Log(int _log)
	{
		if (printf_s("%d\n", _log) <= 0) return false;
		return true;
	}

	bool Log(float _log)
	{
		if (printf_s("%f\n", _log) <= 0) return false;
		return true;
	}
}Debug;

