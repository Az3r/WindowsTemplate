#pragma once
#include <exception>
#include <string>
#include <Windows.h>

class Exception : public std::exception
{
protected:
    std::string m_sMessage;
    std::string m_sName;
    std::string m_sBuffer;
    int m_nLine;
public:
    Exception(std::string msg, int line, std::string name = "Exception") noexcept;
    Exception(DWORD errCode, int line, std::string name = "Exception") noexcept;
    virtual ~Exception() noexcept {}
    virtual const char* what() const noexcept;
    std::string name() const noexcept;
    std::string message() const noexcept;

    // Translate error code returned from GetLastError() to string
    static std::string TranslateErrorCode(DWORD errorCode) noexcept;
    static void throw_if_false(HRESULT hr, std::string msg, int line, std::string name = "Exception");
    static void throw_if_false(BOOL hr, std::string msg, int line, std::string name = "Exception");
};

#define try_throw(hr) if(FAILED(hr)) throw Exception(Exception::TranslateErrorCode(GetLastError()), __LINE__)