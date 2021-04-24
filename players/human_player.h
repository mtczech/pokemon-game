//
// Created by Matthew on 4/23/2021.
//

#ifndef FINAL_PROJECT_MTCZECH_HUMAN_PLAYER_H
#define FINAL_PROJECT_MTCZECH_HUMAN_PLAYER_H

#endif  // FINAL_PROJECT_MTCZECH_HUMAN_PLAYER_H

#include "../data_classes/pokemon_species.h"

class HumanPlayer {
 public:

  HumanPlayer();

  HumanPlayer(std::vector<pokemon_species::Species>);

  void HumanPlayer::SetPokemonTeam(std::vector<pokemon_species::Species> team);

 private:
  //The pokemon that the player has remaining
  std::vector<pokemon_species::Species> ready_pokemon_;

  pokemon_species::Species currently_in_battle_;

  std::vector<pokemon_species::Species> fainted_pokemon_;

  bool has_rocks_ = false;
};