//
// Created by Matthew on 4/17/2021.
//
#include <catch2/catch.hpp>

#include "../game_data/engine_data.h"

TEST_CASE("Setting up the tests for strategy output") {
  EngineData interface_test_data = EngineData("C:\\Cinder\\cinder_0.9.2_vc2015\\cinder_0.9.2_vc2015\\my-projects\\final-project-mtczech\\json_data_for_testing\\test_moves_json.json",
                                              "C:\\Cinder\\cinder_0.9.2_vc2015\\cinder_0.9.2_vc2015\\my-projects\\final-project-mtczech\\json_data_for_testing\\test_pokemon_json.json",
                                              "C:\\Cinder\\cinder_0.9.2_vc2015\\cinder_0.9.2_vc2015\\my-projects\\final-project-mtczech\\json_data_for_testing\\test_sets_json.json");
  SECTION("The best move is selected") {
    pokemon_species::Species* cpu;
    pokemon_species::Species* user;
    for (pokemon_species::Species* s : interface_test_data.GetAllPokemonList()) {
      if (s->species_name_ == "kyogre") {
        cpu = s;
      } else if (s->species_name_ == "arcanine") {
        user = s;
      }
    }
    interface_test_data.GetComputerPlayer().SetCurrentlyInBattle(cpu);
    interface_test_data.GetHumanPlayer().SetCurrentlyInBattle(user);
    REQUIRE(interface_test_data.FindBestComputerMove() == 0);
  }
}
