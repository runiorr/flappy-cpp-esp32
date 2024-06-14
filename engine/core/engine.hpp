#pragma once

#include "../entity/entity.hpp"
#include "../system/system.hpp"

#include <memory>
#include <vector>

class GameEngine {
private:
  std::vector<std::unique_ptr<SystemInterface>> systems;
  std::vector<std::unique_ptr<Entity>> entities;

  void organizeZIndex();

public:
  /**
   *  @brief  Add a system to the engine to be run on a loop.
   *
   *  Use like this:
   *  engine.addSystem<YourSystem, YourSystemParams>(YourSystemParams{x, y, z})
   */
  template <typename T, typename P> void addSystem(P params) {
    systems.emplace_back(make_unique<T>(params));
  }

  /**
   *  @brief  Add an entity to the engine to be passed to every system.
   *
   *  You can pass args to your entity constructor
   *
   *  Use like this:
   *  engine.addEntity<YourEntityClass>("Name");
   *
   *  Where:
   *  YourEntityClass::YourEntityClass(std::string name) : Entity(name) {
   *
   */
  template <typename T, typename... Args> void addEntity(Args &&...args) {
    entities.emplace_back(make_unique<T>(std::forward<Args>(args)...));
  }

  /**
   *  @brief  Start the game.
   *
   *  It will organize entities that has transform component by their Z
   *  coordinate and setup the render before entering the game loop and running
   *  systems.
   */
  void run();
};
