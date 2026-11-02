#include "BattleState.hpp"
#include "StateManager.hpp"
#include "Player.hpp"
#include "ResourceManager.hpp"
#include <algorithm>
#include <cmath>
#include <random>

BattleState::BattleState(StateManager& manager, Player& player, std::shared_ptr<Monster> wildMonster, const ResourceManager& res, bool isBoss)
    : GameState(manager),
      player(player),
      enemyMonster(std::move(wildMonster)),
      resources(res),
      isBossBattle(isBoss),
      phase(BattlePhase::Intro),
      phaseTimer(1.8f),
      selectedMoveIndex(0),
      currentAttackType(ElementType::Normal),
      isPlayerAttacking(false),
      isEnemyAttacking(false),
      attackAnimTime(0.0f),
      floatingDamageText(""),
      floatingTextTimer(0.0f),
      floatingTextPos({0.0f, 0.0f}),
      catchAnimTime(0.0f),
      catchWillSucceed(false) {
    playerMonster = player.getFirstAliveMonster();

    if (isBossBattle) {
        battleLog = "Ancient Forest Guardian " + enemyMonster->getName() + " attacks!";
    } else {
        battleLog = enemyMonster->getName() + " appeared in the tall grass!";
    }
}

void BattleState::handleInput(const sf::Event& event) {
    const auto* keyPressed = event.getIf<sf::Event::KeyPressed>();
    if (!keyPressed) return;

    if (phase == BattlePhase::ActionSelect) {
        if (keyPressed->code == sf::Keyboard::Key::Num1) {
            phase = BattlePhase::MoveSelect;
        } else if (keyPressed->code == sf::Keyboard::Key::Num2) {
            // Use Potion from Bag
            if (player.getInventory().getItemCount("Potion") > 0 ||
                player.getInventory().getItemCount("Super Potion") > 0) {
                if (playerMonster->getCurrentHp() >= playerMonster->getMaxHp()) {
                    battleLog = playerMonster->getName() + " is already at full health!";
                } else {
                    if (player.getInventory().getItemCount("Potion") > 0) {
                        player.getInventory().removeItem("Potion", 1);
                        playerMonster->heal(20);
                        battleLog = "Used Potion! Restored 20 HP to " + playerMonster->getName() + "!";
                    } else {
                        player.getInventory().removeItem("Super Potion", 1);
                        playerMonster->heal(50);
                        battleLog = "Used Super Potion! Restored 50 HP to " + playerMonster->getName() + "!";
                    }
                    phase = BattlePhase::ExecutingEnemyMove;
                    phaseTimer = 1.8f;
                    executeEnemyAttack();
                }
            } else {
                battleLog = "You do not have any healing potions in your Bag!";
            }
        } else if (keyPressed->code == sf::Keyboard::Key::Num3) {
            attemptCatch();
        } else if (keyPressed->code == sf::Keyboard::Key::Num4) {
            if (isBossBattle) {
                battleLog = "You cannot run away from a Guardian battle!";
            } else {
                battleLog = "Got away safely!";
                phase = BattlePhase::RunAway;
                phaseTimer = 1.2f;
            }
        }
    } else if (phase == BattlePhase::MoveSelect) {
        const auto& moves = playerMonster->getMoves();
        if (keyPressed->code == sf::Keyboard::Key::Num1 && moves.size() >= 1) {
            executePlayerAttack(0);
        } else if (keyPressed->code == sf::Keyboard::Key::Num2 && moves.size() >= 2) {
            executePlayerAttack(1);
        } else if (keyPressed->code == sf::Keyboard::Key::Num3 && moves.size() >= 3) {
            executePlayerAttack(2);
        } else if (keyPressed->code == sf::Keyboard::Key::Num4 && moves.size() >= 4) {
            executePlayerAttack(3);
        } else if (keyPressed->code == sf::Keyboard::Key::Escape || keyPressed->code == sf::Keyboard::Key::B) {
            phase = BattlePhase::ActionSelect;
            battleLog = "What will " + playerMonster->getName() + " do?";
        }
    }
}

