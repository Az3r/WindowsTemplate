#pragma once
#include <exception>
#include <string>
#include <Windows.h>

class Exception : public std::exception
{
protected:
    std::string m_sBuffer;
    std::string m_sName;
    int m_nLine;
public:
    Exception(std::string msg, int line, std::string name = "Exception") noexcept;
    Exception(DWORD errCode, int line, std::string name = "Exception") noexcept;
    virtual ~Exception() noexcept {}
    virtual const char* what() const noexcept;
    virtual const std::string name() const noexcept;

    // Translate error code returned from GetLastError() to string
    static std::string TranslateErrorCode(DWORD errorCode) noexcept;
    static void throw_if_false(HRESULT hr, std::string msg, int line, std::string name = "Exception");
    static void throw_if_false(BOOL hr, std::string msg, int line, std::string name = "Exception");
};

