#pragma once

#include <variant>
#include <fstream>
#include <boost/container/flat_map.hpp>
#include <SFML/Graphics.hpp>

#include "Szczur/Utility/Logger.hpp"
#include "Szczur/Utility/Convert/Hash.hpp"

namespace rat {
    template<typename... Ts>
    class GuiAssetsManager {
    public:
        using Variant_t = std::variant<Ts...>;
        using Assets_t = boost::container::flat_map<Hash32_t, Variant_t*>;

        GuiAssetsManager();
        ~GuiAssetsManager();
        
        template<typename T>
        void loadFromFile(const std::string& path);

        template<typename T>
        T* get(const std::string& path) const;

    private:
        Assets_t _assets;
    };

    using BasicGuiAssetsManager = GuiAssetsManager<sf::Texture, sf::Font>;
}

#include "GuiAssetsManager.tpp"