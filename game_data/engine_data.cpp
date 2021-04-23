//
// Created by Matthew on 4/17/2021.
//

#include "engine_data.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "../../include/_deps/json-src/include/nlohmann/json.hpp"
#include "../data_classes/pokemon_species.h"

using nlohmann::json;

EngineData::EngineData(){}

EngineData::EngineData(std::string move_json_path, std::string species_json_path, std::string set_json_path) {
  std::ifstream file_input(move_json_path);
  json j;
  file_input >> j;
  for (size_t k = 0; k < j.at("moves").size(); k++) {
    pokemon_move::Move m = pokemon_move::Move();
    m.from_json(j, m, k);
    moves.push_back(m);
  }
  std::ifstream pokemon_file_input(species_json_path);
  json pokemon_species_json;
  pokemon_file_input >> pokemon_species_json;
  for (auto& pokemon : pokemon_species_json.at("pokemon")) {
    pokemon_species::Species species = pokemon_species::Species();
    species.from_json(pokemon, species);
    all_pokemon_list.push_back(species);
  }
  std::ifstream set_file_input(set_json_path);
  json pokemon_set_json;
  set_file_input >> pokemon_set_json;
  for (auto& set : pokemon_set_json.at("pokemon_sets")) {
    for (pokemon_species::Species& p : all_pokemon_list) {
      if (p.species_name_ == set.at("pokemon_name")) {
        for (auto& move_name : set.at("moves")) {
          p.moves_.push_back(FindMove(move_name.at("name")));
        }
      }
    }
  }
}

//n^4 complexity, glad my input sets are relatively small
//There is a better way, I'm sure

std::vector<pokemon_species::Species> EngineData::GetAllPokemonList() {
  return all_pokemon_list;
}

std::vector<pokemon_move::Move> EngineData::GetMoves() {
  return moves;
}

pokemon_move::Move EngineData::FindMove(const std::string move_name) {
  for (pokemon_move::Move& m : moves) {
    if (m.name_ == move_name) {
      return m;
    }
  }
  //The program should not get to here, throw exception
  throw "Program should not get to here";
}