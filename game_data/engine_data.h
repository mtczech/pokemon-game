#ifndef FINAL_PROJECT_MTCZECH_ENGINE_DATA_H
#define FINAL_PROJECT_MTCZECH_ENGINE_DATA_H

#endif FINAL_PROJECT_MTCZECH_ENGINE_DATA_H

#include <nlohmann/json.hpp>
#include <unordered_map>
#include <map>
#include <cinder/app/App.h>

#include "../data_classes/move.h"
#include "../data_classes/pokemon_species.h"
#include "..\players\human_player.h"
#include "..\players\computer_player.h"

class EngineData {
 public:
  EngineData();

  EngineData(std::string move_json_path, std::string species_json_path, std::string set_json_path);

  void EngineData::to_json(nlohmann::json& j, const pokemon_move::Move& move);

  //Function for converting JSON to a move
  void EngineData::from_json(const nlohmann::json& j, pokemon_move::Move& move);

  std::vector<pokemon_move::Move> EngineData::GetMoves();

  std::vector<pokemon_species::Species> EngineData::GetAllPokemonList();

  /**
   * Function for finding a move given its name
   * @param move_name The name of the move being searched for
   * @return The move being searched for
   */

  pokemon_move::Move EngineData::FindMove(const std::string move_name);

  HumanPlayer EngineData::GetHumanPlayer();

  ComputerPlayer EngineData::GetComputerPlayer();

  std::unordered_map<std::string, std::unordered_map<std::string, float>>
  EngineData::GetTypeMatrix();

  //Function for setting up the type matrix for determining strengths and weaknesses
  //Type matrix is hard coded in since the type matchups do not change

  void EngineData::SetUpTypeMatrix();

  size_t EngineData::FindLeadIndex(std::vector<pokemon_species::Species> v);

  /**
   * Function that returns an array of Pokemon with loaded movesets given an array of numbers
   */

  std::vector<pokemon_species::Species> EngineData::CreatePokemonTeam(std::vector<size_t> indices);

 private:

  //All of the moves in the game

  std::vector<pokemon_move::Move> moves;

  //All of the possible pokemon that a player can have

  std::vector<pokemon_species::Species> all_pokemon_list;

  //The human player

  HumanPlayer human_player;

  //The computer player

  ComputerPlayer computer_player;

  //The type matrix for showing which hits are super effective

  std::unordered_map<std::string, std::unordered_map<std::string, float>> type_matrix_;
};