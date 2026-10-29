#pragma once

#include "GameState.hpp"
#include "Monster.hpp"
#include <string>
#include <vector>
#include <memory>

class Player;
class ResourceManager;

enum class BattlePhase {
    Intro,
    ActionSelect,
    MoveSelect,
    ItemSelect,
    ExecutingPlayerMove,
    ExecutingEnemyMove,
    Capturing,
    CaughtSuccess,
    CaughtFailed,
    Victory,
    Defeat,
    RunAway
};

class BattleState : public GameState {
private:
    Player& player;
    std::shared_ptr<Monster> playerMonster;
    std::shared_ptr<Monster> enemyMonster;
    const ResourceManager& resources;
    bool isBossBattle;

    BattlePhase phase;
    std::string battleLog;
    float phaseTimer;

    int selectedMoveIndex;

    // Battle Animation States
    ElementType currentAttackType;
    bool isPlayerAttacking;
    bool isEnemyAttacking;
    float attackAnimTime;
    std::string floatingDamageText;
    float floatingTextTimer;
    sf::Vector2f floatingTextPos;

    // Capture Ball Animation
    float catchAnimTime;
    bool catchWillSucceed;

    void executePlayerAttack(size_t moveIndex);
    void executeEnemyAttack();
    void attemptCatch();
    void handleVictory();
    void handleDefeat();

    void drawHealthBar(sf::RenderTarget& target, float x, float y, float width, float height, int currentHp, int maxHp);
    void drawAttackEffects(sf::RenderTarget& target, sf::Vector2f targetPos, ElementType type, float animTime);
    void drawCatchAnimation(sf::RenderTarget& target);

public:
    BattleState(StateManager& manager, Player& player, std::shared_ptr<Monster> wildMonster, const ResourceManager& res, bool isBoss = false);

    void handleInput(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderTarget& target) override;
};
