#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <random>
#include "SDL.h"
#include <mutex>

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;
  float speed_hold;
  int grid_width;
  int grid_height;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
};

class Bomb {
 public:
  
  enum class Direction { kUp, kDown, kLeft, kRight };
  Bomb(int grid_width, int grid_height) 
     : grid_width(grid_width),
       grid_height(grid_height),
       head_x(3*grid_width/4),
       head_y(3*grid_height/4) {}
 
  void Update();
  bool BombCell(int x, int y);
  Direction direction = Direction::kDown;
  float speed{0.2f};
  float head_x;
  float head_y;
  int x;
  int y;

 private:
  void UpdateHead();
  int grid_width;
  int grid_height;

//std::random_device dev;
//std::mt19937 engine;
//std::uniform_int_distribution<int> random_dir;

};

class Missile {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };
//Missile(int id) : _id(id) {}
  Missile(int id, int grid_width, int grid_height) : _id(id), grid_width(grid_width), grid_height(grid_height) {}

  void Update();
  bool MissileCell(int x, int y);
  Direction direction = Direction::kDown;
  float speed{0.2f};
  float head_x;
  float head_y;
  int x;
  int y;
  void printID();
  int grid_width;
  int grid_height;
 private:
  int _id;
  void UpdateHead();
};

class MissileQueue {
 public:
//MissileQueue();
  void pushBack(Missile &&m);
  void printSize();
  Missile popBack();
  int qsize();
 private:
  std::vector<Missile> _missiles;
  std::mutex _mutex;
};

#endif
