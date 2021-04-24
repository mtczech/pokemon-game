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