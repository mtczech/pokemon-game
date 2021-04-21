//
// Created by Matthew on 4/20/2021.
//
#pragma once

#ifndef FINAL_PROJECT_MTCZECH_MOVE_H
#define FINAL_PROJECT_MTCZECH_MOVE_H

#endif  // FINAL_PROJECT_MTCZECH_MOVE_H

#include <nlohmann/json.hpp>
#include <boost/optional.hpp>

namespace pokemon_move {

// This is just a data class, it needs to be public so other data classes can access it
class Move {
 public:
  Move();

  void pokemon_move::Move::to_json(nlohmann::json& j, const pokemon_move::Move& move);

  //Function for converting JSON to a move
  void pokemon_move::Move::from_json(const nlohmann::json& j, pokemon_move::Move& move, size_t i);

  std::string name_;

  size_t accuracy_ = 100;

  int effect_chance_ = 0;

  int priority_ = 0;

  size_t power_ = 0;

  std::string damage_class_name_;

  std::string ailment_name_;

  std::string category_name_;

  size_t ailment_chance_;

  size_t min_hits_;

  size_t max_hits_;

  int drain_;

  size_t healing_;

  size_t flinch_chance_;

  size_t stat_chance_;

  std::vector<std::string> stat_;

  std::vector<int> change_;

  std::string type_;
};

}