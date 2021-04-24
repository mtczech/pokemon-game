//
// Created by Matthew on 4/23/2021.
//


#include "human_player.h"

HumanPlayer::HumanPlayer(std::vector<pokemon_species::Species> starting_pokemon) {
  ready_pokemon_ = starting_pokemon;
}

HumanPlayer::HumanPlayer() {
}

void HumanPlayer::SetPokemonTeam(std::vector<pokemon_species::Species> team) {
  ready_pokemon_ = team;
}
