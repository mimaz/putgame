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

        program(const std::string &tag,
                const shdlist &list);

          template<typename ..._Shaders>
        program(const std::string &tag,
                const _Shaders &...shaders);

        program(const program &) = delete;
        program(program &&) = delete;

        ~program();

        void link();
        void destroy();
        void use();

        std::string get_tag();
        GLuint get_handle();

        operator GLuint() { return get_handle(); }

    private:
        std::string tag;
        shdvec shdv;
        GLuint handle;
    };

      template<typename ..._Shaders>
    program::program(const std::string &tag,
                     const _Shaders &...shaders)
        : program(tag, { shaders... }) {}
}

#endif
