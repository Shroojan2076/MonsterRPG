#include "Item.hpp"
#include "Monster.hpp"
#include <algorithm>

// Item Base
Item::Item(std::string name, std::string description, ItemCategory category)
    : name(std::move(name)), description(std::move(description)), category(category) {}

const std::string& Item::getName() const { return name; }
const std::string& Item::getDescription() const { return description; }
ItemCategory Item::getCategory() const { return category; }

// PotionItem
PotionItem::PotionItem(int healAmount)
    : Item("Potion", "Restores 20 HP to a friendly monster.", ItemCategory::Healing),
      healAmount(healAmount) {}

bool PotionItem::use(Monster& target, Player& /*player*/) {
    if (target.isFainted() || target.getCurrentHp() >= target.getMaxHp()) {
        return false;
    }
    target.heal(healAmount);
    return true;
}

int PotionItem::getHealAmount() const { return healAmount; }

// SuperPotionItem
SuperPotionItem::SuperPotionItem(int healAmount)
    : Item("Super Potion", "Restores 50 HP to a friendly monster.", ItemCategory::Healing),
      healAmount(healAmount) {}

bool SuperPotionItem::use(Monster& target, Player& /*player*/) {
    if (target.isFainted() || target.getCurrentHp() >= target.getMaxHp()) {
        return false;
    }
    target.heal(healAmount);
    return true;
}

// CaptureBallItem
CaptureBallItem::CaptureBallItem(float bonus)
    : Item("Capture Ball", "A device used to catch wild monsters in combat.", ItemCategory::Capture),
      catchRateBonus(bonus) {}

bool CaptureBallItem::use(Monster& /*target*/, Player& /*player*/) {
    // BattleState handles catch calculation using catchRateBonus
    return true;
}

float CaptureBallItem::getCatchRateBonus() const { return catchRateBonus; }

// Inventory Implementation
Inventory::Inventory() = default;

void Inventory::addItem(const std::shared_ptr<Item>& item, int count) {
    if (!item || count <= 0) return;
    for (auto& slot : slots) {
        if (slot.item->getName() == item->getName()) {
            slot.count += count;
            return;
        }
    }
    slots.push_back({item, count});
}

bool Inventory::removeItem(const std::string& itemName, int count) {
    for (auto it = slots.begin(); it != slots.end(); ++it) {
        if (it->item->getName() == itemName) {
            if (it->count >= count) {
                it->count -= count;
                if (it->count == 0) {
                    slots.erase(it);
                }
                return true;
            }
            return false;
        }
    }
    return false;
}

int Inventory::getItemCount(const std::string& itemName) const {
    for (const auto& slot : slots) {
        if (slot.item->getName() == itemName) {
            return slot.count;
        }
    }
    return 0;
}

const std::vector<Inventory::Slot>& Inventory::getSlots() const {
    return slots;
}

bool Inventory::useItem(size_t slotIndex, Monster& target, Player& player) {
    if (slotIndex >= slots.size()) return false;
    if (slots[slotIndex].item->use(target, player)) {
        slots[slotIndex].count--;
        if (slots[slotIndex].count == 0) {
            slots.erase(slots.begin() + slotIndex);
        }
        return true;
    }
    return false;
}
