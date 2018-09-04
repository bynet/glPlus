#include <GL/Shader.hpp>
#include <logger.h>
namespace GL {

	Shader::Shader(ShaderType::shader_type_t type) {
		m_ID = glCreateShader(type);
	}

	Shader::Shader(ShaderType::shader_type_t type , const string& code ) {
		m_ID = glCreateShader(type);
		Source(code);
		Compile();
	}

	void Shader::Source(const std::string& code)
	{
		const char* c = code.c_str();
		glShaderSource(m_ID, 1, &c, NULL);
	}


	Shader::Ptr Shader::LoadFromFile(ShaderType::shader_type_t  type, const std::string& filename)
	{
		GL::ID shader_id = -1;

		Z::INFO() << "Loading shader ... " << filename;

		// Read the file
		std::vector<char> contents;
		if (!Shader::getFileContents(filename, contents))
		{
			throw ShaderFileException();
		}

		//return compile(type , &shader[0] );
		//return Shader(type, std::string(&contents[0]));
		return Shader::Create(type, string(&contents[0]));

	}

	void Shader::Compile()
	{
		GLint res{ 0 };

		glCompileShader(m_ID);
		glGetShaderiv(m_ID, GL_COMPILE_STATUS, &res);

		if (res == GL_FALSE)
			throw CompileException(GetInfoLog());
	}

	std::string Shader::GetInfoLog()
	{
		GLint res{ 0 };
		glGetShaderiv(m_ID, GL_INFO_LOG_LENGTH, &res);

		if (res > 0)
		{
			std::string infoLog(res, 0);
			glGetShaderInfoLog(m_ID, res, &res, &infoLog[0]);
			return infoLog;
		}
		else {
			return "";
		}
	}

	GLuint Shader::Compile(GLenum type, const char* shaderCode) {

		GLuint _id = glCreateShader(type);
		glShaderSource(_id, 1, &shaderCode, NULL);
		glCompileShader(_id);

		GLint Result = false;
		int   InfoLogLength = 0;

		glGetShaderiv(_id, GL_COMPILE_STATUS, &Result);
		if (!Result) {
			Z::ERROR() << "Shader file compilation failed " << __FILE__ << __LINE__;
		}

		glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> ErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(_id, InfoLogLength, NULL, &ErrorMessage[0]);
			Z::ERROR() << string(&ErrorMessage[0]).c_str();
		}

		return _id;

	}
	// Read the contents of a file into an array of char
	bool Shader::getFileContents(const std::string& filename, std::vector<char>& buffer)
	{
		std::ifstream file(filename.c_str(), std::ios_base::binary);
		if (file)
		{
			file.seekg(0, std::ios_base::end);
			std::streamsize size = file.tellg();
			if (size > 0)
			{
				file.seekg(0, std::ios_base::beg);
				buffer.resize(static_cast<std::size_t>(size));
				file.read(&buffer[0], size);
			}
			buffer.push_back('\0');
			return true;
		}
		else
		{
			return false;
		}
	}
}