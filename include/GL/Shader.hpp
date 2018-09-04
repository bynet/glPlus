#pragma once 

#include <GL/glew.h>
#include <GL/GL.hpp>
#include <Util/Noncopyable.hpp>
#include <vector>
#include <memory>

//#define GLSL( x ) "#version 150\n" #x


using namespace std;

namespace GL {
	namespace ShaderType
	{
		enum shader_type_t
		{
			Vertex = GL_VERTEX_SHADER,
			Fragment = GL_FRAGMENT_SHADER,
			Geometry = GL_GEOMETRY_SHADER
		};
	}

	class ShaderFileException : public std::exception
	{
		virtual const char* what() const throw()
		{
			return "Failed to open shader file ";
		}
	};

	class CompileException : public std::exception
	{
	public:
		CompileException(const std::string& str) throw() : infoLog(str) {}
		~CompileException() throw() {}

		virtual const char* what() const throw()
		{
			return infoLog.c_str();
		}

	private:
		std::string infoLog;
	};

	
	class Shader :public Noncopyable {

		GLuint m_ID{ 0 };

		Shader(ShaderType::shader_type_t type);
		Shader(ShaderType::shader_type_t type , const string& code );

		static bool getFileContents(const std::string& filename, std::vector<char>& buffer);

	public :
		using Ptr = shared_ptr<Shader>;

		~Shader();

		Shader(Shader&& other);
		Shader& operator=(Shader&& other);

		operator GLuint() const { return m_ID; }

		void Source(const std::string& code);
		void Compile();
		GLuint Compile(GLenum type, const char* shaderCode);

		std::string GetInfoLog();

		static Ptr Create(ShaderType::shader_type_t type);
		static Ptr Create(ShaderType::shader_type_t type, const std::string& filename);
		static Ptr LoadFromFile(ShaderType::shader_type_t  type, const std::string& filename);


	};

}