void BattleState::executePlayerAttack(size_t moveIndex) {
    const auto& moves = playerMonster->getMoves();
    if (moveIndex >= moves.size()) return;

    const auto& move = moves[moveIndex];
    float multiplier = 1.0f;
    int dmg = enemyMonster->takeDamage(move.getPower(), move.getType(), *playerMonster, multiplier);

    battleLog = playerMonster->getName() + " used " + move.getName() + " for " + std::to_string(dmg) + " dmg!";
    if (multiplier > 1.0f) battleLog += " It's super effective!";
    else if (multiplier < 1.0f) battleLog += " It's not very effective...";

    currentAttackType = move.getType();
    isPlayerAttacking = true;
    isEnemyAttacking = false;
    attackAnimTime = 0.0f;

    floatingDamageText = "-" + std::to_string(dmg) + " HP";
    floatingTextPos = {650.0f, 110.0f};
    floatingTextTimer = 1.4f;

    phase = BattlePhase::ExecutingPlayerMove;
    phaseTimer = 2.0f;
}

void BattleState::executeEnemyAttack() {
    const auto& moves = enemyMonster->getMoves();
    if (moves.empty()) return;

    static std::mt19937 rng(1337);
    int moveIdx = rng() % moves.size();
    const auto& move = moves[moveIdx];

    float multiplier = 1.0f;
    int dmg = playerMonster->takeDamage(move.getPower(), move.getType(), *enemyMonster, multiplier);

    battleLog = enemyMonster->getName() + " used " + move.getName() + " dealing " + std::to_string(dmg) + " damage!";
    if (multiplier > 1.0f) battleLog += " Critical damage!";

    currentAttackType = move.getType();
    isPlayerAttacking = false;
    isEnemyAttacking = true;
    attackAnimTime = 0.0f;

    floatingDamageText = "-" + std::to_string(dmg) + " HP";
    floatingTextPos = {260.0f, 260.0f};
    floatingTextTimer = 1.4f;

    phase = BattlePhase::ExecutingEnemyMove;
    phaseTimer = 2.0f;
}

void BattleState::attemptCatch() {
    if (isBossBattle) {
        battleLog = "Sylvanguard's aura deflects the Capture Ball! Weaken it in combat!";
        return;
    }

    if (player.getInventory().getItemCount("Capture Ball") <= 0) {
        battleLog = "You do not have any Capture Balls in your bag!";
        return;
    }

    player.getInventory().removeItem("Capture Ball", 1);

    // Probability calculation: easier when enemy HP is low
    float hpFraction = static_cast<float>(enemyMonster->getCurrentHp()) / static_cast<float>(enemyMonster->getMaxHp());
    float catchChance = (1.0f - hpFraction) * 0.75f + 0.25f; // 25% min, up to 100%

    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    catchWillSucceed = (dist(rng) <= catchChance);
    catchAnimTime = 0.0f;
    phase = BattlePhase::Capturing;
    phaseTimer = 3.2f;
    battleLog = "Threw a Capture Ball!";
}

void BattleState::handleVictory() {
    int expGained = enemyMonster->getLevel() * 15;
    bool leveledUp = playerMonster->gainExp(expGained);

    battleLog = enemyMonster->getName() + " fainted! " + playerMonster->getName() + " gained " + std::to_string(expGained) + " EXP!";
    if (leveledUp) {
        battleLog += " " + playerMonster->getName() + " grew to Lv. " + std::to_string(playerMonster->getLevel()) + "!";
    }

    if (isBossBattle) {
        player.setBossDefeated(true);
    }

    phase = BattlePhase::Victory;
    phaseTimer = 2.4f;
}

void BattleState::handleDefeat() {
    battleLog = playerMonster->getName() + " fainted! You rushed back to the Health Center...";
    player.healAllMonsters();
    player.setGridPosition(6, 19); // Respawn outside Nurse Joy's Clinic
    phase = BattlePhase::Defeat;
    phaseTimer = 2.5f;
}

