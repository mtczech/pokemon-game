//
// Created by Matthew on 4/20/2021.
//
#include "move.h"
#include <nlohmann/json.hpp>

using nlohmann::json;

namespace pokemon_move {

pokemon_move::Move::Move() {
}

void pokemon_move::Move::to_json(json& j, const pokemon_move::Move& p) {
  j = json{{"name", p.name_}, {"address", p.power_}, {"age", p.power_}};
}

void pokemon_move::Move::from_json(const json& j, pokemon_move::Move& move, size_t index) {
  j.at("moves").at(index).at("name").get_to(move.name_);
  if (j.at("moves").at(index).at("accuracy") != nullptr) {
    j.at("moves").at(index).at("accuracy").get_to(move.accuracy_);
  }
  if (j.at("moves").at(index).at("effect_chance") != nullptr) {
    j.at("moves").at(index)["effect_chance"].get_to(move.effect_chance_);
  }
  j.at("moves").at(index)["damage_class"].at("name").get_to(move.damage_class_name_);
  j.at("moves").at(index)["priority"].get_to(move.priority_);
  if (j.at("moves").at(index).at("power") != nullptr) {
    j.at("moves").at(index)["power"].get_to(move.power_);
  }
  if (j.at("moves").at(index).at("meta") != nullptr &&
      j.at("moves").at(index).at("meta").at("ailment") != nullptr) {
    j.at("moves").at(index).at("meta").at("ailment")["name"].get_to(move.ailment_name_);
  }
  if (j.at("moves").at(index).at("meta") != nullptr) {
    j.at("moves").at(index).at("meta").at("category")["name"].get_to(move.category_name_);
    j.at("moves").at(index).at("meta")["ailment_chance"].get_to(move.ailment_chance_);
    j.at("moves").at(index).at("meta")["healing"].get_to(move.healing_);
    j.at("moves").at(index).at("meta")["drain"].get_to(move.drain_);
    if (j.at("moves").at(index).at("meta").at("min_hits") != nullptr) {
      j.at("moves").at(index).at("meta")["min_hits"].get_to(move.min_hits_);
    }
    if (j.at("moves").at(index).at("meta").at("max_hits") != nullptr) {
      j.at("moves").at(index).at("meta")["max_hits"].get_to(move.min_hits_);
    }
    j.at("moves").at(index).at("meta")["flinch_chance"].get_to(move.flinch_chance_);
    j.at("moves").at(index).at("meta")["stat_chance"].get_to(move.stat_chance_);
  }
  if (j.at("moves").at(index).at("stat_changes") != nullptr &&
      j.at("moves").at(index).at("stat_changes") != ""
      && j.at("moves").at(index).at("stat_changes").size() != 0) {
    j.at("moves").at(index).at("stat_changes").at(0).at("stat")["name"].get_to(move.stat_);
    j.at("moves").at(index).at("stat_changes").at(0).at("change").get_to(move.change_);
  }
  j.at("moves").at(index).at("type")["name"].get_to(move.type_);
}

}