#include "Window.hpp"

/** @file Window.cpp
 ** @description Implementation file with main class of the Window module.
 ** @author Patryk (Stritch)
 ** @author Patryk (PsychoX) Ludwikowski <psychoxivi+basementstudios@gmail.com>
 **/

#include <string>

#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include "Szczur/Utility/SFML3D/Drawable.hpp"
#include "Szczur/Utility/SFML3D/RenderStates.hpp"
#include "Szczur/Utility/SFML3D/Vertex.hpp"
#include "Szczur/Utility/SFML3D/Shader.hpp"
#include "Szczur/Utility/SFML3D/ShaderProgram.hpp"
#include "Szczur/Utility/Logger.hpp"

namespace rat
{

/* Properties */
/// Window
Window::Window_t& Window::getWindow()
{
	return this->window;
}
const Window::Window_t& Window::getWindow() const
{
	return this->window;
}

/// VideoMode
sf::VideoMode Window::getVideoMode() const
{
	return this->videoMode;
}
void Window::setVideoMode(const sf::VideoMode& mode)
{
	this->videoMode = mode;
	LOG_INFO("VideoMode: { width: ", this->videoMode.width,  ", height: ", this->videoMode.height, ", bitsPerPixel: ", this->videoMode.bitsPerPixel, " }");

	// Recreate and reset properties
	this->getWindow().create(this->videoMode, this->title);
	this->getWindow().setTitle(this->title);
	this->getWindow().setFramerateLimit(this->framerateLimit);
}

/// FrameRate
unsigned int Window::getFramerateLimit() const
{
	return this->framerateLimit;
}
void Window::setFramerateLimit(const unsigned int limit)
{
	this->framerateLimit = limit;
	LOG_INFO("framerateLimit: " + this->framerateLimit);

	this->getWindow().setFramerateLimit(this->framerateLimit);
}

/// Title
const std::string& Window::getTitle() const
{
	return this->title;
}
void Window::setTitle(const std::string& title)
{
	this->title = title;
	LOG_INFO("Window title: " + this->title);

	this->getWindow().setTitle(this->title);
}



/* Operators */
/// Constructors
Window::Window()
{
	LOG_INFO("Initializing Window module");
	this->init();
	LOG_INFO("Module Window initialized");
}
/// Destructor
Window::~Window()
{
	LOG_INFO("Module Window destructed");
}



/* Methods*/
/// init
void Window::init()
{
	// Create
	// @todo ? load videomode from settings
	this->setVideoMode(this->videoMode);

	// Shaders
	sf3d::FShader frag;
	frag.loadFromFile("Assets/Shaders/default.frag");

	sf3d::VShader vert;
	vert.loadFromFile("Assets/Shaders/default.vert");

	sf3d::ShaderProgram* program = new sf3d::ShaderProgram(); // @warn Leak - bo kiedys to i tak przez ShaderManager czy coś trzeba zrobić.
	program->linkShaders(frag, vert);
	this->getWindow().setProgram(program);
}

/// render
void Window::render()
{
	this->getWindow().display();
}

/// clear
void Window::clear(const sf::Color& color)
{
	this->getWindow().clear((float)color.r, (float)color.g, (float)color.b , (float)color.a, GL_COLOR_BUFFER_BIT);
	//@todo: Fix it.
}

/// GL states
void Window::pushGLStates()
{
	this->getWindow().pushGLStates();
}
void Window::popGLStates()
{
	this->getWindow().popGLStates();
}

/// draw
// 2D
void Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states)
{
	this->getWindow().draw(drawable, states);
}
void Window::draw(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type, const sf::RenderStates& states)
{
	this->getWindow().draw(vertices, vertexCount, type, states);
}
// 3D
void Window::draw(const sf3d::Drawable& drawable, const sf3d::RenderStates& states)
{
	this->getWindow().draw(drawable, states);
}
void Window::draw(const sf3d::Drawable& drawable)
{
	this->getWindow().draw(drawable);
}
void Window::draw(const sf3d::VertexArray& vertices, const sf3d::RenderStates& states)
{
	this->getWindow().draw(vertices, states);
}
void Window::draw(const sf3d::VertexArray& vertices)
{
	this->getWindow().draw(vertices);
}

}
