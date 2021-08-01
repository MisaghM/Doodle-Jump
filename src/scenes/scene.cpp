#include "scene.hpp"

#include "../game_object.hpp"

Scene::Scene(InputManager* inputMan) : inputMan_(inputMan) {}

Scene::~Scene() {
    for (GameObject* obj : objs_) delete obj;
}

bool Scene::update(Window* win, unsigned deltaTime, System* sys) {
    for (GameObject* obj : objs_) obj->update(deltaTime, win);
    return true;
}

void Scene::draw(Window* win) {
    for (GameObject* obj : objs_) obj->draw(win);
}