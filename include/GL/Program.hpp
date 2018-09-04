#pragma once 

#include <GL/glew.h>
#include <GL/Shader.hpp>
#include <Util/Noncopyable.hpp>
#include <Math/Vec2.hpp>
#include <Math/Vec3.hpp>
#include <Math/Vec4.hpp>

#include <Math/Mat3.hpp>
#include <Math/Mat4.hpp>
using namespace std;

namespace GL {
	class LinkException : public std::exception
	{
	public:
		LinkException(const std::string& str) throw() : infoLog(str) {}
		~LinkException() throw() {}

		virtual const char* what() const throw()
		{
			return infoLog.c_str();
		}

	private:
		std::string infoLog;
	};

	class Program : public Noncopyable {

		GLuint m_ID{ 0 };

		Program();
		Program(const Shader& vertex);
		Program(const Shader& vertex, const Shader& fragment);
		Program(const Shader& vertex, const Shader& fragment, const Shader& geometry);

	public:

		using Ptr = shared_ptr<Program>;

		static Ptr Create(const Shader& vertex) {
			return Ptr(new Program(vertex));
		}

		static Ptr Create(const Shader& vertex, const Shader& fragment) {
			return Ptr(new Program(vertex, fragment));
		}

		static Ptr Create(const Shader& vertex, const Shader& fragment, const Shader& geometry) {
			return Ptr(new Program(vertex, fragment, geometry ));
		}


		~Program();
		Program(Program&& other);
		Program& operator=(Program&& rhs); 

		operator GLuint() const { return m_ID;};

		void Attach(const Shader& shader);
		void TransformFeedbackVaryings(const char** varyings, uint count);
		void Link();
		void Destroy();

		std::string GetInfoLog();

		Attribute GetAttribute(const std::string& name);
		Uniform GetUniform(const std::string& name);

		void SetUniform(const Uniform& uniform, int value);
		void SetUniform(const Uniform& uniform, float value);
		void SetUniform(const Uniform& uniform, const Vec2& value);
		void SetUniform(const Uniform& uniform, const Vec3& value);
		void SetUniform(const Uniform& uniform, const Vec4& value);
		void SetUniform(const Uniform& uniform, const float* values, GLuint count);

		void SetUniform(const Uniform& uniform, const Vec2* values, GLuint count);
		void SetUniform(const Uniform& uniform, const Vec3* values, GLuint count);
		void SetUniform(const Uniform& uniform, const Vec4* values, GLuint count);
		void SetUniform(const Uniform& uniform, const Mat3& value);
		void SetUniform(const Uniform& uniform, const Mat4& value);


	};



}