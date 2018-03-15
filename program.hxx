/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#ifndef __glutils_program_hxx
#define __glutils_program_hxx

namespace glutils
{
    class shader;

    class program
    {
    public:
        using shdlist = std::initializer_list<shader *>;
        using shdvec = std::vector<shader *>;

        program(const shdlist &list);

          template<typename ..._Shaders>
        program(const _Shaders &...shaders);

        program(const program &) = delete;
        program(program &&) = delete;

        ~program();

        void link();
        void destroy();

        GLuint get_handle();

        operator GLuint() { return get_handle(); }

    private:
        shdvec shdv;

        GLuint handle;
    };

      template<typename ..._Shaders>
    program::program(const _Shaders &...shaders)
        : program({ shaders... }) {}
}

#endif
