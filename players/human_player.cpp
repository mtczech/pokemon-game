//
// Created by Matthew on 4/23/2021.
//

#include "human_player.h"
#include "cinder/Log.h"

#include <iostream>

HumanPlayer::HumanPlayer(std::vector<pokemon_species::Species*> starting_pokemon) {
  ready_pokemon_ = starting_pokemon;
}

HumanPlayer::HumanPlayer() {
}

void HumanPlayer::SetPokemonTeam(std::vector<pokemon_species::Species*> team) {
  ready_pokemon_ = team;
}

void HumanPlayer::SendOutFirstPokemon(size_t starting_pokemon_index) {
  pokemon_species::Species* starter = ready_pokemon_.at(starting_pokemon_index);
  currently_in_battle_ = starter;
  ready_pokemon_.erase(ready_pokemon_.begin() + starting_pokemon_index);
}

std::vector<pokemon_species::Species*> HumanPlayer::GetReadyPokemon() {
  return ready_pokemon_;
}

pokemon_species::Species* HumanPlayer::GetCurrentlyInBattle() {
  return currently_in_battle_;
}

void HumanPlayer::SetRocks() {
  if (!has_rocks_) {
    has_rocks_ = true;
  }
}

void HumanPlayer::RemoveRocks() {
  if (has_rocks_) {
    has_rocks_ = false;
  }
}

void HumanPlayer::CheckIfPokemonFainted() {
  if (currently_in_battle_->current_hp_ <= 0) {
    fainted_pokemon_.push_back(currently_in_battle_);
    if (ready_pokemon_.size() != 0) {
      currently_in_battle_ = nullptr;
      int r = rand() % ready_pokemon_.size();
      currently_in_battle_ = ready_pokemon_.at(r);
      ready_pokemon_.erase(ready_pokemon_.begin() + r);
    }
  }
}

bool HumanPlayer::GetHasRocks() {
  return has_rocks_;
}

std::vector<pokemon_species::Species*> HumanPlayer::GetFaintedPokemon() {
  return fainted_pokemon_;
}

void HumanPlayer::SwitchPokemon(size_t pokemon_index) {
  if (ready_pokemon_.size() > pokemon_index) {
    pokemon_species::Species* switched_out_pokemon = currently_in_battle_;
    currently_in_battle_ = nullptr;
    SendOutFirstPokemon(pokemon_index);
    std::cout << "You switched out " << switched_out_pokemon->species_name_ << " for " <<
        currently_in_battle_->species_name_ << std::endl;
    ready_pokemon_.push_back(switched_out_pokemon);
  } else {
    std::cout << "You do not have that pokemon ready" << std::endl;
  }
}