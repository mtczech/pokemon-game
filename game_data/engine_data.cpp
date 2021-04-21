//
// Created by Matthew on 4/17/2021.
//

#include <iostream>
#include <fstream>
#include "engine_data.h"

#include <nlohmann/json.hpp>

#include "../../include/_deps/json-src/include/nlohmann/json.hpp"

using nlohmann::json;

pokemon_move::EngineData::EngineData() {
  std::ifstream file_input("C:\\Cinder\\cinder_0.9.2_vc2015\\cinder_0.9.2_vc2015\\my-projects\\final-project-mtczech\\necessary_json_data\\json_for_all_moves.json");
  json j;
  file_input >> j;
  for (size_t k = 0; k < j.at("moves").size(); k++) {
    pokemon_move::Move m = pokemon_move::Move();
    m.from_json(j, m, k);
    moves.push_back(m);
  }
}


