/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_context_part_hxx
#define __world_context_part_hxx

namespace world
{
    class context;

    class context_part
    {
    public:
        context_part(context *ctx);

        virtual ~context_part();

        context *get_context() const { return _m_context; }

    private:
        context *const _m_context;
    };
}

#endif
