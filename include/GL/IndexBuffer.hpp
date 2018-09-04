#pragma once
#include "assert.h"
#include <functional>
#include <Util/Noncopyable.hpp>
#include <GL/glew.h>

using namespace std;

namespace GL {

	class IndexBuffer : public Noncopyable {

	private:
		GLuint m_ID{ 0 };

		IndexBuffer();
		IndexBuffer(const GLvoid* data, GLsizei length, GLenum usage);
		void Destroy();

	public:
		using Ptr = shared_ptr<IndexBuffer>;
		operator GLuint() const { return m_ID; }

		IndexBuffer(IndexBuffer &&other);
		IndexBuffer& operator=(IndexBuffer&& other);
		~IndexBuffer();

		static Ptr Create() {
			return Ptr(new IndexBuffer());
		}
		static Ptr Create(const GLvoid* data, GLsizei length, GLenum usage) {
			return Ptr(new IndexBuffer(data, length, usage));
		}

		void Data(const GLvoid* data, GLsizeiptr lenght, GLenum usage);
		void SubData(const GLvoid* data, GLsizeiptr offset, GLsizeiptr length);
		void GetSubData(GLvoid* data, GLsizeiptr  offset, GLsizeiptr length);

	};

}