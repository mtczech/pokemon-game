//
// Created by Matthew on 4/21/2021.
//

#include "pokemon_species.h"
#include <nlohmann/json.hpp>

namespace pokemon_species {

//No reason not to use a magic number here, the formula for calculating HP is always constant
//Except for if you are using a Shedinja

pokemon_species::Species::Species() { }

size_t pokemon_species::Species::CalculateHPFromBase(size_t base_hp) {
  return (2 * base_hp) + 110;
}

size_t pokemon_species::Species::CalculateStatFromBase(size_t base_stat) {
  return (2 * base_stat) + 5;
}

void pokemon_species::Species::to_json(nlohmann::json &j,
                                              const pokemon_species::Species &p) {
  //This is never used, I do not need to convert anything into json, so no need to implement
}

void pokemon_species::Species::from_json(const nlohmann::json &j,
                                                pokemon_species::Species &created) {
  species_name_ = j.at("name");
  for (auto& stat : j.at("stats")) {
    if (stat.at("stat")["name"] == "hp") {
      hp_ = CalculateHPFromBase(stat.at("base_stat"));
      current_hp_ = hp_;
    } else {
      size_t base_stat = stat.at("base_stat");
      other_stats_.emplace(stat.at("stat")["name"],
                          CalculateStatFromBase(base_stat));
      stat_changes_.emplace(stat.at("stat")["name"], 0);
    }
  }
  for (auto& type : j.at("types")) {
    types_.push_back(type.at("type").at("name"));
  }
  front_sprite_ = "C:/Cinder/cinder_0.9.2_vc2015/cinder_0.9.2_vc2015/my-projects/final-project-mtczech/pokemon_images/"
                      + species_name_ + ".png";
}

}