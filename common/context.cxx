/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include "context.hxx"
#include "log.hxx"

namespace common
{
    context::context() 
    {
        common::logi("created common::context");
    }

    context::~context()
    {
        common::logi("destroyed common::context");
    }
}
