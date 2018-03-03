
#include "Szczur/Debug/Logger.hpp"

#include <iostream>
namespace rat {
    template<typename Tuple>
    Dialog::Dialog(Tuple&& tuple, const std::string& file) :
    Module(tuple),
    _dialogGUI(getModule<GUI>()) {
        
        auto& gui = getModule<GUI>();
        gui.addAsset<Json>(file);
        gui.addAsset<sf::Texture>("data/dial_back.png");
        gui.addAsset<sf::Font>("data/consolab.ttf");
        
        _dialogGUI.create();
        /*

        _interface = gui.addInterface(file);
        TextAreaWidget* area = reinterpret_cast<TextAreaWidget*>(_interface->get("_root")->get("background")->get("area"));

        _dialogManager.load("data/dialog");
       // area->setString(_dialogManager.play(2u));

        _interface->get("_root")->get("button1")->setCallback(Widget::CallbackType::onRelease, [this, area](Widget*){
            area->setString(_dialogManager.play(1u));
        });
        _interface->get("_root")->get("button2")->setCallback(Widget::CallbackType::onRelease, [this, area](Widget*){
            area->setString(_dialogManager.play(2u));
        });
        _interface->get("_root")->get("button3")->setCallback(Widget::CallbackType::onRelease, [this, area](Widget*){
            area->setString(_dialogManager.play(3u));
        });*/

    
        Options *options1 = new Options;
        options1->setRunners(1u);
        options1->addOption(
            "4",
            nullptr,
            4u,
            [](){std::cout << "asdasdasd\n";}
        );
        options1->addOption(
            "3",
            nullptr,
            3u,
            nullptr
        );
        options1->addOption(
            "2",
            nullptr,
            2u,
            nullptr
        );

        

        Options *options2 = new Options;
        options2->setRunners(4u, 3u, 2u);
        options2->addOption(
            "Wezwanie",
            nullptr,
            1u,
            nullptr
        );

        auto* mngr = load("data/dialog");

        mngr->addOptions(options1, options2);

        mngr->startWith(1u);
        mngr->play();
    }
}