#include <GL/VertexArray.hpp>

using namespace std;

namespace GL {

	VertexArray::VertexArray(VertexArray &&other) 
	:m_ID(other.m_ID)
	{
		other.m_ID = 0;
	
	}

	VertexArray& VertexArray::operator=(VertexArray&& other) {

		if (this != &other)
		{
			Destroy();
			swap(m_ID, other.m_ID);
		}

		return *this;

	}
	
	void VertexArray::Destroy() {
		if (m_ID) {
			glDeleteVertexArrays(1, &m_ID);
			m_ID = 0;
		}
	}

	VertexArray::VertexArray() {
		glGenVertexArrays(1, &m_ID);
	}

	VertexArray::~VertexArray() {
		Destroy();
	}

	void VertexArray::BindAttribute(const Attribute& attribute, const VertexBuffer& buffer, Type::type_t type, uint count, uint stride, intptr_t offset)
	{
		glBindVertexArray(m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer); //check this : cihangir
		glEnableVertexAttribArray(attribute);
		glVertexAttribPointer(attribute, count, type, GL_FALSE, stride, (const GLvoid*)offset);
	}

	void VertexArray::BindElements(const VertexBuffer& elements)
	{
		glBindVertexArray(m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements);
	}

	void VertexArray::BindTransformFeedback(uint index, const VertexBuffer& buffer)
	{
		glBindVertexArray(m_ID);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, index, buffer);
	}
}
