/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <putgame/std>

#include "default_font.hxx"

text::ascii_font text::default_font = {
    0.05f,
    7, 7,
    {
        {
            "1     2"
            "       "
            "       "
            "       "
            "       "
            "       "
            "3     4", "#LS12431#L1423", 0
        },
        {
            "   1   "
            "       "
            "       "
            "       "
            "       "
            " 2  3  "
            "4     5", "#LS415#L23", 'a'
        },
        {
            "1    2 "
            "7     3"
            "       "
            "       "
            "       "
            "      4"
            "6    5 ", "#LS1234567", 'd'
        },
        {
            "1     5"
            "       "
            "       "
            "       "
            "       "
            "2      "
            " 3    4", "#LS12345", 'u'
        },
        {
            "2    3 "
            "      4"
            "      5"
            " 7   6 "
            "       "
            "       "
            "1      ", "#LS1234567", 'p'
        }
    }
};
