//
// Created by Matthew on 4/17/2021.
//

#include <catch2/catch.hpp>

#include "../game_data/engine_data.h"

TEST_CASE("Sample data retrieval test") {
  EngineData test_data = EngineData("C:\\Cinder\\cinder_0.9.2_vc2015\\cinder_0.9.2_vc2015\\my-projects\\final-project-mtczech\\json_data_for_testing\\test_json_stealth_rock.json",
      "C:\\Cinder\\cinder_0.9.2_vc2015\\cinder_0.9.2_vc2015\\my-projects\\final-project-mtczech\\json_data_for_testing\\test_json_magikarp.json",
                                    "nothing here yet");
  SECTION("Check that there are the correct number of Pokemon") {
    REQUIRE(test_data.GetAllPokemonList().size() == 1);
  }

  SECTION("Check that there are the correct number of moves") {
    REQUIRE(test_data.GetMoves().size() == 1);
  }

  SECTION("Check to see that the move's power is correct") {
    REQUIRE(test_data.GetMoves().at(0).power_ == 0);
  }

  SECTION("Check to see all base stats are loaded correctly") {
    REQUIRE(test_data.GetAllPokemonList().at(0).other_stats_.size() == 5);
  }

  SECTION("Check to see all base stats have the correct values") {
    REQUIRE(test_data.GetAllPokemonList().at(0).other_stats_.at("attack") == 25);
  }
}