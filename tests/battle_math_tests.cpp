//
// Created by Matthew on 4/17/2021.
//

#include <jsoncpp/json.h>

#include <catch2/catch.hpp>

#include "../game_data/engine_data.h"

TEST_CASE("Sample damage calculation math test") {
  EngineData test_data = EngineData("C:\\Cinder\\cinder_0.9.2_vc2015\\cinder_0.9.2_vc2015\\my-projects\\final-project-mtczech\\json_data_for_testing\\test_moves_json.json",
                                    "C:\\Cinder\\cinder_0.9.2_vc2015\\cinder_0.9.2_vc2015\\my-projects\\final-project-mtczech\\json_data_for_testing\\test_pokemon_json.json",

                                    "C:\\Cinder\\cinder_0.9.2_vc2015\\cinder_0.9.2_vc2015\\my-projects\\final-project-mtczech\\json_data_for_testing\\test_sets_json.json");
  SECTION("Test if move hits when it should") {
    pokemon_move::Move m;
    for (pokemon_move::Move move : test_data.GetMoves()) {
      if (move.name_ == "thunderbolt") {
        m = move;
      }
    }
    for (size_t i = 0; i < 200; i++) {
      REQUIRE(test_data.CheckIfMoveHits(*test_data.GetHumanPlayer().GetCurrentlyInBattle(), m));
    }
  }

  SECTION("Test if damage calculations are correct") {
    pokemon_move::Move m;
    for (pokemon_move::Move move : test_data.GetMoves()) {
      if (move.name_ == "origin-pulse") {
        m = move;
      }
    }
    pokemon_species::Species* cpu;
    pokemon_species::Species* user;
    for (pokemon_species::Species* s : test_data.GetAllPokemonList()) {
      if (s->species_name_ == "kyogre") {
        cpu = s;
      } else if (s->species_name_ == "arcanine") {
        user = s;
      }
    }
    REQUIRE(test_data.CalculateDamageDealt(*cpu, m, *user) > 441.7875);
    REQUIRE(test_data.CalculateDamageDealt(*cpu, m, *user) < 519.75);
  }
}