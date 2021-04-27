//
// Created by Matthew on 4/23/2021.
//

#include "../players/computer_player.h"

ComputerPlayer::ComputerPlayer(std::vector<pokemon_species::Species> starting_pokemon) {
  ready_pokemon_ = starting_pokemon;
}

ComputerPlayer::ComputerPlayer() {
}

void ComputerPlayer::SetPokemonTeam(std::vector<pokemon_species::Species> team) {
  ready_pokemon_ = team;
}

void ComputerPlayer::SendOutFirstPokemon(size_t starting_pokemon_index) {
  pokemon_species::Species& starter = ready_pokemon_.at(starting_pokemon_index);
  currently_in_battle_ = starter;
  ready_pokemon_.erase(ready_pokemon_.begin() + starting_pokemon_index);
}

pokemon_species::Species ComputerPlayer::GetCurrentlyInBattle() {
  return currently_in_battle_;
}

std::vector<pokemon_species::Species> ComputerPlayer::GetReadyPokemon() {
  return ready_pokemon_;
}