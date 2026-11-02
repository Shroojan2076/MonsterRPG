#include "DialogueState.hpp"
#include "StateManager.hpp"
#include "ResourceManager.hpp"

DialogueState::DialogueState(StateManager& manager, const ResourceManager& res, std::string speaker, std::vector<std::string> dialogueLines, std::function<void()> onComplete)
    : GameState(manager),
      resources(res),
      speakerName(std::move(speaker)),
      lines(std::move(dialogueLines)),
      currentLineIndex(0),
      textCharTimer(0.0f),
      visibleCharCount(0),
      onCompleteCallback(std::move(onComplete)) {
    if (lines.empty()) {
        lines.push_back("...");
    }
}

void DialogueState::handleInput(const sf::Event& event) {
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::E ||
            keyPressed->code == sf::Keyboard::Key::Space ||
            keyPressed->code == sf::Keyboard::Key::Enter) {

            // If text is still typing, finish typing instantly
            if (visibleCharCount < lines[currentLineIndex].length()) {
                visibleCharCount = lines[currentLineIndex].length();
            } else {
                // Advance to next line
                currentLineIndex++;
                visibleCharCount = 0;
                textCharTimer = 0.0f;

                if (currentLineIndex >= lines.size()) {
                    stateManager.popState();
                    if (onCompleteCallback) {
                        onCompleteCallback();
                    }
                }
            }
        }
    }
}

void DialogueState::update(float deltaTime) {
    if (currentLineIndex < lines.size()) {
        if (visibleCharCount < lines[currentLineIndex].length()) {
            textCharTimer += deltaTime;
            if (textCharTimer >= 0.025f) {
                textCharTimer = 0.0f;
                visibleCharCount++;
            }
        }
    }
}

void DialogueState::render(sf::RenderTarget& target) {
    sf::View originalView = target.getView();
    target.setView(target.getDefaultView()); // Render in screen pixel coordinates (960x640)

    // Dialogue Box
    sf::RectangleShape box({880.0f, 150.0f});
    box.setPosition({40.0f, 450.0f});
    box.setFillColor(sf::Color(15, 20, 35, 240));
    box.setOutlineColor(sf::Color(230, 200, 100, 255));
    box.setOutlineThickness(3.0f);
    target.draw(box);

    // Speaker Name Tag
    if (!speakerName.empty()) {
        sf::RectangleShape tag({220.0f, 38.0f});
        tag.setPosition({40.0f, 404.0f});
        tag.setFillColor(sf::Color(35, 50, 95, 250));
        tag.setOutlineColor(sf::Color(230, 200, 100, 255));
        tag.setOutlineThickness(2.0f);
        target.draw(tag);

        sf::Text nameText(resources.getFont(), speakerName, 20);
        nameText.setFillColor(sf::Color(255, 235, 140, 255));
        nameText.setPosition({52.0f, 408.0f});
        target.draw(nameText);
    }

    // Typewriter Dialogue Content
    if (currentLineIndex < lines.size()) {
        std::string currentVisible = lines[currentLineIndex].substr(0, visibleCharCount);
        sf::Text dialogueText(resources.getFont(), currentVisible, 22);
        dialogueText.setFillColor(sf::Color::White);
        dialogueText.setPosition({60.0f, 475.0f});
        target.draw(dialogueText);
    }

    // Prompt icon
    sf::Text promptText(resources.getFont(), "[Space / E] Next >", 16);
    promptText.setFillColor(sf::Color(180, 200, 220, 220));
    promptText.setPosition({750.0f, 565.0f});
    target.draw(promptText);

    target.setView(originalView); // Restore world view
}
