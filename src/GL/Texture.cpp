#include <GL/Texture.hpp>

#define PUSHSTATE() GLint restoreId; glGetIntegerv( GL_TEXTURE_BINDING_2D, &restoreId );
#define POPSTATE() glBindTexture( GL_TEXTURE_2D, restoreId );

namespace GL {

	Texture::Texture() {
		glGenTextures(1, &m_ID);
	}

	void Texture::Destroy() {

		glDeleteTextures(1, &m_ID);
	}

	Texture::Texture(const Image& image, InternalFormat::internal_format_t internalFormat ) {

		PUSHSTATE();

		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, image.GetWidth(), image.GetHeight(), 0, Format::RGBA, DataType::UnsignedByte, image.GetPixels());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		POPSTATE();

	}

	Texture::Ptr Texture::Create() {
		return Ptr(new Texture());
	}

	Texture::Ptr Texture::Create(const Image& image, InternalFormat::internal_format_t internalFormat) {
		return Ptr(new Texture(image, internalFormat));
	}


	Texture::Texture(Texture&& other) 
		:m_ID(other.m_ID)
	{
		other.m_ID = 0;
	}



	Texture& Texture::operator=(Texture&& other) {
		if (this != &other)
		{
			Destroy();
			swap(m_ID, other.m_ID);
		}

		return *this;
	}


	void Texture::Image2D(const GLvoid* data, DataType::data_type_t type, Format::format_t format, uint width, uint height, InternalFormat::internal_format_t internalFormat)
	{
		PUSHSTATE()

		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, data);

		POPSTATE()
	}

	void Texture::SetWrapping(Wrapping::wrapping_t s)
	{
		PUSHSTATE()

		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);

		POPSTATE()
	}


	void Texture::Bind(uchar unit)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	void Texture::SetWrapping(Wrapping::wrapping_t s, Wrapping::wrapping_t t)
	{
		PUSHSTATE()

		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t);

		POPSTATE()
	}

	void Texture::SetWrapping(Wrapping::wrapping_t s, Wrapping::wrapping_t t, Wrapping::wrapping_t r)
	{
		PUSHSTATE()

		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, r);

		POPSTATE()
	}

	void Texture::SetFilters(Filter::filter_t min, Filter::filter_t mag)
	{
		PUSHSTATE()

		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);

		POPSTATE()
	}

	void Texture::SetBorderColor(const Color& color)
	{
		PUSHSTATE()

		glBindTexture(GL_TEXTURE_2D, m_ID);
		float col[4] = { color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, col);

		POPSTATE()
	}

	void Texture::GenerateMipmaps()
	{
		PUSHSTATE()

		glBindTexture(GL_TEXTURE_2D, m_ID);
		glGenerateMipmap(GL_TEXTURE_2D);

		POPSTATE()
	}


}