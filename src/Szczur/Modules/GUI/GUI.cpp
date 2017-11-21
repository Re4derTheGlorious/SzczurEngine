#include "GUI.hpp"

#include <iostream>

namespace rat {
    void GUI::init() {
        Widget* test = _root.add(new Widget());
        test->setCallback(Widget::CallbackType::onHover, [](Widget* owner) {
            std::cout << ".";
        });
        test->setCallback(Widget::CallbackType::onHoverIn, [](Widget* owner) {
            std::cout << "HoveredIn\n";
        });
        test->setCallback(Widget::CallbackType::onHoverOut, [](Widget* owner) {
            std::cout << "\nHoveredOut\n\n";
        });
        test->setCallback(Widget::CallbackType::onPress, [](Widget* owner) {
            std::cout << "\nPRESSED<==============\n";
        });
        test->setCallback(Widget::CallbackType::onHeld, [](Widget* owner) {
            std::cout << ",";
        });
        test->setCallback(Widget::CallbackType::onRelease, [](Widget* owner) {
            std::cout << "\nRELEASED<==============\n";
        });
        test->setPosition({255.f, 120.f});

    }

    void GUI::input(const sf::Event& event) {
        if(
            event.type == sf::Event::MouseButtonPressed || 
            event.type == sf::Event::MouseButtonReleased || 
            event.type == sf::Event::MouseMoved ||
            event.type == sf::Event::TextEntered
        ) {
            _root.input(event);
        }
    }

    void GUI::update(float deltaTime) {
        _root.update(deltaTime);
    }

    void GUI::render() {
        getModule<Canvas>().draw(Canvas::LayerId::GUI, _root);
    }
}