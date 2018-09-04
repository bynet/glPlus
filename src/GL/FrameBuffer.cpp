#include <GL/FrameBuffer.hpp>

namespace GL {

#define PUSHSTATE() GLint restoreId; glGetIntegerv( GL_DRAW_FRAMEBUFFER_BINDING, &restoreId );
#define POPSTATE() glBindFramebuffer( GL_DRAW_FRAMEBUFFER, restoreId );

	FrameBuffer::FrameBuffer(uint width, uint height, uchar color , uchar depth ) {
		PUSHSTATE()

			// Determine appropriate formats
		InternalFormat::internal_format_t colorFormat;
		if (color == 24) colorFormat = InternalFormat::RGB;
		else if (color == 32) colorFormat = InternalFormat::RGBA;
		else throw FramebufferException();

		InternalFormat::internal_format_t depthFormat;
		if (depth == 8) depthFormat = InternalFormat::DepthComponent;
		else if (depth == 16) depthFormat = InternalFormat::DepthComponent16;
		else if (depth == 24) depthFormat = InternalFormat::DepthComponent24;
		else if (depth == 32) depthFormat = InternalFormat::DepthComponent32F;
		else throw FramebufferException();

		// Create FBO		
		//gc.Create( obj, glGenFramebuffers, glDeleteFramebuffers );
		glGenFramebuffers(1, &m_ID);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_ID );

		// Create texture to hold color buffer
		texColor = Texture::Create();
		texColor->Image2D(0, DataType::UnsignedByte, Format::RGBA, width, height, colorFormat);
		texColor->SetWrapping(GL::Wrapping::ClampEdge, GL::Wrapping::ClampEdge);
		texColor->SetFilters(GL::Filter::Linear, GL::Filter::Linear);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *texColor, 0);

		// Create renderbuffer to hold depth buffer
		if (depth > 0) {
			texDepth = Texture::Create();
			glBindTexture(GL_TEXTURE_2D, *texDepth);
			glTexImage2D(GL_TEXTURE_2D, 0, depthFormat, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
			texDepth->SetWrapping(GL::Wrapping::ClampEdge, GL::Wrapping::ClampEdge);
			texDepth->SetFilters(GL::Filter::Nearest, GL::Filter::Nearest);
			glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *texDepth, 0);
		}

		// Check
		if (glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			throw FramebufferException();

		POPSTATE()
	}

	FrameBuffer::~FrameBuffer() {
		Destroy();
	}

	void FrameBuffer::Destroy() {
		glDeleteFramebuffers(1, &m_ID);
	}

	FrameBuffer::FrameBuffer(FrameBuffer&& other)
		:m_ID(other.m_ID) 
	{
		other.m_ID = 0;
		*texColor = move(*other.texColor);
		*texDepth = move(*other.texDepth);

	}

	FrameBuffer& FrameBuffer::operator=(FrameBuffer&& other) {

		if (this != &other) {
			Destroy();
			swap(m_ID, other.m_ID);
			*texColor = move(*other.texColor);
			*texDepth = move(*other.texDepth);

		}
		return *this;
	}

	FrameBuffer::Ptr FrameBuffer::Create(uint width, uint height, uchar color, uchar depth) {
		return Ptr(new FrameBuffer(width, height, color, depth));
	}



}