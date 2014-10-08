/*++
//  Module Name:
//    WString.cpp

//  Abstract:
//    This file contains the implementation of the WString class
//    which supports operations on string.
//
//  Author:
//    Xu, Feng s 29-Nov-2011
//
//  Revision History:
//    creation      Xu, Feng    29-Nov-2011
--*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "WString.h"

#define LOG_TAG "WString"
#define LOGE printf
#define LOGD printf
int WString::memoryCount = 0;

#ifdef __cplusplus
extern "C"
{
#endif

void WString::wstring_alloc(int size)
{
    if(size <= 0)
        return;
        
    if(size <= buf_size){
        msize = buf_size;
        m_data = buf;
        return;
    }
    if(msize >= size){
        return;
    }
    m_data = new char[size];
    memset(m_data, 0, size);
    WString::memoryCount += size;
    msize = size;
}

void WString::wstring_dealloc()
{
    if(m_data == NULL){
        wstring_alloc(1); 
        m_data[0] = '\0';
        return;
    }
    if(m_data == buf){
        return;
    }
    WString::memoryCount -= msize;
    delete [] m_data;
    msize = 0;
    m_data = NULL;
}

WString::WString(const char *str)
{
    LOGD("Constructor: WString::WString(const char *str)\n");
    msize = 0;
    m_data = NULL;
    if(str==NULL){
        wstring_alloc(1); 
        m_data[0] = '\0';
    }else{
        int length = strlen(str);
        wstring_alloc(length+1); 
        strncpy(m_data, str, msize);
        m_data[msize-1] = '\0';
    }
}

WString::WString()
{
    LOGD("Constructor: WString::WString()\n");
    msize = 0;
    m_data = NULL;
    wstring_alloc(1); 
    m_data[0] = '\0';
}

WString::~WString(void)
{
    LOGD("Destructor: WString::~WString(void)\n");
    wstring_dealloc();
}

WString::WString(const WString &other) 
{
    LOGD("Copy Constructor: WString::WString(const WString &other) \n");
    msize = 0;
    m_data = NULL;
    int length = strlen(other.m_data);
    wstring_alloc(length+1);
    strncpy(m_data, other.m_data, msize);
    m_data[msize-1] = '\0';
}

WString& WString::operator =(const WString &other)
{
    LOGD("Operator =: WString& WString::operator =(const WString &other)\n");
    if(this == &other)
        return *this;
    wstring_dealloc();
    
    int len = ((WString&)other).length();
    wstring_alloc(len+1);
    strncpy(m_data, ((WString&)other).get(), msize);
    m_data[msize-1] = '\0';
    return *this;
}

WString& WString::operator =(const char* other)
{
    LOGE("Operator =: WString& WString::operator =(const char* other)\n");
    if(other == NULL){
        wstring_dealloc();
        wstring_alloc(1);
        m_data[0] = '\0';
        return *this;
    }
    
    if(m_data == (char*)other)
        return *this;
    
    if(other+strlen(other) < m_data || m_data+strlen(m_data) < other){
        wstring_dealloc();
        int len = strlen(other);
        wstring_alloc(len+1);
        strncpy(m_data, other, msize);
        m_data[msize-1] = '\0';
        return *this;
    }else{
        // m_data and other is overlapped. 
        if(other >= m_data && other+strlen(other) <= m_data+strlen(m_data)){
            // other is a sub string of m_data
            int i = 0;
            for(;i<strlen(other)+1;i++){
                m_data[i] = other[i];
            }
            m_data[msize-1] = '\0';
        }else{
            // Just part of m_data and other is overlapped. return without doing anything
            // as we don't know how to deal with the buffer in m_data
            LOGE("operator = error");
        }
        return *this;
    }
}

WString WString::operator +(const WString & other)
{
    WString s;
    int lenA = strlen(m_data);
    int lenB = strlen(other.m_data);
    LOGD("Operator +: WString WString::operator +(const WString & other)\n");
    s.wstring_dealloc();
    s.wstring_alloc(lenA+lenB+1);
    strncpy(s.m_data, m_data, lenA+1);
    strncpy(s.m_data+lenA, other.m_data, lenB+1);
    s.m_data[s.msize-1] = '\0';
    return s;
}

bool WString::startsWith(const char *str)
{
    if(str == NULL)
        return false;

    if(strstr(m_data, str) == m_data)
        return true;

    return false;
}

void WString::toLowerCase()
{
    if(length() == 0)
        return;
    
    int i;
    for(i=0;i<length();i++){
        m_data[i] = tolower(m_data[i]);
    }
}

void WString::toUpperCase()
{
    if(length() == 0)
        return;
    
    int i;
    for(i=0;i<length();i++){
        m_data[i] = toupper(m_data[i]);
    }
}

int WString::indexOf(const char *str)
{
    if(str == NULL)
        return -1;

    char* pos = NULL;
    if((pos=strstr(m_data, str)) == NULL)
        return -1;

    return pos-m_data;
}

int WString::caseIndexOf(const char *str)
{
    if(str == NULL)
        return -1;

    WString thiz(m_data);
    WString src(str);
    
    thiz.toUpperCase();
    src.toUpperCase();
    
    return thiz.indexOf(src.get());
}

int WString::caseIndexOf(int start, const char *str)
{
    if(str == NULL || (start > length()-1) || start < 0)
        return -1;

    WString thiz(m_data);
    WString src(str);
    
    thiz.toUpperCase();
    src.toUpperCase();
    
    return thiz.indexOf(start, src.get());
}

int WString::indexOf(int start, const char *str)
{
    if(str == NULL || (start > length()-1) || start < 0)
        return -1;
    
    char* pos = NULL;
    if((pos=strstr(m_data+start, str)) == NULL)
        return -1;

    return pos-m_data;
}

int WString::subString(int start, int end, WString& s)
{
    if(end< 0 || start < 0 || start > end || end > length()-1){
        s.m_data[0] = '\0';
        return -1;
    }
        
    if(&s == this){
        int i = 0;
        for(;i<end-start+1;i++){
            s.m_data[i] = m_data[i+start];
        }
        s.m_data[i] = '\0';
        return 0;
    }

    char endChar = m_data[end+1];
    char* other = s.get();
    if(other+strlen(other) < m_data || m_data+strlen(m_data) < other){
        m_data[end+1] = '\0';
        s = m_data+start;
        m_data[end+1] = endChar;
    }else{
        // Just part of m_data and other is overlapped. The request is invalid.
        LOGE("subString error");
        return -1;
    }
    return 0;
}

int WString::getSplit(int* start, const char* pattern, WString& s)
{
    if(start == NULL || *start >= length() || *start < 0 || pattern == NULL)
        return -1;

    char* pos = NULL;
    int tstart = *start;
    if((pos=strstr(m_data+tstart, pattern)) == NULL){
        s.m_data[0] = '\0';
        return -1;
    }
    *start = pos + strlen(pattern) - m_data;
    subString(tstart, pos-1-m_data, s);
    return 0;
}

int WString::length()
{
   return strlen(m_data);
}

bool WString::equals(const char *str)
{
   bool isMatch = false;
   if(str == NULL)
       return isMatch;

   if(strcmp(m_data, str) == 0)
       isMatch = true;
   
   return isMatch;
}

bool WString::equalsIgnoreCase(const char *str)
{
   bool isMatch = false;
   if(str == NULL)
       return isMatch;

   if(strcasecmp(m_data, str) == 0)
       isMatch = true;
   
   return isMatch;
}

char* WString::get()
{
   return m_data;
}

char* WString::strim()
{
   int end = length();
   if(end == 0)
       return m_data;
   
   end -= 1;
   while(m_data[end] == ' ' || m_data[end] == '\t' || m_data[end] == '\r' || m_data[end] == '\n'){
       end --;
       if(end < 0){
           m_data[0] = '\0';
           return m_data;
       }
   }
   m_data[end+1] = '\0';

   int start = 0;
   while(m_data[start] == ' ' || m_data[start] == '\t' || m_data[start] == '\r' || m_data[start] == '\n'){
       start ++;
       if(start >= length()){
           m_data[0] = '\0';
           return m_data;
       }
   }
   if(start > 0){
       int i = 0;
       for(;i<end-start+1;i++){
           m_data[i] = m_data[start+i];
       }
       m_data[i] = '\0';
   }
   return m_data;
}

bool WString::isEmpty()
{
   return (length() == 0)?true:false;
}

char WString::charAt(int pos)
{
    if(pos < 0 || pos > length()-1)
        return 0;

    return m_data[pos];
}

int WString::append(WString &s)
{
    return append(s.get());
}

int WString::append(const char *s)
{
    if(s == NULL)
        return 0;

    int lenA = strlen(m_data);
    int lenB = strlen(s);
    char* thisData = m_data;
    int thisSize = msize;
    char* appendData = (char*)s;
    
    if(s+lenB < m_data || s > m_data+lenA){
        // no overlap between s and this string
        if(msize < (lenA+lenB+1)){
            wstring_alloc(lenA+lenB+1);
            strncpy(m_data, thisData, lenA+1);
            strncpy(m_data+lenA, appendData, msize-lenA);
            m_data[msize-1] = '\0';
            if(thisData != buf && thisData != m_data){
                memoryCount -= thisSize;
                delete [] thisData;
            }
        }else{
            strncpy(m_data+lenA, appendData, lenB+1);
            m_data[msize-1] = '\0';
        }
    }else if (s+lenB == m_data+lenA){
        // s and this string is overlapped
        if(msize < (lenA+lenB+1)){
            wstring_alloc(lenA+lenB+1);
        }
        
        int i;
        for(i=0;i<lenA;i++){
            m_data[i] = thisData[i];
        }
        for(i=0;i<lenB;i++){
            m_data[i+lenA] = appendData[i];
        }
        m_data[i+lenA] = '\0';
        if(thisData != buf && thisData != m_data){
            memoryCount -= thisSize;
            delete [] thisData;
        }
    }else{
        // the end of s and this string is different.
        // it is clearly a error situation
        LOGE("Append error");
        return -1;
    }
    return 0;
}

#ifdef __cplusplus
}
#endif


