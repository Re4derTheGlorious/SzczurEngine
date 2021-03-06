#include "View.hpp"
namespace sf3d {
	View::View(float factor, const glm::vec3 & center) :
	_factor(factor),
	_center(center*factor) {

	}

	void View::create(float factor, const glm::vec3& center) {
		_factor = factor;
		_center = center*factor;
	}

	void View::move(const glm::vec3 & offset) {
		_center += offset;
	}

	void View::rotate(const glm::vec3 & direction) {
		_rotation += direction;
	}

	void View::setCenter(const glm::vec3 & offset) {
		_center = offset;
	}

	const glm::vec3 & View::getCenter() const {
		return _center;
	}

	void View::setRotation(const glm::vec3 & direction) {
		_rotation = direction;
	}

	const glm::vec3 & View::getRotation() const {
		return _rotation;
	}

	Transform View::getTransform() const {
		Transform transform;
		transform.rotate(glm::radians(_rotation.x), {1.f, 0.f, 0.f});
		transform.rotate(glm::radians(_rotation.y), {0.f, 1.f, 0.f});
		transform.rotate(glm::radians(_rotation.z), {0.f, 0.f, 1.f});
		transform.translate(-(_center*_factor));
		return transform;

	}
}
