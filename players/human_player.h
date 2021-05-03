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

  HumanPlayer(std::vector<pokemon_species::Species*>);

  /**
   * Function for setting up the player's pokemon team
   * @param team the pokemon being put into the player's party
   */

  void HumanPlayer::SetPokemonTeam(std::vector<pokemon_species::Species*> team);

  void HumanPlayer::SendOutFirstPokemon(size_t starting_pokemon_index);

  std::vector<pokemon_species::Species*> HumanPlayer::GetReadyPokemon();

  pokemon_species::Species* HumanPlayer::GetCurrentlyInBattle();

  std::vector<pokemon_species::Species*> HumanPlayer::GetFaintedPokemon();

  /**
   * Sets up stealth rock
   */

  void HumanPlayer::SetRocks();

  /**
   * Removes stealth rock
   */

  void HumanPlayer::RemoveRocks();

  void HumanPlayer::CheckIfPokemonFainted();

  bool HumanPlayer::GetHasRocks();

  void HumanPlayer::SwitchPokemon(size_t pokemon_index);

 private:
  //The pokemon that the player has remaining
  std::vector<pokemon_species::Species*> ready_pokemon_;

  pokemon_species::Species* currently_in_battle_;

  std::vector<pokemon_species::Species*> fainted_pokemon_;

  bool has_rocks_ = false;
};