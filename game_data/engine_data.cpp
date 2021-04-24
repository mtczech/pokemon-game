//
// Created by Matthew on 4/17/2021.
//

#include "engine_data.h"

#include <ctime>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <nlohmann/json.hpp>

#include "../../include/_deps/json-src/include/nlohmann/json.hpp"
#include "../data_classes/pokemon_species.h"

using nlohmann::json;

EngineData::EngineData(){}

EngineData::EngineData(std::string move_json_path, std::string species_json_path, std::string set_json_path) {
  srand(unsigned (time(0)));
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
  std::vector<size_t> chosen_numbers;
  while (chosen_numbers.size() < 10) {
    size_t pokemon_index = (rand() % 15);
    if (std::count(chosen_numbers.begin(), chosen_numbers.end(), pokemon_index) == 0) {
      chosen_numbers.push_back(pokemon_index);
    }
  }
  //Code here from https://stackoverflow.com/questions/9811235/
  // best-way-to-split-a-vector-into-two-smaller-arrays
  size_t const team_size = chosen_numbers.size() / 2;
  std::vector<size_t> human_team(chosen_numbers.begin(), chosen_numbers.begin() + team_size);
  std::vector<size_t> computer_team(chosen_numbers.begin() + team_size, chosen_numbers.end());
  human_player.SetPokemonTeam(CreatePokemonTeam(human_team));
  computer_player.SetPokemonTeam(CreatePokemonTeam(computer_team));
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

std::vector<pokemon_species::Species> EngineData::CreatePokemonTeam(std::vector<size_t> indices) {
  std::vector<pokemon_species::Species> pokemon_team;
  for (size_t& index : indices) {
    pokemon_team.push_back(all_pokemon_list.at(index));
  }
  return pokemon_team;
}