void BattleState::update(float deltaTime) {
    attackAnimTime += deltaTime;

    if (floatingTextTimer > 0.0f) {
        floatingTextTimer -= deltaTime;
        floatingTextPos.y -= 25.0f * deltaTime;
    }

    if (phase == BattlePhase::Capturing) {
        catchAnimTime += deltaTime;
        if (catchAnimTime > 1.2f && catchAnimTime < 2.8f) {
            int wobble = static_cast<int>((catchAnimTime - 1.2f) / 0.5f) + 1;
            battleLog = "The ball is wobbling... (" + std::to_string(wobble) + "/3)";
        }
    }

    if (phaseTimer > 0.0f) {
        phaseTimer -= deltaTime;
        if (phaseTimer <= 0.0f) {
            switch (phase) {
                case BattlePhase::Intro:
                    phase = BattlePhase::ActionSelect;
                    battleLog = "What will " + playerMonster->getName() + " do?";
                    break;

                case BattlePhase::ExecutingPlayerMove:
                    isPlayerAttacking = false;
                    if (enemyMonster->isFainted()) {
                        handleVictory();
                    } else {
                        executeEnemyAttack();
                    }
                    break;

                case BattlePhase::ExecutingEnemyMove:
                    isEnemyAttacking = false;
                    if (playerMonster->isFainted()) {
                        handleDefeat();
                    } else {
                        phase = BattlePhase::ActionSelect;
                        battleLog = "What will " + playerMonster->getName() + " do?";
                    }
                    break;

                case BattlePhase::Capturing:
                    if (catchWillSucceed) {
                        battleLog = "All right! " + enemyMonster->getName() + " was caught!";
                        player.addMonster(enemyMonster);
                        phase = BattlePhase::CaughtSuccess;
                        phaseTimer = 2.0f;
                    } else {
                        battleLog = "Oh no! The wild monster broke free!";
                        phase = BattlePhase::CaughtFailed;
                        phaseTimer = 1.8f;
                        executeEnemyAttack();
                    }
                    break;

                case BattlePhase::CaughtSuccess:
                case BattlePhase::Victory:
                case BattlePhase::RunAway:
                case BattlePhase::Defeat:
                    stateManager.popState();
                    break;

                default:
                    break;
            }
        }
    }
}

void BattleState::drawHealthBar(sf::RenderTarget& target, float x, float y, float width, float height, int currentHp, int maxHp) {
    sf::RectangleShape bg({width, height});
    bg.setPosition({x, y});
    bg.setFillColor(sf::Color(40, 40, 45, 255));
    bg.setOutlineColor(sf::Color(10, 10, 15, 255));
    bg.setOutlineThickness(2.0f);
    target.draw(bg);

    float ratio = std::clamp(static_cast<float>(currentHp) / std::max(1.0f, static_cast<float>(maxHp)), 0.0f, 1.0f);
    sf::RectangleShape bar({width * ratio, height});
    bar.setPosition({x, y});

    if (ratio > 0.5f) bar.setFillColor(sf::Color(60, 210, 80, 255));     // Green
    else if (ratio > 0.2f) bar.setFillColor(sf::Color(240, 190, 40, 255)); // Yellow
    else bar.setFillColor(sf::Color(230, 50, 40, 255));                  // Red

    target.draw(bar);
}

