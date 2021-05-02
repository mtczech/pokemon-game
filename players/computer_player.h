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

  ComputerPlayer(std::vector<pokemon_species::Species*> starting_pokemon);

  void ComputerPlayer::SetPokemonTeam(std::vector<pokemon_species::Species*> team);

  void ComputerPlayer::SendOutFirstPokemon(size_t starting_pokemon_index);

  pokemon_species::Species* ComputerPlayer::GetCurrentlyInBattle();

  std::vector<pokemon_species::Species*> ComputerPlayer::GetReadyPokemon();

  std::vector<pokemon_species::Species*> ComputerPlayer::GetFaintedPokemon();

  /**
   * Sets up stealth rock on the computer's side of the field
   */

  void ComputerPlayer::SetRocks();

  /**
   * Removes rocks from the computer's side of the field
   */

  void ComputerPlayer::RemoveRocks();

  /**
   * Checks if the current pokemon is fainted for the computer player
   */

  bool ComputerPlayer::CheckIfPokemonFainted();

  bool ComputerPlayer::GetHasRocks();

  void ComputerPlayer::DetermineCurrentlyInBattle();

  void ComputerPlayer::SetCurrentlyInBattle(pokemon_species::Species* pokemon);

 private:
  //The pokemon that the computer player has remaining
  std::vector<pokemon_species::Species*> ready_pokemon_;

  pokemon_species::Species* currently_in_battle_;

  std::vector<pokemon_species::Species*> fainted_pokemon_;

  bool has_rocks_ = false;
};