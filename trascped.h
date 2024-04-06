//
// Created by craig on 6/04/24.
//

#ifndef TRASCPED_TRASCPED_H
#define TRASCPED_TRASCPED_H

#include <boost/scoped_ptr.hpp>
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>

const std::string START_TEXT = "TRACE_START";
const std::string END_TEXT = "TRACE_END";

class Trace {
public:
    Trace(const char *pFilePath, const char *pFunction, const int lineNo) :
            m_FilePath(pFilePath),
            m_Filename(Trace::GetFilename(pFilePath)),
            m_Function(pFunction),
            m_LineNo(lineNo) {
        std::cout << START_TEXT << ": " << m_Filename << ":" << m_Function << ":" << m_LineNo << std::endl;
    }

    Trace(const char *pFilePath, const char *pFunction, const int lineNo, std::string &plus) :
            m_FilePath(pFilePath),
            m_Filename(Trace::GetFilename(pFilePath)),
            m_Function(pFunction),
            m_LineNo(lineNo),
            m_Plus(plus) {
        std::cout << START_TEXT << ": " << m_Filename << ":" << m_Function << ":" << m_LineNo;
        if (!m_Plus.empty()) {
            std::cout << " - " << m_Plus;
        }
        std::cout << std::endl;
    }

    ~Trace() {
        std::cout << END_TEXT << ": " << m_Filename << ":" << m_Function;
        if (!m_Plus.empty()) {
            std::cout << " - " << m_Plus;
        }
        std::cout << std::endl;
    }

private:

    static std::string GetFilename(const char *pFilePath) {
        std::string ret = strrchr(pFilePath, '/') ? strrchr(pFilePath, '/') + 1 : pFilePath;
        return ret;
    }

private:
    const char *m_FilePath;
    std::string m_Filename;
    const char *m_Function;
    int m_LineNo;
    std::string m_Plus;
};

#define TRACE() boost::scoped_ptr<Trace> _abcdef_( new Trace( __FILE__, __PRETTY_FUNCTION__, __LINE__ ))

#endif //TRASCPED_TRASCPED_H
