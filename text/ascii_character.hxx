/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __text_ascii_character_hxx
#define __text_ascii_character_hxx

namespace text
{
    class ascii_character
    {
    public:
        ascii_character(const char *layout, 
                        const char *order,
                        int code)
            : layout(layout)
            , order(order)
            , code(code)
        {}

        ascii_character(const ascii_character &) = default;
        ascii_character(ascii_character &&) = default;

        const char *get_layout() const { return layout; }
        const char *get_order() const { return order; }
        int get_code() const { return code; }

    private:
        const char *layout;
        const char *order;
        int code;
    };
}

#endif
