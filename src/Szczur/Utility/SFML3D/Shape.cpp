#include "Shape.hpp"

namespace sf3d {
	Shape::Shape(size_t vertexSize) :
		_vertices(vertexSize) {
		_update();
	}

	void Shape::_update() {
		for(size_t i = 0; i < _vertices.getSize(); ++i) {
			_vertices[i].setPosition(getPointPosition(i));
			_vertices[i].setColor(getPointColor(i));
			_vertices[i].setTexCoord(getPointCoord(i));
		}
		_vertices.setPrimitveType(GL_TRIANGLE_FAN);
	}

	void Shape::draw(RenderTarget & target, RenderStates states) const {
		states.transform *= getTransform();
		target.draw(_vertices, states);
	}

	glm::vec3 Shape::getPointPosition(size_t index) const {
		/*1.0, 1.0, 1.0,
			0.0f, 1.0, 1.0,
			1.0, 1.0, 0.0f,
			0.0f, 1.0, 0.0f,
			1.0, 0.0f, 1.0,
			0.0f, 0.0f, 1.0,
			0.0f, 0.0f, 0.0f,
			1.0, 0.0f, 0.0f
			*/
		switch(index) {
			case 0: return {100.f, 100.f, 100.f};
			case 1: return {0.f, 100.f, 100.f};
			case 2: return {100.f, 100.f, 0.f};
			case 3: return {0.f, 100.f, 0.f};
			case 4: return {100.f, 0.f, 100.f};
			case 5: return {0.f, 0.f, 100.f};
			case 6: return {0.f, 0.f, 0.f};
			case 7: return {100.f, 0.f, 0.f};
		}

		return {};
	}

	glm::vec4 Shape::getPointColor(size_t /*index*/) const {
		return {1.0, 0.0, 1.0, 1.0};
	}

	glm::vec2 Shape::getPointCoord(size_t /*index*/) const {
		return {0.0, 0.0};
	}
}
