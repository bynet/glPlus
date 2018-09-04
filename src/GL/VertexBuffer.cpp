/*
	Copyright (C) 2012 Alexander Overvoorde

	Permission is hereby granted, free of charge, to any person obtaining a copy of
	this software and associated documentation files (the "Software"), to deal in
	the Software without restriction, including without limitation the rights to
	use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
	the Software, and to permit persons to whom the Software is furnished to do so,
	subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
	FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
	COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
	IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
	CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
*/

#include <GL/VertexBuffer.hpp>
#include <vector>

namespace GL {

	VertexBuffer::VertexBuffer(VertexBuffer&& other)
		:m_ID(other.m_ID)
	{
		other.m_ID = 0;
	}

	VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other)
	{
		//ALWAYS check for self-assignment
		if (this != &other)
		{
			Destroy();
			swap(m_ID, other.m_ID);
		}
		return *this;
	}

	VertexBuffer::Ptr VertexBuffer::Create() {
		return Ptr(new VertexBuffer());
	}

	VertexBuffer::Ptr VertexBuffer::Create(const void* data, size_t length, BufferUsage::buffer_usage_t usage) {
		return Ptr(new VertexBuffer(data,length, usage));
	}

	VertexBuffer::Ptr VertexBuffer::Create(const Mesh& mesh, BufferUsage::buffer_usage_t usage, std::function<void(const Vertex& v, VertexDataBuffer& data)> f) {
		return Ptr(new VertexBuffer(mesh, usage, f));
	}

	VertexBuffer::~VertexBuffer() {
		Destroy();
	}

	void VertexBuffer::Destroy() {
		if (m_ID) {
			glDeleteBuffers(1, &m_ID);
			m_ID = 0;
		}
	}

	VertexBuffer::VertexBuffer() {
		glGenBuffers(1, &m_ID);

	}
	VertexBuffer::VertexBuffer(const void* data, size_t length, BufferUsage::buffer_usage_t usage){
		glGenBuffers(1, &m_ID);
		Data(data, length ,  usage);
	}

	VertexBuffer::VertexBuffer(const Mesh& mesh, BufferUsage::buffer_usage_t usage, std::function<void(const Vertex& v, VertexDataBuffer& data)> f)
	{
		VertexDataBuffer data;
		const Vertex* vertices = mesh.Vertices();
		uint count = mesh.VertexCount();

		for (uint i = 0; i < count; i++)
			f(vertices[i], data);

		glGenBuffers(1, &m_ID);
		Data(data.Pointer(), data.Size(), usage);
	}

	void VertexBuffer::Data( const void* data, size_t length, GL::BufferUsage::buffer_usage_t usage ) {
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, length , data, usage);
	}

	void VertexBuffer::SubData( const void* data, size_t offset, size_t length ){
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferSubData(GL_ARRAY_BUFFER, offset, length, data);
	}

	void VertexBuffer::GetSubData( void* data, size_t offset, size_t length ) {
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glGetBufferSubData(GL_ARRAY_BUFFER, offset, length, data);
	}

}
