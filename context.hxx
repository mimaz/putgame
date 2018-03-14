/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __world_context_hxx
#define __world_context_hxx

namespace world
{
    class camera;

    class context
    {
    public:
        class part;

        context();
        ~context();

        template<typename _Type>
        _Type *get_part();

    private:
    };

    class context::part
    {

    };
}

#endif
