#ifndef FINAL_PROJECT_MTCZECH_ENGINE_DATA_H
#define FINAL_PROJECT_MTCZECH_ENGINE_DATA_H

#endif FINAL_PROJECT_MTCZECH_ENGINE_DATA_H

#include <C:\Cinder\cinder_0.9.2_vc2015\cinder_0.9.2_vc2015\my-projects\final-project-mtczech\httplib\httplib.h>

#include <nlohmann/json.hpp>

#include "../data_classes/move.h"

namespace pokemon_move {

class EngineData {
 public:
  EngineData();

  void pokemon_move::EngineData::to_json(nlohmann::json& j, const pokemon_move::Move& move);

  //Function for converting JSON to a move
  void pokemon_move::EngineData::from_json(const nlohmann::json& j, pokemon_move::Move& move);

 private:

  //All of the moves in the game

  std::vector<Move> moves;

};

}