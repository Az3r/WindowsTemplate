#pragma once
#include <exception>
#include <string>
#include <Windows.h>
#include <string>

class Exception : public std::exception
{
protected:
    std::string mMessage;
    std::string mName;
    std::string mBuffer;
    std::string mFile;
    int mLine;
public:
    Exception(std::string msg, int line, const char* file, std::string name = "Exception") noexcept;
    Exception(DWORD errCode, int line, const char* file, std::string name = "Exception") noexcept;
    virtual ~Exception() noexcept {}
    virtual const char* what() const noexcept;
    const std::string& name() const noexcept;
    const std::string& message() const noexcept;
    const std::string& file() const noexcept;

    // Translate error code returned from GetLastError() to string
    static std::string TranslateErrorCode(DWORD errorCode) noexcept;
    static void Assert(HRESULT hr, std::string msg, int line, const char* file, std::string name = "Exception");
    static void Assert(BOOL hr, std::string msg, int line, const char* file, std::string name = "Exception");
};

#define THROW_IF_FAILED(hr) if(FAILED(hr)) throw Exception(Exception::TranslateErrorCode(GetLastError()), __LINE__, __FILE__)
#define THROW_EXCEPTION(msg) throw Exception(msg, __LINE__, __FILE__)