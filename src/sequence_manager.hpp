#ifndef SEQUENCE_MANAGER_HPP_INCLUDE
#define SEQUENCE_MANAGER_HPP_INCLUDE

#include <fstream>
#include <unordered_map>
#include <vector>

#include "game_object.hpp"

class Window;

class SequenceManager {
public:
    SequenceManager() = default;

    void readFromFile();

    struct Entity {
        Entity(int x_, int y_, GameObject::CollisionType type_);

        int x, y;
        GameObject::CollisionType type;
    };

    struct Sequence {
        Sequence(int start_, int end_, int totalHeight_, int numOfEntities_,
                 const std::vector<SequenceManager::Entity>& entities_);

        int start, end, totalHeight, numOfEntities;
        std::vector<SequenceManager::Entity> entities;

        std::vector<GameObject*> toObject() const;
    };

    std::vector<Sequence> seqs;

private:
    std::vector<Entity> readEntitiesFromFile(std::ifstream& file, int numOfEntities);

    const std::unordered_map<std::string, GameObject::CollisionType> typeMap_{
        {"platform", GameObject::CollisionType::pNormal},
        {"mplatform", GameObject::CollisionType::pMovable},
        {"bplatform", GameObject::CollisionType::pBreakable},
        {"spring", GameObject::CollisionType::spring},
        {"enemy", GameObject::CollisionType::enemyNormal},
    };
};

#endif // SEQUENCE_MANAGER_HPP_INCLUDE
