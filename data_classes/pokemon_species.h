//
// Created by Matthew on 4/21/2021.
//
#pragma once

#include <string>
#include <vector>

#include "move.h"

#ifndef SPECIES_HEADER
#define SPECIES_HEADER

#endif  // FINAL_PROJECT_MTCZECH_POKEMON_SPECIES_H

namespace pokemon_species {

// This is just a data class, it needs to be public so other data classes can access it
class Species {
 public:
  pokemon_species::Species::Species();

  //I had to put this in bc it was part of the interface, I never use it
  void pokemon_species::Species::to_json(nlohmann::json& j,
                                                const pokemon_species::Species& p);

  //Function for converting JSON to a Pokemon
  /**
   *
   * @param j the json string being turned into pokemon data
   * @param created the pokemon having data added to it
   */
  void pokemon_species::Species::from_json(const nlohmann::json& j,
      pokemon_species::Species& created);

  /**
   * Function that takes in base HP and spits out the HP stat of a pokemon
   * @param base_hp the base hp stat for the pokemon
   * @return the calculated hp stat
   */
  size_t pokemon_species::Species::CalculateHPFromBase(size_t base_hp);

  /**
   * Function that takes in a base stat and spits out the computed stat of a pokemon
   * @param base_stat the base stat for the pokemon
   * @return the calculated stat
   */

  size_t pokemon_species::Species::CalculateStatFromBase(size_t base_stat);

  void pokemon_species::Species::AddResidualDamage();

  std::string front_sprite_;

  int current_hp_;

  std::string species_name_;

  size_t hp_;

  std::unordered_map<std::string, size_t> other_stats_;

  std::vector<std::string> types_;

  std::vector<pokemon_move::Move> moves_;

  std::unordered_map<std::string, int> stat_changes_;

  std::string ailment_ = "none";
};

}