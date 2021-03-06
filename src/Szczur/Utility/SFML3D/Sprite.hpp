#pragma once

#include "Transformable.hpp"
#include "Drawable.hpp"
#include "RenderStates.hpp"
#include "VertexArray.hpp"

namespace sf3d {
	class RenderTarget;
	class Texture;

	class Sprite : public Transformable, public Drawable {
	public:
		Sprite();

		void setTexture(Texture* texture);

		virtual void draw(RenderTarget& target, RenderStates states) const override;
	private:
		Texture* _texture{nullptr};
		VertexArray _vertices{4u};
	};
}