void BattleState::drawAttackEffects(sf::RenderTarget& target, sf::Vector2f targetPos, ElementType type, float animTime) {
    if (animTime < 0.2f || animTime > 1.2f) return;

    float t = (animTime - 0.2f) / 1.0f;

    if (type == ElementType::Fire) {
        // Fire particles: expanding swirling flame circles
        for (int i = 0; i < 7; ++i) {
            float angle = static_cast<float>(i) * 0.9f + t * 6.0f;
            float radius = 20.0f + t * 50.0f;
            float fx = targetPos.x + std::cos(angle) * radius;
            float fy = targetPos.y + std::sin(angle) * (radius * 0.6f);

            sf::CircleShape flame(14.0f * (1.0f - t * 0.6f));
            flame.setOrigin({flame.getRadius(), flame.getRadius()});
            flame.setPosition({fx, fy});
            if (i % 2 == 0) flame.setFillColor(sf::Color(255, 120, 20, static_cast<std::uint8_t>(255 * (1.0f - t))));
            else flame.setFillColor(sf::Color(255, 230, 50, static_cast<std::uint8_t>(255 * (1.0f - t))));
            target.draw(flame);
        }
    } else if (type == ElementType::Water) {
        // Water bubbles: streaming blue droplet bubbles
        for (int i = 0; i < 8; ++i) {
            float bx = targetPos.x - 40.0f + static_cast<float>(i * 12) + std::sin(t * 10.0f + static_cast<float>(i)) * 15.0f;
            float by = targetPos.y + 20.0f - t * 60.0f - static_cast<float>(i * 6);
            sf::CircleShape bubble(10.0f + static_cast<float>(i % 3) * 4.0f);
            bubble.setOrigin({bubble.getRadius(), bubble.getRadius()});
            bubble.setPosition({bx, by});
            bubble.setFillColor(sf::Color(90, 180, 255, static_cast<std::uint8_t>(230 * (1.0f - t))));
            bubble.setOutlineColor(sf::Color(255, 255, 255, static_cast<std::uint8_t>(200 * (1.0f - t))));
            bubble.setOutlineThickness(2.0f);
            target.draw(bubble);
        }
    } else if (type == ElementType::Grass) {
        // Razor leaf / Vine arc
        for (int i = 0; i < 5; ++i) {
            float angle = static_cast<float>(i) * 1.25f + t * 12.0f;
            float rx = targetPos.x + std::cos(angle) * (45.0f * (1.0f - t));
            float ry = targetPos.y + std::sin(angle) * (30.0f * (1.0f - t));

            sf::ConvexShape leaf;
            leaf.setPointCount(4);
            leaf.setPoint(0, sf::Vector2f(0.0f, -14.0f));
            leaf.setPoint(1, sf::Vector2f(7.0f, 0.0f));
            leaf.setPoint(2, sf::Vector2f(0.0f, 14.0f));
            leaf.setPoint(3, sf::Vector2f(-7.0f, 0.0f));
            leaf.setPosition({rx, ry});
            leaf.setRotation(sf::degrees(angle * 57.29f));
            leaf.setFillColor(sf::Color(60, 210, 80, static_cast<std::uint8_t>(255 * (1.0f - t))));
            target.draw(leaf);
        }
    } else if (type == ElementType::Electric) {
        // Electric zigzag lightning bolts
        sf::VertexArray lightning(sf::PrimitiveType::LineStrip);
        float lx = targetPos.x - 30.0f;
        float ly = targetPos.y - 40.0f;
        lightning.append(sf::Vertex({lx, ly}, sf::Color::Yellow));
        for (int i = 1; i <= 6; ++i) {
            lx += 12.0f;
            ly += (i % 2 == 0) ? -18.0f : 24.0f;
            lightning.append(sf::Vertex({lx, ly}, sf::Color(255, 255, 120, 255)));
        }
        target.draw(lightning);

        // Electric spark dots
        for (int i = 0; i < 6; ++i) {
            sf::CircleShape spark(4.0f);
            spark.setPosition({targetPos.x + static_cast<float>((i % 3) * 25 - 25), targetPos.y + static_cast<float>((i / 3) * 30 - 15)});
            spark.setFillColor(sf::Color(255, 255, 60, 240));
            target.draw(spark);
        }
    } else {
        // Normal slash / impact stars
        sf::RectangleShape slash({60.0f, 4.0f});
        slash.setOrigin({30.0f, 2.0f});
        slash.setPosition(targetPos);
        slash.setRotation(sf::degrees(45.0f));
        slash.setFillColor(sf::Color(255, 255, 255, static_cast<std::uint8_t>(255 * (1.0f - t))));
        target.draw(slash);

        sf::RectangleShape slash2({50.0f, 4.0f});
        slash2.setOrigin({25.0f, 2.0f});
        slash2.setPosition({targetPos.x + 10.0f, targetPos.y - 10.0f});
        slash2.setRotation(sf::degrees(45.0f));
        slash2.setFillColor(sf::Color(255, 240, 200, static_cast<std::uint8_t>(255 * (1.0f - t))));
        target.draw(slash2);
    }
}

