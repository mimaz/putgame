/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __common_program_hxx
#define __common_program_hxx

namespace common
{
    class shader;

    class program
    {
    public:
        using shdvec = std::vector<shader *>;

        program(shdvec shdv);

          template<typename ..._Shaders>
        program(const _Shaders &...shaders);

    private:
        std::vector<shader *> shdv;

        GLuint handle;
    };

      template<typename ..._Shaders>
    program::program(const _Shaders &...shaders)
    {
        
    }
}


#endif
