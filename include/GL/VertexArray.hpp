#pragma once

#include <Util/Noncopyable.hpp>
#include <iostream>
#include <GL/glew.h>
#include <GL/GL.hpp>
#include <GL/VertexBuffer.hpp>

using namespace std;

namespace GL {

	class VertexArray : public Noncopyable {
	private:
		GLuint m_ID{ 0 };
		VertexArray();
		void Destroy();

	public:

		using Ptr = shared_ptr<VertexArray>;
		operator GLuint() const { return m_ID; }
		VertexArray(VertexArray &&other);
		VertexArray& operator=(VertexArray&& other);
		~VertexArray();

		static Ptr Create() {
//			struct make_shared_enabler : public VertexArray{};
//			return make_shared<make_shared_enabler>();
			return Ptr(new VertexArray());
		}

		void BindAttribute(const Attribute& attribute, const VertexBuffer& buffer, Type::type_t type, uint count, uint stride, intptr_t offset);
		void BindElements(const VertexBuffer& elements);
		void BindTransformFeedback(uint index, const VertexBuffer& buffer);

	};

}