void BattleState::drawCatchAnimation(sf::RenderTarget& target) {
    if (phase != BattlePhase::Capturing && phase != BattlePhase::CaughtSuccess && phase != BattlePhase::CaughtFailed) {
        return;
    }

    float t = catchAnimTime;
    float ballX = 0.0f;
    float ballY = 0.0f;
    float rot = 0.0f;

    if (t < 1.0f) {
        // Parabolic throw arc from player platform (240, 360) to enemy platform (640, 220)
        float progress = t / 1.0f;
        ballX = 240.0f + (640.0f - 240.0f) * progress;
        ballY = 360.0f + (220.0f - 360.0f) * progress - std::sin(progress * 3.14159f) * 160.0f;
        rot = progress * 720.0f;
    } else {
        // Ball resting on platform, rocking/wobbling 3 times
        ballX = 640.0f;
        ballY = 220.0f;
        float wobbleTime = t - 1.0f;
        if (wobbleTime < 2.0f) {
            rot = std::sin(wobbleTime * 10.0f) * 22.0f;
        }
    }

    // Draw Pokéball
    sf::CircleShape ball(16.0f);
    ball.setOrigin({16.0f, 16.0f});
    ball.setPosition({ballX, ballY});
    ball.setRotation(sf::degrees(rot));
    ball.setFillColor(sf::Color(230, 40, 40, 255)); // Red top
    ball.setOutlineColor(sf::Color(20, 20, 20, 255));
    ball.setOutlineThickness(2.0f);
    target.draw(ball);

    // Ball lower hemisphere
    sf::CircleShape lower(16.0f);
    lower.setOrigin({16.0f, 16.0f});
    lower.setPosition({ballX, ballY});
    lower.setRotation(sf::degrees(rot));
    lower.setFillColor(sf::Color(245, 245, 245, 255)); // White bottom
    target.draw(lower);

    // Central band & button
    sf::RectangleShape band({32.0f, 4.0f});
    band.setOrigin({16.0f, 2.0f});
    band.setPosition({ballX, ballY});
    band.setRotation(sf::degrees(rot));
    band.setFillColor(sf::Color(20, 20, 20, 255));
    target.draw(band);

    sf::CircleShape button(5.0f);
    button.setOrigin({5.0f, 5.0f});
    button.setPosition({ballX, ballY});
    button.setFillColor(sf::Color::White);
    button.setOutlineColor(sf::Color(30, 30, 30, 255));
    button.setOutlineThickness(1.0f);
    target.draw(button);

    // Star burst on catch success
    if (phase == BattlePhase::CaughtSuccess) {
        for (int i = 0; i < 6; ++i) {
            float starAngle = static_cast<float>(i) * 1.04f;
            float dist = 25.0f + (2.0f - phaseTimer) * 40.0f;
            sf::CircleShape star(5.0f, 4); // Diamond/star shape
            star.setPosition({ballX + std::cos(starAngle) * dist, ballY + std::sin(starAngle) * dist});
            star.setFillColor(sf::Color(255, 235, 60, 255));
            target.draw(star);
        }
    }
}

