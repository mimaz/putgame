/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */


#include "assertion.hxx"

void common::assertion(bool cond)
{
    assertion(cond, "");
}

void common::assertion(bool cond, const std::string &errmsg)
{
    if (not cond)
    {
        auto &os = std::cerr;

        os << "assertion failed";

        if (not errmsg.empty())
            os << ": " << errmsg;

        os << std::endl;

        ::abort();
    }
}
