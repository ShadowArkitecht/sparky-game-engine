/*
====================
CPP Includes
====================
*/
#include <vector>							// Container for the buffers of the frame buffer.
/*
====================
Class Includes
====================
*/
#include <sparky\rendering\gbuffer.hpp>		// Class definition.
#include <sparky\core\window.hpp>			// Generating the buffer to the size of the Window.

namespace sparky
{
	/*
	====================
	Ctor and Dtor
	====================
	*/
	////////////////////////////////////////////////////////////
	GBuffer::GBuffer(void)
		: m_fbo(0), m_textures(), m_depth(0)
	{
		m_textures.fill(0);
	}

	////////////////////////////////////////////////////////////
	GBuffer::~GBuffer(void)
	{
		glDeleteTextures(MAX_AMOUNT, &m_textures[0]);

		if (m_fbo)
		{
			glDeleteFramebuffers(1, &m_fbo);
		}
	}

	/*
	====================
	Methods
	====================
	*/
	////////////////////////////////////////////////////////////
	bool GBuffer::generate(void)
	{
		glGenFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		std::vector<GLuint> buffers;

		auto addTexture = [&buffers](GLuint& texture, GLuint attachment, GLenum internalFormat, GLenum format, GLenum type)
		{
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, Window::getMain().getSize().x, Window::getMain().getSize().y, 0, format, type, NULL);

			glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture, 0);

			if (attachment != GL_DEPTH_ATTACHMENT)
			{
				buffers.push_back(attachment);
			}
		};

		// Use the lambda to generate the information about the different frame buffer textures.
		addTexture(m_textures[POSITION], GL_COLOR_ATTACHMENT0, GL_RGB32F, GL_RGB, GL_FLOAT);
		addTexture(m_textures[NORMAL],   GL_COLOR_ATTACHMENT1, GL_RGB32F, GL_RGB, GL_FLOAT);
		addTexture(m_textures[DIFFUSE],  GL_COLOR_ATTACHMENT2, GL_RGB32F, GL_RGB, GL_FLOAT);

		// Draws the buffers set by the textures.
		glDrawBuffers(buffers.size(), &buffers[0]);
		// Generates and binds the depth buffer 
		glGenRenderbuffers(1, &m_depth);
		glBindRenderbuffer(GL_RENDERBUFFER, m_depth);
		// Sets the information of the depth buffer
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, Window::getMain().getSize().x, Window::getMain().getSize().y);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth);
		// Checks to see if the frame buffer initialised correctly without errors
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			return false;
		}
		// Unbinds the frame buffer by default so it doesn't effect any renderable objects
		this->unbindTextures();
		this->unbind();

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

		return true;
	}

	////////////////////////////////////////////////////////////
	void GBuffer::bind(void) const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	}

	////////////////////////////////////////////////////////////
	void GBuffer::unbind(void) const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, NULL);
	}

	////////////////////////////////////////////////////////////
	void GBuffer::bindTextures(void) const
	{
		for (unsigned int i = 0; i < MAX_AMOUNT; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_textures.at(i));
		}
	}

	////////////////////////////////////////////////////////////
	void GBuffer::unbindTextures(void) const
	{
		glBindTexture(GL_TEXTURE_2D, NULL);
	}

}//namespace sparky