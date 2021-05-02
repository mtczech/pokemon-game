//
// Created by Matthew on 4/17/2021.
//

#include "engine_data.h"

#include <ctime>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <map>

#include "../data_classes/pokemon_species.h"

using nlohmann::json;

EngineData::EngineData(){}

EngineData::EngineData(std::string move_json_path, std::string species_json_path, std::string set_json_path) {
  srand(unsigned (time(0)));
  //Generates all of the pokemon moves from the first json
  std::ifstream file_input(move_json_path);
  json j;
  file_input >> j;
  for (size_t k = 0; k < j.at("moves").size(); k++) {
    pokemon_move::Move m = pokemon_move::Move();
    m.from_json(j, m, k);
    moves.push_back(m);
  }
  //Generates all of the pokemon from the second json
  std::ifstream pokemon_file_input(species_json_path);
  json pokemon_species_json;
  pokemon_file_input >> pokemon_species_json;
  for (auto& pokemon : pokemon_species_json.at("pokemon")) {
    pokemon_species::Species* species = new pokemon_species::Species();
    species->from_json(pokemon, (*species));
    all_pokemon_list.push_back(species);
  }
  //Uses the third json to map the pokemon to their movesets
  std::ifstream set_file_input(set_json_path);
  json pokemon_set_json;
  set_file_input >> pokemon_set_json;
  for (auto& set : pokemon_set_json.at("pokemon_sets")) {
    for (pokemon_species::Species* p : all_pokemon_list) {
      if (p->species_name_ == set.at("pokemon_name")) {
        for (auto& move_name : set.at("moves")) {
          p->moves_.push_back(FindMove(move_name.at("name")));
        }
      }
    }
  }
  //Randomly selects 10 out of the 15 pokemon, assigns 5 to the player and 5 to the computer
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
  type_matrix_ = std::unordered_map<std::string, std::unordered_map<std::string, float>>();
  SetUpTypeMatrix();
  human_player.SendOutFirstPokemon(FindLeadIndex(human_player.GetReadyPokemon()));
  computer_player.SendOutFirstPokemon(FindLeadIndex((computer_player.GetReadyPokemon())));
  std::cout << "test" << std::endl;
}

//n^4 complexity, glad my input sets are relatively small
//There is a better way, I'm sure

