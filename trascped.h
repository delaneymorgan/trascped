/**
 * @file trascped.h
 *
 * @brief a header-only trace library
 *
 * @copyright Delaney & Morgan Computing
 */

#ifndef TRASCPED_TRASCPED_H
#define TRASCPED_TRASCPED_H

#include <boost/scoped_ptr.hpp>

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace trascped {

    const std::string START_TEXT = "TRACE_START";
    const std::string END_TEXT = "TRACE_END";
    const std::string CHECK_TEXT = "TRACE_CHECK";

    class Trace {
    public:
        Trace(const char *pFilePath, const char *pFunction, const int lineNo) :
                m_Filename(Trace::GetFilename(pFilePath)),
                m_Function(pFunction),
                m_LineNo(lineNo),
                m_Plus() {
            std::stringstream ss;
            ss << START_TEXT << ": " << m_Filename << ":" << m_Function << ":" << m_LineNo << std::endl;
            std::cout << ss.str();
        }

        Trace(const char *pFilePath, const char *pFunction, const int lineNo, std::string &plus) :
                m_Filename(Trace::GetFilename(pFilePath)),
                m_Function(pFunction),
                m_LineNo(lineNo),
                m_Plus(plus) {
            std::stringstream ss;
            ss << START_TEXT << ": " << m_Filename << ":" << m_Function << ":" << m_LineNo;
            if (!m_Plus.empty()) {
                ss << " - " << m_Plus;
            }
            ss << std::endl;
            std::cout << ss.str();
        }

        ~Trace() {
            std::stringstream ss;
            ss << END_TEXT << ":   " << m_Filename << ":" << m_Function;
            if (!m_Plus.empty()) {
                ss << " - " << m_Plus;
            }
            ss << std::endl;
            std::cout << ss.str();
        }

        void Check(const int lineNo, const char *pFormat, ...) {
            va_list args1, args2;
            va_start(args1, pFormat);
            va_copy(args2, args1);
            int size = vsnprintf(NULL, 0, pFormat, args1);
            std::vector<char> buffer(size + 1);
            vsnprintf(buffer.data(), buffer.size(), pFormat, args2);
            std::string str = std::string(&buffer[0], size);
            std::stringstream ss;
            ss << CHECK_TEXT << ": " << m_Filename << ":" << m_Function << ":" << lineNo << " - " << str << std::endl;
            std::cout << ss.str();
        }

    private:

        static std::string GetFilename(const char *pFilePath) {
            std::string ret = strrchr(pFilePath, '/') ? strrchr(pFilePath, '/') + 1 : pFilePath;
            return ret;
        }

    private:
        std::string m_Filename;
        const char *m_Function;
        int m_LineNo;
        std::string m_Plus;
    };

#define TRACE() boost::scoped_ptr<Trace> _abcdef_( new Trace( __FILE__, __PRETTY_FUNCTION__, __LINE__ ))

#define TRACE_CHECK(format, ...) _abcdef_->Check(__LINE__, format, ##__VA_ARGS__)

}

#endif //TRASCPED_TRASCPED_H