void BattleState::render(sf::RenderTarget& target) {
    sf::View originalView = target.getView();
    target.setView(target.getDefaultView()); // 960x640 UI space

    // 1. Battle Arena Background
    sf::RectangleShape sky({960.0f, 380.0f});
    sky.setFillColor(sf::Color(135, 190, 240, 255)); // Sky blue
    target.draw(sky);

    sf::RectangleShape field({960.0f, 260.0f});
    field.setPosition({0.0f, 380.0f});
    field.setFillColor(sf::Color(70, 150, 80, 255)); // Grass green
    target.draw(field);

    // Arena Platform ovals
    sf::CircleShape enemyPlatform(120.0f);
    enemyPlatform.setScale({1.8f, 0.5f});
    enemyPlatform.setPosition({450.0f, 240.0f});
    enemyPlatform.setFillColor(sf::Color(140, 205, 120, 255));
    target.draw(enemyPlatform);

    sf::CircleShape playerPlatform(140.0f);
    playerPlatform.setScale({2.0f, 0.55f});
    playerPlatform.setPosition({80.0f, 400.0f});
    playerPlatform.setFillColor(sf::Color(140, 205, 120, 255));
    target.draw(playerPlatform);

    // 2. Enemy Monster Sprite with Animation
    sf::Vector2f enemyBasePos({570.0f, 120.0f});

    // Enemy Lunge during attack
    if (isEnemyAttacking && attackAnimTime < 0.4f) {
        float lunge = std::sin((attackAnimTime / 0.4f) * 3.14159f) * 55.0f;
        enemyBasePos.x -= lunge * 1.2f;
        enemyBasePos.y += lunge * 0.5f;
    }

    // Enemy Hit Shake & Flash
    bool enemyHitFlashing = false;
    if (isPlayerAttacking && attackAnimTime >= 0.25f && attackAnimTime < 0.8f) {
        float shake = std::sin((attackAnimTime - 0.25f) * 45.0f) * 10.0f;
        enemyBasePos.x += shake;
        if (static_cast<int>(attackAnimTime * 20.0f) % 2 == 0) {
            enemyHitFlashing = true;
        }
    }

    // Capture shrinking effect
    float enemyScale = 2.8f;
    if (phase == BattlePhase::Capturing && catchAnimTime > 0.9f) {
        enemyScale = std::max(0.0f, 2.8f * (1.0f - (catchAnimTime - 0.9f) * 2.5f));
    }

    if (enemyScale > 0.05f) {
        const sf::Texture& enemyTex = resources.getPokemonFrontTexture(enemyMonster->getTextureKey());
        sf::Sprite enemySprite(enemyTex);
        enemySprite.setScale({enemyScale, enemyScale});
        enemySprite.setPosition(enemyBasePos);
        if (enemyHitFlashing) {
            enemySprite.setColor(sf::Color(255, 120, 120, 220));
        }
        target.draw(enemySprite);
    }

    // 3. Enemy Status Card (Top Left)
    sf::RectangleShape enemyCard({340.0f, 90.0f});
    enemyCard.setPosition({80.0f, 50.0f});
    enemyCard.setFillColor(sf::Color(245, 245, 240, 240));
    enemyCard.setOutlineColor(sf::Color(50, 60, 70, 255));
    enemyCard.setOutlineThickness(3.0f);
    target.draw(enemyCard);

    sf::Text enemyName(resources.getFont(), enemyMonster->getName(), 20);
    enemyName.setFillColor(sf::Color(30, 30, 30, 255));
    enemyName.setPosition({95.0f, 58.0f});
    target.draw(enemyName);

    sf::Text enemyLevel(resources.getFont(), "Lv. " + std::to_string(enemyMonster->getLevel()), 18);
    enemyLevel.setFillColor(sf::Color(80, 80, 90, 255));
    enemyLevel.setPosition({340.0f, 60.0f});
    target.draw(enemyLevel);

    drawHealthBar(target, 140.0f, 95.0f, 240.0f, 14.0f, enemyMonster->getCurrentHp(), enemyMonster->getMaxHp());

    sf::Text hpLabel(resources.getFont(), "HP", 14);
    hpLabel.setFillColor(sf::Color(220, 140, 20, 255));
    hpLabel.setPosition({105.0f, 93.0f});
    target.draw(hpLabel);

    // 4. Player Monster Sprite with Animation
    sf::Vector2f playerBasePos({180.0f, 270.0f});

    // Player Lunge during attack
    if (isPlayerAttacking && attackAnimTime < 0.4f) {
        float lunge = std::sin((attackAnimTime / 0.4f) * 3.14159f) * 55.0f;
        playerBasePos.x += lunge * 1.2f;
        playerBasePos.y -= lunge * 0.5f;
    }

    // Player Hit Shake & Flash
    bool playerHitFlashing = false;
    if (isEnemyAttacking && attackAnimTime >= 0.25f && attackAnimTime < 0.8f) {
        float shake = std::sin((attackAnimTime - 0.25f) * 45.0f) * 10.0f;
        playerBasePos.x += shake;
        if (static_cast<int>(attackAnimTime * 20.0f) % 2 == 0) {
            playerHitFlashing = true;
        }
    }

    const sf::Texture& playerTex = resources.getPokemonBackTexture(playerMonster->getTextureKey());
    sf::Sprite playerSprite(playerTex);
    playerSprite.setScale({3.4f, 3.4f});
    playerSprite.setPosition(playerBasePos);
    if (playerHitFlashing) {
        playerSprite.setColor(sf::Color(255, 120, 120, 220));
    }
    target.draw(playerSprite);

    // 5. Draw Attack FX particles
    if (isPlayerAttacking) {
        drawAttackEffects(target, {660.0f, 180.0f}, currentAttackType, attackAnimTime);
    } else if (isEnemyAttacking) {
        drawAttackEffects(target, {270.0f, 340.0f}, currentAttackType, attackAnimTime);
    }

    // 6. Draw Pokéball Catch Animation
    drawCatchAnimation(target);

    // 7. Floating Damage Number
    if (floatingTextTimer > 0.0f) {
        sf::Text dmgText(resources.getFont(), floatingDamageText, 24);
        dmgText.setFillColor(sf::Color(255, 230, 40, static_cast<std::uint8_t>(255 * (floatingTextTimer / 1.4f))));
        dmgText.setOutlineColor(sf::Color(180, 20, 20, 255));
        dmgText.setOutlineThickness(2.0f);
        dmgText.setPosition(floatingTextPos);
        target.draw(dmgText);
    }

    // 8. Player Status Card (Bottom Right)
    sf::RectangleShape playerCard({360.0f, 105.0f});
    playerCard.setPosition({520.0f, 330.0f});
    playerCard.setFillColor(sf::Color(245, 245, 240, 240));
    playerCard.setOutlineColor(sf::Color(50, 60, 70, 255));
    playerCard.setOutlineThickness(3.0f);
    target.draw(playerCard);

    sf::Text playerName(resources.getFont(), playerMonster->getName(), 20);
    playerName.setFillColor(sf::Color(30, 30, 30, 255));
    playerName.setPosition({540.0f, 338.0f});
    target.draw(playerName);

    sf::Text playerLevel(resources.getFont(), "Lv. " + std::to_string(playerMonster->getLevel()), 18);
    playerLevel.setFillColor(sf::Color(80, 80, 90, 255));
    playerLevel.setPosition({800.0f, 340.0f});
    target.draw(playerLevel);

    drawHealthBar(target, 580.0f, 375.0f, 260.0f, 14.0f, playerMonster->getCurrentHp(), playerMonster->getMaxHp());

    sf::Text pPhpLabel(resources.getFont(), "HP", 14);
    pPhpLabel.setFillColor(sf::Color(220, 140, 20, 255));
    pPhpLabel.setPosition({545.0f, 373.0f});
    target.draw(pPhpLabel);

    sf::Text hpValues(resources.getFont(), std::to_string(playerMonster->getCurrentHp()) + " / " + std::to_string(playerMonster->getMaxHp()), 15);
    hpValues.setFillColor(sf::Color(40, 40, 40, 255));
    hpValues.setPosition({740.0f, 395.0f});
    target.draw(hpValues);

    // 9. Bottom Battle Command Bar
    sf::RectangleShape bottomPanel({960.0f, 170.0f});
    bottomPanel.setPosition({0.0f, 470.0f});
    bottomPanel.setFillColor(sf::Color(25, 30, 45, 255));
    bottomPanel.setOutlineColor(sf::Color(220, 190, 80, 255));
    bottomPanel.setOutlineThickness(3.0f);
    target.draw(bottomPanel);

    // Battle Narrative Text Box (Left)
    sf::Text logText(resources.getFont(), battleLog, 20);
    logText.setFillColor(sf::Color::White);
    logText.setPosition({40.0f, 500.0f});
    target.draw(logText);

    // Options Menu (Right)
    if (phase == BattlePhase::ActionSelect) {
        sf::Text opt1(resources.getFont(), "[1] FIGHT", 20);
        opt1.setFillColor(sf::Color(255, 90, 90, 255));
        opt1.setPosition({560.0f, 500.0f});
        target.draw(opt1);

        sf::Text opt2(resources.getFont(), "[2] BAG", 20);
        opt2.setFillColor(sf::Color(255, 210, 80, 255));
        opt2.setPosition({760.0f, 500.0f});
        target.draw(opt2);

        sf::Text opt3(resources.getFont(), "[3] CATCH", 20);
        opt3.setFillColor(sf::Color(90, 190, 255, 255));
        opt3.setPosition({560.0f, 560.0f});
        target.draw(opt3);

        sf::Text opt4(resources.getFont(), "[4] RUN", 20);
        opt4.setFillColor(sf::Color(180, 240, 120, 255));
        opt4.setPosition({760.0f, 560.0f});
        target.draw(opt4);
    } else if (phase == BattlePhase::MoveSelect) {
        const auto& moves = playerMonster->getMoves();
        for (size_t i = 0; i < moves.size(); ++i) {
            float mx = (i % 2 == 0) ? 520.0f : 740.0f;
            float my = (i < 2) ? 495.0f : 555.0f;

            std::string mStr = "[" + std::to_string(i + 1) + "] " + moves[i].getName() + "\n" +
                               moves[i].getTypeName() + " (Pwr " + std::to_string(moves[i].getPower()) + ")";
            sf::Text moveText(resources.getFont(), mStr, 17);
            moveText.setFillColor(sf::Color(240, 240, 255, 255));
            moveText.setPosition({mx, my});
            target.draw(moveText);
        }

        sf::Text backText(resources.getFont(), "[Esc] Back", 14);
        backText.setFillColor(sf::Color(160, 160, 180, 200));
        backText.setPosition({860.0f, 605.0f});
        target.draw(backText);
    }

    target.setView(originalView); // Restore
}
