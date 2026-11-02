#pragma once

#include "GameState.hpp"
#include <string>
#include <vector>
#include <functional>

class ResourceManager;

class DialogueState : public GameState {
private:
    const ResourceManager& resources;
    std::string speakerName;
    std::vector<std::string> lines;
    size_t currentLineIndex;

    float textCharTimer;
    size_t visibleCharCount;
    std::function<void()> onCompleteCallback;

public:
    DialogueState(StateManager& manager, const ResourceManager& res, std::string speaker, std::vector<std::string> dialogueLines, std::function<void()> onComplete = nullptr);

    void handleInput(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderTarget& target) override;

    bool isOverlay() const override { return true; }
};
