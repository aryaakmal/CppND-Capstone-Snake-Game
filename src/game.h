#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include <thread>
#include <memory>

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration, std::string user);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  SDL_Point food;
  SDL_Point poison;
  Bomb bomb;
  Missile missile;
//MissileQueue mqueue;
//std::shared_ptr<MissileQueue> mqueue(new MissileQueue); //why doesn't this work?
  std::shared_ptr<MissileQueue> mqueue = std::make_shared<MissileQueue>();

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  int m_cnt{0};

  void Update();
  template <typename T>
  void PlaceItem(T &item);
};

#endif
