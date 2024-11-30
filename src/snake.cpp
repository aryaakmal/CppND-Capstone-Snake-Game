#include "snake.h"
#include <cmath>
#include <iostream>
#include <mutex>

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

void Bomb::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the bomb's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the bomb's cell after updating.
}

void Bomb::UpdateHead() {
  std::random_device dev;
  std::mt19937 engine(dev());
  std::uniform_int_distribution<int> random_dir(1,4);

  switch (random_dir(engine)) {
    case 1:
      head_y -= speed;
      break;

    case 2:
      head_y += speed;
      break;

    case 3:
      head_x -= speed;
      break;

    case 4:
      head_x += speed;
      break;
  }

  // Wrap the path around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}


// Inefficient method to check if cell is occupied by bomb.
bool Bomb::BombCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  return false;
}

void Missile::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // We first capture the Missile's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the Missile's cell after updating.
}

void Missile::UpdateHead() {
  switch (_id%4) {
    case 0:
      head_y -= speed;
      break;

    case 1:
      head_y += speed;
      break;

    case 2:
      head_x -= speed;
      break;

    case 3:
      head_x += speed;
      break;
  }

  // Wrap the path around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

// Inefficient method to check if cell is occupied by missile.
bool Missile::MissileCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  return false;
}

void Missile::printID(){
 std::cout << "missile ID: " <<_id << std::endl;
}

int MissileQueue::qsize(){
 return _missiles.size();
}

void MissileQueue::pushBack(Missile &&m){
  _mutex.lock();
  _missiles.emplace_back(std::move(m));
  _mutex.unlock();
}

void MissileQueue::printSize(){
  _mutex.lock();
  std::cout << "queue length: " << _missiles.size() <<std::endl;
  _mutex.unlock();
}

Missile MissileQueue::popBack(){
   auto lastElement = _missiles.back();
   if (!_missiles.empty()){ _missiles.pop_back();}
   return lastElement;
}
