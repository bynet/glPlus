
#include <GL/IndexBuffer.hpp>


namespace GL {

	IndexBuffer::IndexBuffer(IndexBuffer&& other)
		:m_ID(other.m_ID)
	{
		other.m_ID = 0;
	}

	IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) {

		if (this != &other)
		{
			Destroy();
			swap(m_ID, other.m_ID);
		}

		return *this;
	}


	IndexBuffer::IndexBuffer() {
		glGenBuffers(1, &m_ID);
	}

	IndexBuffer::IndexBuffer(const GLvoid* data, GLsizei length, GLenum usage) {
		glGenBuffers(1, &m_ID);
		Data(data, length, usage);
	}

	void IndexBuffer::Destroy() {
		if (m_ID) {
			glDeleteBuffers(1, &m_ID);
			m_ID = 0;
		}
	}

	void IndexBuffer::Data(const GLvoid* data, GLsizeiptr  lenght, GLenum usage) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, lenght, data, usage);
	}

	void IndexBuffer::SubData(const GLvoid* data, GLsizeiptr offset, GLsizeiptr length) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, length, data);
	}

	void IndexBuffer::GetSubData(GLvoid* data, GLsizeiptr  offset, GLsizeiptr length) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, length, data);
	}
}

