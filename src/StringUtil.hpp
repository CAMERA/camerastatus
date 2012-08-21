/* 
 * File:   StringUtil.hpp
 * Author: churas
 *
 * Created on August 17, 2012, 10:24 AM
 */

#ifndef STRINGUTIL_HPP
#define	STRINGUTIL_HPP

class StringUtil {
public:
    StringUtil();
    virtual ~StringUtil();
    const char *getIntAsPaddedString(int value,int maxvalue,int size);
private:

};

#endif	/* STRINGUTIL_HPP */

