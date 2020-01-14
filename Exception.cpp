#include "Exception.h"
#include <sstream>

Exception::Exception(std::string msg, int line, const char* file, std::string name) noexcept : m_sMessage(msg), m_nLine(line), m_sName(name), m_sFile(file)
{
	char message[512];
	sprintf_s(message, "[LINE]: %i\n[FILE]: %s\n[MESSAGE]: %s", m_nLine, m_sFile.c_str(), m_sMessage.c_str());
	m_sBuffer = std::string(message, strlen(message));
	m_sBuffer.shrink_to_fit();
}

Exception::Exception(DWORD errCode, int line, const char* file, std::string name) noexcept : m_sName(name), m_nLine(line), m_sFile(file)
{
	m_sMessage = TranslateErrorCode(errCode);
	char message[512];
	sprintf_s(message, "[LINE]: %i\n[FILE]: %s\n[MESSAGE]: %s", m_nLine, m_sFile.c_str(), m_sMessage.c_str());
	m_sBuffer = std::string(message, strlen(message));
	m_sBuffer.shrink_to_fit();
}

inline const char* Exception::what() const noexcept
{
	return m_sBuffer.c_str();
}

std::string Exception::name() const noexcept
{
	return m_sName;
}

std::string Exception::message() const noexcept
{
	return m_sMessage;
}

std::string Exception::file() const noexcept
{
	return m_sFile;
}

std::string Exception::TranslateErrorCode(DWORD errorCode) noexcept
{
	// get language id
	DWORD value;
	int langResult = GetLocaleInfoEx(L"en-us", LOCALE_ILANGUAGE | LOCALE_RETURN_NUMBER, reinterpret_cast<LPWSTR>(&value), sizeof(DWORD) / sizeof(wchar_t));
	LANGID langId = value;

	// get message corresponding its error code
	LPSTR pBuffer = nullptr;
	DWORD formatResult = FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,	// dwFlags
		NULL,																							// lpSource
		errorCode,																						// dwMessageId
		langId,																							// dwLanguageId
		reinterpret_cast<LPSTR>(&pBuffer),																// lpBuffer
		0,																								// nSize
		NULL																							// pArgs
	);

	if (!formatResult) return "Unknow error with code: " + std::to_string(errorCode);

	// store in an wstring instance and free buffer
	std::string msg = std::string(pBuffer, strlen(pBuffer));
	LocalFree(pBuffer);
	return msg;
}

void Exception::throw_if_false(HRESULT hr, std::string msg, int line, const char* file, std::string name)
{
	if (FAILED(hr)) throw Exception(msg, line, file, name);
}

void Exception::throw_if_false(BOOL hr, std::string msg, int line, const char* file, std::string name)
{
	if (!hr) throw Exception(msg, line, file, name);
}
