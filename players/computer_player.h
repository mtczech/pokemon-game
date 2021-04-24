//
// Created by Matthew on 4/23/2021.
//

#include <vector>
#include "../data_classes/pokemon_species.h"
#ifndef FINAL_PROJECT_MTCZECH_COMPUTER_PLAYER_H
#define FINAL_PROJECT_MTCZECH_COMPUTER_PLAYER_H

#endif  // FINAL_PROJECT_MTCZECH_COMPUTER_PLAYER_H

class ComputerPlayer {
 public:

  ComputerPlayer();

  ComputerPlayer(std::vector<pokemon_species::Species> starting_pokemon);

  void ComputerPlayer::SetPokemonTeam(std::vector<pokemon_species::Species> team);

 private:
  //The pokemon that the computer player has remaining
  std::vector<pokemon_species::Species> ready_pokemon_;

  pokemon_species::Species currently_in_battle_;

  std::vector<pokemon_species::Species> fainted_pokemon_;

  bool has_rocks_ = false;
};