std::vector<pokemon_species::Species*> EngineData::GetAllPokemonList() {
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

std::vector<pokemon_species::Species*> EngineData::CreatePokemonTeam(std::vector<size_t> indices) {
  std::vector<pokemon_species::Species*> pokemon_team;
  for (size_t& index : indices) {
    pokemon_team.push_back(all_pokemon_list.at(index));
  }
  return pokemon_team;
}

std::unordered_map<std::string, std::unordered_map<std::string, float>> EngineData::GetTypeMatrix() {
  return type_matrix_;
}

void EngineData::SetUpTypeMatrix() {
  std::ifstream matrix_json_file("C:\\Cinder\\cinder_0.9.2_vc2015\\cinder_0.9.2_vc2015\\my-projects\\final-project-mtczech\\necessary_json_data\\type_matrix_json.json");
  json matrix_json;
  matrix_json_file >> matrix_json;
  for (auto& pokemon_type : matrix_json["types"]) {
    std::unordered_map<std::string, float> type_matchups = std::unordered_map<std::string, float>();
    for (auto& super_effective : pokemon_type.at("damage_relations").at("double_damage_from")) {
      type_matchups.emplace(std::pair<std::string, float> {super_effective["name"], float(2)});
    }
    for (auto& not_very_effective : pokemon_type.at("damage_relations").at("half_damage_from")) {
      type_matchups.emplace(std::pair<std::string, float> {not_very_effective["name"], float(0.5)});
    }
    if (pokemon_type.at("damage_relations").at("no_damage_from").size() != 0) {
      for (auto& immune : pokemon_type.at("damage_relations").at("no_damage_from")) {
        type_matchups.emplace(std::pair<std::string, float> {immune["name"], float(0)});
      }
    }
    type_matrix_.emplace(std::pair<std::string, std::unordered_map<std::string, float>>
                         {pokemon_type["name"], type_matchups});
  }
}

HumanPlayer EngineData::GetHumanPlayer() {
  return human_player;
}

ComputerPlayer EngineData::GetComputerPlayer() {
  return computer_player;
}

size_t EngineData::FindLeadIndex(std::vector<pokemon_species::Species*> v) {
  for (size_t i = 0; i < v.size(); i++) {
    for (pokemon_move::Move m : v.at(i)->moves_) {
      if (m.name_ == "stealth-rock") {
        return i;
      }
    }
  }
  return (rand() % 5);
}

std::string EngineData::GetMessage() {
  return message_;
}

bool EngineData::CheckIfMoveHits(pokemon_species::Species& attacking, const pokemon_move::Move move) {
  srand(unsigned (time(0)));
  size_t ailment_chance = rand() % kProbability;
  size_t paralysis_chance = 1;
  if (ailment_chance < paralysis_chance && attacking.ailment_ == "paralysis") {
    message_ = attacking.species_name_ + " is fully paralyzed!";
    return false;
  }
  size_t confusion_chance = 1;
  if (ailment_chance < confusion_chance && attacking.ailment_ == "confusion") {
    message_ = attacking.species_name_ + " is confused and hurt itself!";
    attacking.current_hp_ = std::max(0, attacking.current_hp_ - 40);
    return false;
  }
  size_t sleep_chance = 2;
  if (ailment_chance < sleep_chance && attacking.ailment_ == "sleep") {
    message_ = attacking.species_name_ + " is fast asleep.";
    return false;
  } else if (attacking.ailment_ == "sleep") {
    message_ = attacking.species_name_ + " woke up!";
    attacking.ailment_ = "none";
  }
  size_t freeze_chance = 3;
  if (ailment_chance < freeze_chance && attacking.ailment_ == "freeze") {
    message_ = attacking.species_name_ + " is frozen solid!";
    return false;
  } else if (attacking.ailment_ == "freeze") {
    message_ = attacking.species_name_ + " thawed out!";
    attacking.ailment_ = "none";
  }
  size_t miss_chance = rand() % 100;
  if (move.accuracy_ <= miss_chance) {
    message_ = attacking.species_name_ + "'s attack missed!";
    return false;
  }
  return true;
}

void EngineData::AdjustStats(pokemon_species::Species pokemon) {
  if (pokemon.ailment_ == "burn") {
    pokemon.other_stats_.at("attack") = size_t
        (std::floorf(float (pokemon.other_stats_.at("attack")) * float (0.5)));
  } else if (pokemon.ailment_ == "paralysis") {
    pokemon.other_stats_.at("speed") = size_t
        (std::floorf(float (pokemon.other_stats_.at("speed")) * float (0.25)));
  }
  //Code taken from https://www.lonecpluspluscoder.com/2015/08/13/
  //an-elegant-way-to-extract-keys-from-a-c-map/
  std::vector<std::string> stats;
  for (auto& s : pokemon.other_stats_) {
    stats.push_back(s.first);
  }
  for (std::string stat : stats) {
    float stat_changed = float (pokemon.other_stats_.at(stat));
    if (pokemon.stat_changes_.at(stat) < 0) {
      float multiplier = 2 / float (2 - pokemon.stat_changes_.at(stat));
      pokemon.other_stats_.at(stat) = size_t (std::ceilf(stat_changed *= multiplier));
    } else if (pokemon.stat_changes_.at(stat) > 0) {
      float multiplier = float (2 + pokemon.stat_changes_.at(stat)) / 2;
      pokemon.other_stats_.at(stat) = size_t (std::floorf(stat_changed *= multiplier));
    }
  }
}

void EngineData::SetStatsBack(pokemon_species::Species pokemon) {
  if (pokemon.ailment_ == "burn") {
    pokemon.other_stats_.at("attack") = size_t
        (std::floorf(float (pokemon.other_stats_.at("attack")) * 2));
  } else if (pokemon.ailment_ == "paralysis") {
    pokemon.other_stats_.at("speed") = size_t
        (std::floorf(float (pokemon.other_stats_.at("speed")) * 4));
  }
  std::vector<std::string> stats;
  for (auto& s : pokemon.other_stats_) {
    stats.push_back(s.first);
  }
  for (std::string stat : stats) {
    float stat_changed = float (pokemon.other_stats_.at(stat));
    if (pokemon.stat_changes_.at(stat) < 0) {
      float multiplier = float (2 - pokemon.stat_changes_.at(stat)) / 2;
      pokemon.other_stats_.at(stat) = size_t (std::ceilf(stat_changed *= multiplier));
    } else if (pokemon.stat_changes_.at(stat) > 0) {
      float multiplier =  2 / float (2 + pokemon.stat_changes_.at(stat));
      pokemon.other_stats_.at(stat) = size_t (std::floorf(stat_changed *= multiplier));
    }
  }
}

size_t EngineData::CalculateDamageDealt(pokemon_species::Species attacking,
         pokemon_move::Move attack, pokemon_species::Species defending) {
  float stats_multiplier;
  if (attack.damage_class_name_ == "physical") {
    stats_multiplier = float (attacking.other_stats_.at("attack")) /
                       float (defending.other_stats_.at("defense"));
  } else if (attack.damage_class_name_ == "special") {
    stats_multiplier = float (attacking.other_stats_.at("special-attack")) /
                       float (defending.other_stats_.at("special-defense"));
  } else {
    return 0;
  }
  float base_damage = ((float (kDamageConstant * attack.power_) * stats_multiplier) /
                            float (50)) + float (2);
  float rng_multiplier = float (unsigned (rand() % 16) + 85) / float (100);
  float final_damage = base_damage * rng_multiplier;
  final_damage *= GetStab(attacking, attack);
  final_damage *= GetTypeMultiplier(defending, attack);
  size_t recoil = unsigned (std::floor((final_damage * attack.drain_) / 100));
  attacking.current_hp_ += std::max(0, attacking.current_hp_ += recoil);
  return size_t (std::ceilf(final_damage));
}

float EngineData::GetStab(pokemon_species::Species attacking, pokemon_move::Move attack) {
  for (std::string type : attacking.types_) {
    if (type == attack.type_) {
      return 1.5;
    }
  }
  return 1;
}

float EngineData::GetTypeMultiplier(pokemon_species::Species defending,
                                    pokemon_move::Move attack) {
  float type_multiplier = 1;
  for (std::string type : defending.types_) {
    if (type_matrix_.at(type).count(attack.type_)) {
      type_multiplier *= type_matrix_.at(type).at(attack.type_);
    }
  }
  return type_multiplier;
}

bool EngineData::CheckChance(size_t percent) {
  auto r = unsigned (rand() % 100);
  return percent > r;
}

void EngineData::AddEffects(pokemon_species::Species& attacking,
                            pokemon_species::Species& defending, pokemon_move::Move& move) {
  //As much as I would love to do a switch function here, you cannot do it with strings in c++
  if (move.category_name_ == "field-effect"
      && attacking.species_name_ == human_player.GetCurrentlyInBattle()->species_name_) {
    computer_player.SetRocks();
    message_ = "Rocks are ready to dig into opposing Pokemon!";
  } else if (move.category_name_ == "field-effect") {
    human_player.SetRocks();
    message_ = "Rocks are ready to dig into your Pokemon!";
  }
  if (move.category_name_ == "damage+raise" || move.category_name_ == "net-good-stats") {
    for (size_t i = 0; i < move.stat_.size(); i++) {
      attacking.stat_changes_.at(move.stat_.at(i)) += move.change_.at(i);
    }
  }
  if (defending.ailment_ == "none" && move.category_name_ == "ailment") {
    defending.ailment_ = move.ailment_name_;
  }
  if (move.category_name_ == "damage+ailment" && defending.ailment_ == "none") {
    if (CheckChance(move.ailment_chance_)) {
      defending.ailment_ = move.ailment_name_;
    }
  }
  if (move.category_name_ == "unique") {
    human_player.RemoveRocks();
    computer_player.RemoveRocks();
    message_ = "Both sides no longer have rocks";
  }
  if (move.category_name_ == "damage+lower" && CheckChance(move.stat_chance_)) {
    for (size_t i = 0; i < move.stat_.size(); i++) {
      defending.stat_changes_.at(move.stat_.at(i)) += move.change_.at(i);
    }
  }
  if (move.category_name_ == "heal") {
    size_t hp_after_healing = attacking.current_hp_ += ((attacking.hp_ * move.healing_) / 100);
    attacking.current_hp_ = std::min(attacking.hp_, hp_after_healing);
  }
}

void EngineData::CheckIfGameOver() {
  if (human_player.GetReadyPokemon().size() == 0 &&
      human_player.GetCurrentlyInBattle()->current_hp_ <= 0) {
    message_ = "Game over, better luck next time";
    is_game_over_ = true;
  } else if (computer_player.GetReadyPokemon().size() == 0 &&
             computer_player.GetCurrentlyInBattle()->current_hp_ == 0) {
    message_ = "Congratulations! You are the Pokemon League Champion!";
    is_game_over_ = true;
  }
}

bool EngineData::HumanGoesFirst(pokemon_move::Move human_move, pokemon_move::Move computer_move) {
  AdjustStats((*human_player.GetCurrentlyInBattle()));
  AdjustStats((*computer_player.GetCurrentlyInBattle()));
  if (human_move.priority_ > computer_move.priority_) {
    return true;
  } else if (computer_move.priority_ > human_move.priority_) {
    return false;
  }
  bool returned = human_player.GetCurrentlyInBattle()->other_stats_.at("speed")
                  >= computer_player.GetCurrentlyInBattle()->other_stats_.at("speed");
  SetStatsBack((*human_player.GetCurrentlyInBattle()));
  SetStatsBack((*computer_player.GetCurrentlyInBattle()));
  return returned;
}

size_t EngineData::FindBestComputerMove() {
  size_t best_move_index = 0;
  size_t damage_dealt_by_best_move = 0;
  for (size_t i = 0; i < computer_player.GetCurrentlyInBattle()->moves_.size(); i++) {
    size_t damage = CalculateDamageDealt(*(computer_player.GetCurrentlyInBattle()),
          computer_player.GetCurrentlyInBattle()->moves_.at(i),
                                         (*human_player.GetCurrentlyInBattle()));
    if (damage >= damage_dealt_by_best_move) {
      best_move_index = i;
      damage_dealt_by_best_move = damage;
    }
  }
  return best_move_index;
}

bool EngineData::GetIsGameOver() {
  return is_game_over_;
}

void EngineData::DealStealthRockDamage(pokemon_species::Species& damage_recipient) {
  float damage_multiplier = 0.125;
  for (std::string& type : damage_recipient.types_) {
    if (type_matrix_.at("rock").find(type) != type_matrix_.at("rock").end()) {
      damage_multiplier *= type_matrix_.at("rock").at(type);
    }
  }
  int hp_after_damage = damage_recipient.current_hp_ -
                        int (std::ceil(float (damage_recipient.hp_) * damage_multiplier));
  damage_recipient.current_hp_ = std::max(0, hp_after_damage);
  human_player.CheckIfPokemonFainted();
  computer_player.CheckIfPokemonFainted();
}