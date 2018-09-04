#pragma once
#include <GL/glew.h>
#include <stdexcept>

using namespace std;

namespace GL{
	typedef unsigned char uchar;
	typedef unsigned short ushort;
	typedef unsigned int uint;
	typedef unsigned long ulong;

	namespace Type
	{
		enum type_t
		{
			Byte = GL_BYTE,
			UnsignedByte = GL_UNSIGNED_BYTE,
			Short = GL_SHORT,
			UnsignedShort = GL_UNSIGNED_SHORT,
			Int = GL_INT,
			UnsignedInt = GL_UNSIGNED_INT,
			Float = GL_FLOAT,
			Double = GL_DOUBLE
		};
	};

	namespace BufferUsage
	{
		enum buffer_usage_t
		{
			StreamDraw = GL_STREAM_DRAW,
			StreamRead = GL_STREAM_READ,
			StreamCopy = GL_STREAM_COPY,
			StaticDraw = GL_STATIC_DRAW,
			StaticRead = GL_STATIC_READ,
			StaticCopy = GL_STATIC_COPY,
			DynamicDraw = GL_DYNAMIC_DRAW,
			DynamicRead = GL_DYNAMIC_READ,
			DynamicCopy = GL_DYNAMIC_COPY
		};
	}


	typedef GLint Attribute;
	typedef GLint Uniform;

	using ID = GLuint;
	using INDEX = GLint;
	using COUNT = GLint;
	using SIZE = GLsizei;

};