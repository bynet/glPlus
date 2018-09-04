#pragma once

#include <GL/GL.hpp>
#include <GL/glew.h>
#include <Util/Noncopyable.hpp>
#include <GL/Texture.hpp>

using namespace std;
namespace GL {

	class FramebufferException : public std::exception
	{
		virtual const char* what() const throw()
		{
			return "Framebuffer could not be created!";
		}
	};

	class FrameBuffer : public Noncopyable {

		GLuint m_ID{ 0 };
		Texture::Ptr texColor;
		Texture::Ptr texDepth;
		FrameBuffer(uint width, uint height, uchar color = 32, uchar depth = 24);
		void Destroy();

	public:
		~FrameBuffer();

		using Ptr = shared_ptr<FrameBuffer>;

		FrameBuffer(FrameBuffer&& other);
		FrameBuffer& operator=(FrameBuffer&& other);
		operator GLuint() const { return m_ID; }

		static Ptr Create(uint width , uint height , uchar color = 32 , uchar depth = 24 );
	


	};




}