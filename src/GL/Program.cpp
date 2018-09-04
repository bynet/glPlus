#include <GL/Program.hpp>


using namespace std;

namespace GL {


	Program::Program() {
		m_ID = glCreateProgram();
	}

	Program::Program(const Shader& vertexShader) {
		m_ID = glCreateProgram();
		Attach(vertexShader);
		Link();
		glUseProgram(m_ID);
	}

	Program::Program(const Shader& vertex, const Shader& fragment) {
		m_ID = glCreateProgram();
		Attach(vertex);
		Attach(fragment);
		Link();
		glUseProgram(m_ID);
	}

	Program::Program(const Shader& vertex, const Shader& fragment, const Shader& geometry) {
		m_ID = glCreateProgram();
		Attach(vertex);
		Attach(fragment);
		Attach(geometry);
		Link();
		glUseProgram(m_ID);
	}

	Program::Program(Program&& other)
		:m_ID(other.m_ID)
	{
		other.m_ID = 0 ;
	}
	
	Program& Program::operator=(Program&& rhs) {

		if (this != &rhs) {
			Destroy();
			swap(m_ID, rhs.m_ID);
		}

		return *this;
	}

	Program::~Program() {
		Destroy();
	}

	void Program::Destroy() {
		glDeleteProgram(m_ID);
	}

	void Program::Attach(const Shader& shader) {
		glAttachShader(m_ID, shader);
	}
	void Program::TransformFeedbackVaryings(const char** varyings, uint count) {
		glTransformFeedbackVaryings(m_ID, count, varyings, GL_INTERLEAVED_ATTRIBS);
	}

	void Program::Link() {
		GLint res;

		glLinkProgram(m_ID);
		glGetProgramiv(m_ID, GL_LINK_STATUS, &res);

		if (res == GL_FALSE)
			throw LinkException(GetInfoLog());
	}


	string Program::GetInfoLog() {
		GLint res;
		glGetProgramiv(m_ID, GL_INFO_LOG_LENGTH, &res);

		if (res > 0)
		{
			std::string infoLog(res, 0);
			glGetProgramInfoLog(m_ID, res, &res, &infoLog[0]);
			return infoLog;
		}
		else {
			return "";
		}
	}

	Attribute Program::GetAttribute(const std::string& name) {
		return glGetAttribLocation(m_ID, name.c_str());
	}

	Uniform Program::GetUniform(const std::string& name) {
		return glGetUniformLocation(m_ID, name.c_str());
	}

	void Program::SetUniform(const Uniform& uniform, int value)
	{
		glUniform1i(uniform, value);
	}

	void Program::SetUniform(const Uniform& uniform, float value)
	{
		glUniform1f(uniform, value);
	}

	void Program::SetUniform(const Uniform& uniform, const Vec2& value)
	{
		glUniform2f(uniform, value.X, value.Y);
	}

	void Program::SetUniform(const Uniform& uniform, const Vec3& value)
	{
		glUniform3f(uniform, value.X, value.Y, value.Z);
	}

	void Program::SetUniform(const Uniform& uniform, const Vec4& value)
	{
		glUniform4f(uniform, value.X, value.Y, value.Z, value.W);
	}

	void Program::SetUniform(const Uniform& uniform, const float* values, GLuint count)
	{
		glUniform1fv(uniform, count, values);
	}

	void Program::SetUniform(const Uniform& uniform, const Vec2* values, GLuint count)
	{
		glUniform2fv(uniform, count, (float*)values);
	}

	void Program::SetUniform(const Uniform& uniform, const Vec3* values, GLuint count)
	{
		glUniform3fv(uniform, count, (float*)values);
	}

	void Program::SetUniform(const Uniform& uniform, const Vec4* values, GLuint count)
	{
		glUniform4fv(uniform, count, (float*)values);
	}

	void Program::SetUniform(const Uniform& uniform, const Mat3& value)
	{
		glUniformMatrix3fv(uniform, 1, GL_FALSE, value.m);
	}

	void Program::SetUniform(const Uniform& uniform, const Mat4& value)
	{
		glUniformMatrix4fv(uniform, 1, GL_FALSE, value.m);
	}


}