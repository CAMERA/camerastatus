/* 
 * File:   StringUtil.hpp
 * Author: churas
 *
 * Created on August 17, 2012, 10:24 AM
 */

#ifndef STRINGUTIL_HPP
#define	STRINGUTIL_HPP

/**
 * Instances of this class provide a couple helper String methods
 * @author churas
 */
class StringUtil {
    
    /**
     * Sets the max field width used by getIntAsPaddedString method
     */
    static const int MAX_FIELD_SIZE_OF_INT = 10;
    
public:
    
    /**
     * Constructor
     */
    StringUtil();
    
    virtual ~StringUtil();
    
    /**
     * Given an integer (value) this method returns a string set to the width
     * set by (width) method with the value left padded with spaces to reach
     * the (width) specified.  If the width exceeds MAX_FIELD_SIZE_OF_INT constant
     * which at the time of this writing is 10, then the width will be reset to 10.
     * @param value Value to write into returned string.  If this value exceeds maxvalue 
     *        then ### equal to width will be returned
     * @param maxvalue any value above this value will cause this method to return ### 
     *        as the return value
     * @param width length in characters of returned string
     * @return left padded string (padded by spaces) of value parameter or empty string if 
     *         the width was less or equal to 0.
     */
    const char *getIntAsPaddedString(int value,int maxvalue,int width);
private:

};

#endif	/* STRINGUTIL_HPP */

