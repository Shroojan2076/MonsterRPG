#pragma once

#include <string>
#include <vector>
#include <memory>

class Monster;
class Player;

enum class ItemCategory {
    Healing,
    Capture,
    KeyItem
};

// Abstract Base Class: Demonstrating Polymorphism & Abstraction
class Item {
protected:
    std::string name;
    std::string description;
    ItemCategory category;

public:
    Item(std::string name, std::string description, ItemCategory category);
    virtual ~Item() = default;

    // Pure virtual method (Interface)
    virtual bool use(Monster& target, Player& player) = 0;

    const std::string& getName() const;
    const std::string& getDescription() const;
    ItemCategory getCategory() const;
};

// Derived Class 1: Potion
class PotionItem : public Item {
private:
    int healAmount;

public:
    explicit PotionItem(int healAmount = 20);
    bool use(Monster& target, Player& player) override;
    int getHealAmount() const;
};

// Derived Class 2: Super Potion
class SuperPotionItem : public Item {
private:
    int healAmount;

public:
    explicit SuperPotionItem(int healAmount = 50);
    bool use(Monster& target, Player& player) override;
};

// Derived Class 3: Capture Ball
class CaptureBallItem : public Item {
private:
    float catchRateBonus;

public:
    explicit CaptureBallItem(float bonus = 1.0f);
    bool use(Monster& target, Player& player) override;
    float getCatchRateBonus() const;
};

// Inventory Container Class (Demonstrating Composition & Encapsulation)
class Inventory {
public:
    struct Slot {
        std::shared_ptr<Item> item;
        int count;
    };

private:
    std::vector<Slot> slots;

public:
    Inventory();

    void addItem(const std::shared_ptr<Item>& item, int count = 1);
    bool removeItem(const std::string& itemName, int count = 1);
    int getItemCount(const std::string& itemName) const;
    const std::vector<Slot>& getSlots() const;
    bool useItem(size_t slotIndex, Monster& target, Player& player);
};
