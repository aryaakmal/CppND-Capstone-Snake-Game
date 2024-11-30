#include "game.h"
#include <iostream>
#include <thread>
#include "SDL.h"
#include <memory>
#include <future>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height), bomb(grid_width, grid_height),
      engine(dev()), missile(0, grid_width, grid_height),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceItem(food);
  PlaceItem(poison);
  PlaceItem(bomb);
  bomb.head_x = static_cast<float>(bomb.x);
  bomb.head_y = static_cast<float>(bomb.y);
  PlaceItem(missile);
  missile.head_x = static_cast<float>(missile.x);
  missile.head_y = static_cast<float>(missile.y);
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration, std::string user) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    
    renderer.Render(snake, food, poison, bomb, missile);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count, user);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}


//template for placing food, poison or missile on grid.
template <typename T>
void Game::PlaceItem(T &item) {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // new item.
    if (!snake.SnakeCell(x, y)) {
      item.x = x;
      item.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  std::thread t1(&Snake::Update, &snake);
  std::future<void> ftr;

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  //check if there's a bomb over there

  int bomb_x = static_cast<int>(bomb.head_x);
  int bomb_y = static_cast<int>(bomb.head_y);
  if (bomb_x == new_x && bomb_y == new_y) {
   snake.alive = false;
  }

  //check if there's a missile over there

  int missile_x = static_cast<int>(missile.head_x);
  int missile_y = static_cast<int>(missile.head_y);
  if (missile_x == new_x && missile_y == new_y) {
   snake.alive = false;
  }

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    m_cnt++;
    Missile missile(m_cnt, snake.grid_width, snake.grid_height); 
    PlaceItem(missile);
    missile.head_x = static_cast<float>(missile.x);
    missile.head_y = static_cast<float>(missile.y);
    ftr=std::async(std::launch::async, &MissileQueue::pushBack, mqueue, std::move(missile));
    PlaceItem(food);
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }

 // Check if there's poison over here
 if (poison.x == new_x && poison.y == new_y) {
    score--;
    //auto missile = mqueue->popBack();
    mqueue->printSize();
    if(score > 0){
     missile = std::move(mqueue->popBack());
    }
    mqueue->printSize();
    missile.printID();
    PlaceItem(poison);
    if(score < 0)
    {
     snake.alive = false; 
    }
 }
 if(ftr.valid()){ftr.wait();}
 std::thread t2(&Bomb::Update, &bomb);
 std::thread t3(&Missile::Update, &missile);
 t1.join();
 t2.join();
 t3.join();
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
