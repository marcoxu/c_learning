/*++
//  Module Name:
//    WString.h

//  Abstract:
//    This file contains the implementation of the WString class
//
//  Author:
//    Xu, Feng 29-Nov-2011
//
//  Revision History:
//    creation      Xu, Feng    29-Nov-2011
--*/

#ifndef _WSTRING_H
#define _WSTRING_H
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

class WString
{
public:
    WString(const char *str);
    WString();
    WString(const WString&s);
    ~WString();
    WString& operator =(const WString &s);
    WString& operator =(const char* s);

    /*
     * startsWith:  check if mdata is started with the specified string
     * @param IN str: the string that is required to be found at the front of mdata
     * Return: TRUE if it is found
     */
    bool startsWith(const char *str);

    /*
     * indexOf:  find the poistion in mdata in case it contains the specified string
     *           (case sensitive).
     * @param IN str: the string that is required to be found in mdata
     * Return: >=0 it if found otherwise returns -1
     */
    int indexOf(const char *str);

    /*
     * caseIndexOf: find the poistion in mdata in case it contains the specified string
     *              (not case sensitive).
     * @param IN str: the string that is required to be found in mdata
     * Return: >=0 it if found otherwise returns -1
     */
    int caseIndexOf(const char *str);

    /*
     * indexOf:  find the poistion in mdata in case the sub string of mdata (starts from 
     *           specified position) contains the specified string (case sensitive).
     * @param IN start: the start position of the sub string of mdata
     * @param IN str  : the string that is required to be found in sub string
     * Return: >=0 it if found otherwise returns -1
     */
    int indexOf(int start, const char *str);

    /*
     * caseIndexOf:  find the poistion in mdata in case the sub string of mdata (starts from 
     *           specified position) contains the specified string (not case sensitive).
     * @param IN start: the start position of the sub string of mdata
     * @param IN str  : the string that is required to be found in sub string
     * Return: >=0 it if found otherwise returns -1
     */
    int caseIndexOf(int start, const char *str);

    /*
     * toLowerCase: convert the string in mdata to lower case.
     */
    void toLowerCase();

    /*
     * toUpperCase: convert the string in mdata to upper case.
     */
    void toUpperCase();

    /*
     * subString:  get the sub string from mdata
     * @param IN start: the start position of the sub string of mdata
     * @param IN end  : the end position of the sub string of mdata
     * @param OUT s   : the WString object to carry the sub string
     * Return: return 0 in case sub string is got
     */
    int subString(int start, int end, WString& s);

    /*
     * length:  get the length of mdata
     * Return: string length
     */
    int length();

    /*
     * equals:  check if mdata equals to the specified string (case sensitive)
     * @param IN str: the string that needs to be compared with mdata
     * Return: return TRUE if they are equal
     */
    bool equals(const char *str);

    /*
     * get:  get mdata
     * Return: the pointer of mdata
     */
    char* get();

    /*
     * isEmpty:  check if mdata is empty string ("\0")
     * Return: return TRUE if it is empty
     */
    bool isEmpty();

    /*
     * charAt:  get the charactor at the specified position of mdata
     * @param IN pos: the value of the position
     * Return: returns the charactor in case it exists otherwise returns -1
     */
    char charAt(int pos);

    /*
     * strim:  get rid of the '\n','\r' and space from the front/end of mdata
     * Return: return mdata after the charactors are removed
     */
    char* strim();

    /*
     * getSplit:  split mdata from the specified position by dividing it with
     *            a certain pattern.
     * @param IN start  : the start position of mdata
     * @param IN pattern: the pattern that is used to divide mdata
     * @param OUT s     : the string between the start position and the pattern
     * Return: returns 0 if pattern is found otherwise returns -1
     */
    int getSplit(int* start, const char* pattern, WString& s);
    static int getMemoryCount() {return memoryCount;};

    /*
     * equalsIgnoreCase:  check if mdata equals to the specified string (not case sensitive)
     * @param IN str: the string that needs to be compared with mdata
     * Return: return TRUE if they are equal
     */
    bool equalsIgnoreCase(const char *str);

    /*
     * append:  append the specified string at the end of mdata
     * @param IN s: the string that needs to be appended
     * Return: return 0 if success
     */
    int append(WString &s);

    /*
     * append:  append the specified string at the end of mdata
     * @param IN s: the string that needs to be appended
     * Return: return 0 if success
     */
    int append(const char *s);
    WString operator +(const WString &s);
private:
    static int memoryCount;
    static const int buf_size = 50;
    char buf[buf_size];
    char *m_data;
    int msize;

    /*
     * wstring_alloc:  allocate memory for m_data
     * @param IN size: the size of the memory that is required
     */
    void wstring_alloc(int size);

    /*
     * wstring_dealloc:  deallocate the memory that is allocated for m_data
     */
    void wstring_dealloc();
};

#ifdef __cplusplus
}
#endif

#endif
