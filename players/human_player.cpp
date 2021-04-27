//
// Created by Matthew on 4/23/2021.
//

#include "human_player.h"
#include "cinder/Log.h"

#include <iostream>

HumanPlayer::HumanPlayer(std::vector<pokemon_species::Species> starting_pokemon) {
  ready_pokemon_ = starting_pokemon;
}

HumanPlayer::HumanPlayer() {
}

void HumanPlayer::SetPokemonTeam(std::vector<pokemon_species::Species> team) {
  ready_pokemon_ = team;
}

void HumanPlayer::SendOutFirstPokemon(size_t starting_pokemon_index) {
  pokemon_species::Species& starter = ready_pokemon_.at(starting_pokemon_index);
  currently_in_battle_ = starter;
  ready_pokemon_.erase(ready_pokemon_.begin() + starting_pokemon_index);
}

std::vector<pokemon_species::Species> HumanPlayer::GetReadyPokemon() {
  return ready_pokemon_;
}

pokemon_species::Species HumanPlayer::GetCurrentlyInBattle() {
  return currently_in_battle_;
}