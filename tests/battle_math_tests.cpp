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

  }

  SECTION("Test if damage calculations are correct") {

  }

  SECTION("Test Flare Blitz recoil is correct") {

  }
}