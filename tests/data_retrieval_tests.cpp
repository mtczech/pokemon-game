//
// Created by Matthew on 4/17/2021.
//

#include <catch2/catch.hpp>

#include "../game_data/engine_data.h"

EngineData test_data = EngineData("C:\\Cinder\\cinder_0.9.2_vc2015\\cinder_0.9.2_vc2015\\my-projects\\final-project-mtczech\\json_data_for_testing\\test_moves_json.json",
                                  "C:\\Cinder\\cinder_0.9.2_vc2015\\cinder_0.9.2_vc2015\\my-projects\\final-project-mtczech\\json_data_for_testing\\test_pokemon_json.json",
                                  "C:\\Cinder\\cinder_0.9.2_vc2015\\cinder_0.9.2_vc2015\\my-projects\\final-project-mtczech\\json_data_for_testing\\test_sets_json.json");

TEST_CASE("Check to see that all of the data is properly retrieved") {
  SECTION("Check that there are the correct number of Pokemon") {
    REQUIRE(test_data.GetAllPokemonList().size() == 4);
  }

  SECTION("Check that there are the correct number of moves") {
    REQUIRE(test_data.GetMoves().size() == 16);
  }

  SECTION("Check to see that the move's power is correct") {
    REQUIRE(test_data.GetMoves().at(0).power_ == 150);
  }

  SECTION("Check to see all base stats are loaded correctly") {
    REQUIRE(test_data.GetAllPokemonList().at(0)->other_stats_.size() == 5);
  }

  SECTION("Check to see all base stats have the correct values") {
    REQUIRE(test_data.GetAllPokemonList().at(0)->other_stats_.at("attack") == 205);
  }

  SECTION("Check that each Pokemon has the correct moveset") {
    REQUIRE(test_data.GetAllPokemonList().at(0)->moves_.at(0).name_ == "water-spout");
  }

  SECTION("Check to see there are no duplicate pokemon") {
    std::vector<std::string> names;
    for (pokemon_species::Species* pokemon : test_data.GetAllPokemonList()) {
      if (names.size() != 0) {
        REQUIRE(std::count(names.begin(), names.end(), pokemon->species_name_) == 0);
      }
      names.push_back(pokemon->species_name_);
    }
  }

  SECTION("Check to see if the type matrix has been correctly created") {
    REQUIRE(test_data.GetTypeMatrix().at("ghost").at("normal") == 0);
    REQUIRE(test_data.GetTypeMatrix().at("fighting").at("psychic") == 2);

  }

  SECTION("Check if a move can do X4 damage against a dual typed pokemon") {
    REQUIRE(test_data.GetTypeMultiplier(*test_data.GetAllPokemonList().at(1),
                    test_data.GetAllPokemonList().at(0)->moves_.at(0)) == 4);
  }

  SECTION("Test if a move can do no damage") {
    REQUIRE(test_data.CalculateDamageDealt(*test_data.GetAllPokemonList().at(2),
            test_data.GetAllPokemonList().at(2)->moves_.at(0), *test_data.GetAllPokemonList().at(1)) == 0);
  }
}