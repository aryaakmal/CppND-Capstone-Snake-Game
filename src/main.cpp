#include <iostream>
#include <string>
#include<fstream>
#include<chrono>
#include<ctime>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  std::string user;
  std::ofstream result_file;

  //time the game duration
  auto start = std::chrono::system_clock::now();
  std::time_t start_time = std::chrono::system_clock::to_time_t(start);
 
  std::cout << "Enter Player Name: " << std::endl;
  std::cin >> user;

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame, user);
  std::cout << "Game has terminated successfully!\n";
  std::cout << user << "'s results:" << std::endl; 
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";

  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;

  //output results to player's text file
  result_file.open(user+".results.txt", std::ios_base::app);
  result_file << "----------\n";
  result_file << "Started at: " << std::ctime(&start_time);
  result_file << "---Score: " << game.GetScore() << std::endl;
  result_file << "---Size: " << game.GetSize() << std::endl;
  result_file << "Game duration: " << elapsed_seconds.count() << "s" << std::endl;
  result_file.close();

  return 0;
}
