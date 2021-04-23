#ifndef FINAL_PROJECT_MTCZECH_ENGINE_DATA_H
#define FINAL_PROJECT_MTCZECH_ENGINE_DATA_H

#endif FINAL_PROJECT_MTCZECH_ENGINE_DATA_H

#include <C:\Cinder\cinder_0.9.2_vc2015\cinder_0.9.2_vc2015\my-projects\final-project-mtczech\httplib\httplib.h>

#include <nlohmann/json.hpp>

#include "../data_classes/move.h"
#include "../data_classes/pokemon_species.h"

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

 private:

  //All of the moves in the game

  std::vector<pokemon_move::Move> moves;

  //All of the possible pokemon that a player can have

  std::vector<pokemon_species::Species> all_pokemon_list;

};