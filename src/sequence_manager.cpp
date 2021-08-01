#include "sequence_manager.hpp"

#include <stdexcept>

#include "consts.hpp"
#include "enemies/enemy_normal.hpp"
#include "items/spring.hpp"
#include "platforms/platform_breakable.hpp"
#include "platforms/platform_movable.hpp"
#include "platforms/platform_normal.hpp"
#include "spritesheet.hpp"
#include "utils/point_f.hpp"
#include "utils/rectangle_f.hpp"

SequenceManager::Entity::Entity(int x_, int y_, GameObject::CollisionType type_)
    : x(x_),
      y(y_),
      type(type_) {}

SequenceManager::Sequence::Sequence(int start_, int end_, int totalHeight_, int numOfEntities_, const std::vector<SequenceManager::Entity>& entities_)
    : start(start_),
      end(end_),
      totalHeight(totalHeight_),
      numOfEntities(numOfEntities_),
      entities(entities_) {}

void SequenceManager::readFromFile() {
    std::ifstream file(consts::SEQ_FILE);
    if (!file.is_open()) throw std::runtime_error(std::string("Failed to open file: ") + consts::SEQ_FILE);

    int numOfSeqs;
    file >> numOfSeqs;
    seqs.reserve(numOfSeqs);

    for (int i = 0; i < numOfSeqs; i++) {
        int start, end, totalHeight, numOfEntities;
        file >> start >> end >> totalHeight >> numOfEntities;
        file.ignore(1, '\n');

        seqs.emplace_back(start, end, totalHeight, numOfEntities, readEntitiesFromFile(file, numOfEntities));
    }

    file.close();
}

std::vector<SequenceManager::Entity> SequenceManager::readEntitiesFromFile(std::ifstream& file, int numOfEntities) {
    std::vector<SequenceManager::Entity> entities;
    entities.reserve(numOfEntities);

    for (int i = 0; i < numOfEntities; i++) {
        int x, y;
        std::string type;
        file >> x >> y >> type;

        auto itr = typeMap_.find(type);
        if (itr == typeMap_.end()) {
            throw std::invalid_argument(std::string("Invalid game object type in file: ") + type);
        }

        entities.emplace_back(x, y, itr->second);
    }

    return entities;
}

static PointF getTopLeftFromBottomMiddle(int x, int y, int w, int h) {
    return PointF(x - w / 2, consts::WIN_HEIGHT - (y + h));
}

std::vector<GameObject*> SequenceManager::Sequence::toObject() const {
    std::vector<GameObject*> seqObjs;
    seqObjs.reserve(entities.size());

    for (auto& e : entities) {
        switch (e.type) {
            int width;
            int height;
        case GameObject::CollisionType::pNormal:
            width = sprite::platform[sprite::Platform::NORMAL].w;
            height = sprite::platform[sprite::Platform::NORMAL].h;
            seqObjs.push_back(new PlatformNormal(RectangleF(getTopLeftFromBottomMiddle(e.x, e.y, width, height), width, height)));
            break;
        case GameObject::CollisionType::pMovable:
            width = sprite::platform[sprite::Platform::MOVABLE].w;
            height = sprite::platform[sprite::Platform::MOVABLE].h;
            seqObjs.push_back(new PlatformMovable(RectangleF(getTopLeftFromBottomMiddle(e.x, e.y, width, height), width, height)));
            break;
        case GameObject::CollisionType::pBreakable:
            width = sprite::platform[sprite::Platform::BREAKABLE].w;
            height = sprite::platform[sprite::Platform::BREAKABLE].h;
            seqObjs.push_back(new PlatformBreakable(RectangleF(getTopLeftFromBottomMiddle(e.x, e.y, width, height), width, height)));
            break;
        case GameObject::CollisionType::spring:
            width = sprite::item[sprite::Item::SPRING].w;
            height = sprite::item[sprite::Item::SPRING].h;
            seqObjs.push_back(new Spring(RectangleF(getTopLeftFromBottomMiddle(e.x, e.y, width, height), width, height)));
            break;
        case GameObject::CollisionType::enemyNormal:
            width = sprite::enemy[sprite::Enemy::NORM].w;
            height = sprite::enemy[sprite::Enemy::NORM].h;
            seqObjs.push_back(new EnemyNormal(RectangleF(getTopLeftFromBottomMiddle(e.x, e.y, width, height), width, height),
                                              RectangleF(10, 10, width - 20, height - 20)));
            break;
        default: break;
        }
    }

    return seqObjs;
}