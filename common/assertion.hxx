/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __common_assertion_hxx
#define __common_assertion_hxx

namespace common
{
    void assertion(bool cond);
    void assertion(bool cond, const std::string &errmsg);
}

#endif
