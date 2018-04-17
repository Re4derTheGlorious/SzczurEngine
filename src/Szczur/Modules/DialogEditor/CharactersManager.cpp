#include "CharactersManager.hpp"

#include <fstream>
#include <experimental/filesystem>

#include <nlohmann/json.hpp>

#include "Szczur/Modules/FileSystem/FileDialog.hpp"
#include "Szczur/Config.hpp"

namespace rat
{
    CharactersManager::CharactersManager(DLGEditor::TextContainer_t& dialogParts)
        : _dialogParts(dialogParts)
    {

    }

    void CharactersManager::update()
    {
        ImGui::Begin("Characters Manager");
            for(unsigned int i = 0; i < _charactersName.size(); ++i) {
                auto name =  _charactersName.begin() + i;
                auto imagePath = _charactersImagePath.begin() + i;

                ImGui::PushID(i);

                std::string clipText = (ImGui::GetClipboardText() != nullptr) ? ImGui::GetClipboardText() : "";
                size_t clipSize = clipText.length();  
                size_t size = name->length() + clipSize + 30;
                char *newText = new char[size] {};
                strncpy(newText, name->c_str(), size);

                ImGui::PushItemWidth(ImGui::GetWindowWidth() - 100);
                ImGui::InputText("##Characters Name Input", newText, size);
                ImGui::PopItemWidth();

                *name = newText;
                delete[] newText;

                ImGui::SameLine();
                if (ImGui::Button("Load##Characters Manager")) {
                    auto currentPath = std::experimental::filesystem::current_path().string();
                    auto path = FileDialog::getOpenFileName("", currentPath, "Images (*.png, *.jpg)|*.png;*.jpg");
                    size_t start = path.find(currentPath);
                    if (start != -1) {
                        *imagePath = path.substr(currentPath.length() + 1, path.length() - currentPath.length() - 1);
                    } 
                    else {
                        *imagePath = path;
                    }
                }

                ImGui::SameLine(); 
                if (ImGui::Button("-##Characters Manager", ImVec2(30, 22))) {
                    _charactersName.erase(name);
                    _charactersImagePath.erase(imagePath);

                    for(auto& majors : _dialogParts) {
                        for(auto& minor : majors.second) {
                            for (auto& it : minor.second->chosenCharacter) {
                                if (i < static_cast<unsigned>(it)) {
                                    --it;
                                }
                            }
                        }
                    }
                }

                ImGui::PopID();
            }
            if (ImGui::Button("+##Characters Manager", ImVec2(30, 27))) {
                _charactersName.push_back("");
                _charactersImagePath.push_back("");
            };
        ImGui::End();
    }

    void CharactersManager::clear()
    {
        _charactersName.clear();
        _charactersImagePath.clear();
    }

    std::vector<std::string>& CharactersManager::getNamesContainer()
    {
        return _charactersName;
    }

    std::vector<std::string>& CharactersManager::getImagePathsContainer()
    {
        return _charactersImagePath;
    }

    void CharactersManager::load(const std::string& path)
    {
        _charactersName.clear();
        _charactersImagePath.clear();

        nlohmann::json json;

        std::ifstream file(path);
        if(file.is_open()) {
            file >> json;
        }
        file.close();

        for (auto it = json.begin(); it != json.end(); ++it)
        {
            _charactersName.push_back(it.key());
            _charactersImagePath.push_back(it.value() == nullptr ? "" : it.value());
        }

    }

    void CharactersManager::save(const std::string& path)
    {
        nlohmann::json json;

        for(unsigned int i = 0; i < _charactersName.size(); ++i) {
            json[_charactersName[i]] = _charactersImagePath[i];
        }

        std::ofstream file(path, std::ios::trunc);
        if(file.is_open()) {
            file << json;
        }
        file.close();
    }
    
}