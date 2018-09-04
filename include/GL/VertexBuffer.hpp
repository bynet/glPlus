
#pragma once


#include <functional>
#include <cstdint>
#include <Util/Noncopyable.hpp>
#include <GL/glew.h>
#include <GL/GL.hpp>
#include <Util/Mesh.hpp>
#include <Math/Vec4.hpp>
using namespace std;


namespace GL {

	/*
	Helper class for building vertex data
	*/
	class VertexDataBuffer
	{
	public:
		void Float(float v) { Bytes((uchar*)&v, sizeof(v)); }
		void Int8(int8_t v) { Bytes((uchar*)&v, sizeof(v)); }
		void Int16(int16_t v) { Bytes((uchar*)&v, sizeof(v)); }
		void Int32(int32_t v) { Bytes((uchar*)&v, sizeof(v)); }
		void Uint8(uint8_t v) { Bytes((uchar*)&v, sizeof(v)); }
		void Uint16(uint16_t v) { Bytes((uchar*)&v, sizeof(v)); }
		void Uint32(uint32_t v) { Bytes((uchar*)&v, sizeof(v)); }

		void Vec2(const Vec2& v) { Bytes((uchar*)&v, sizeof(v)); }
		void Vec3(const Vec3& v) { Bytes((uchar*)&v, sizeof(v)); }
		void Vec4(const Vec4& v) { Bytes((uchar*)&v, sizeof(v)); }

		void* Pointer() { return &data[0]; }
		size_t Size() { return data.size(); }

	private:
		std::vector<uchar> data;

		void Bytes(uchar* bytes, uint count) {
			for (uint i = 0; i < count; i++)
				data.push_back(bytes[i]);
		}
	};

	class VertexBuffer : public Noncopyable {

		GLuint m_ID{ 0 };
		void Destroy();

		VertexBuffer();
		VertexBuffer(const void* data, size_t length, BufferUsage::buffer_usage_t usage); 
		VertexBuffer( const Mesh& mesh, BufferUsage::buffer_usage_t usage, std::function<void ( const Vertex& v, VertexDataBuffer& data )> f );

	public:

		using Ptr = shared_ptr<VertexBuffer>;

		~VertexBuffer();
		VertexBuffer(VertexBuffer&& other);
		VertexBuffer& operator=(VertexBuffer&& other);
		operator GLuint() const { return m_ID; }

		static Ptr Create();
		static Ptr Create( const void* data, size_t length, BufferUsage::buffer_usage_t usage); 
		static Ptr Create( const Mesh& mesh, BufferUsage::buffer_usage_t usage, std::function<void ( const Vertex& v, VertexDataBuffer& data )> f );


		void Data(const void* data, size_t length, BufferUsage::buffer_usage_t usage);
		void SubData(const void* data, size_t offset, size_t length);
		void GetSubData(void* data, size_t offset, size_t length);

	};

}