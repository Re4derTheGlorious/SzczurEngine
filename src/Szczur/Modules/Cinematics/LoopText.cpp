#include "Szczur/Modules/Cinematics/LoopText.hpp"

LoopText::LoopText(callme callback,const char * text,unsigned int size)
{  
    func = callback;
    m_text.setCharacterSize(size);
    m_text.setString(text);
    m_set = false;
}

bool LoopText::isSet()
{
    return m_set;
}

void LoopText::set(bool val)
{
    m_set=val;
}

void LoopText::setFont(sf::Font &font)
{
    m_text.setFont(font);
}

void LoopText::setCharacterSize(const unsigned int &size)
{
    m_text.setCharacterSize(size);
}

void LoopText::setSize(const sf::Vector2f &vec)
{
    m_text.setScale(vec);
}

void LoopText::setPosition(const sf::Vector2f &vec)
{
    m_text.setPosition(vec);
}

void LoopText::draw()
{
    getModule<rat::Window>().getWindow().draw(m_text);
}

void LoopText::setColor(const sf::Color &color)
{
    m_text.setColor(color);
}

void LoopText::callEvent()
{
    func();
}