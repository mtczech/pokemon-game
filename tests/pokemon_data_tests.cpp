//
// Created by Matthew on 4/17/2021.
//
#pragma once

#include <catch2/catch.hpp>

#include "../game_data/engine_data.h"
#include "../pokemon_engine_interface/pokemon_engine_interface.h"

TEST_CASE("Just setting up the tests") {
  EngineData interface_test_data = EngineData("C:\\Cinder\\cinder_0.9.2_vc2015\\cinder_0.9.2_vc2015\\my-projects\\final-project-mtczech\\json_data_for_testing\\test_moves_json.json",
                                              "C:\\Cinder\\cinder_0.9.2_vc2015\\cinder_0.9.2_vc2015\\my-projects\\final-project-mtczech\\json_data_for_testing\\test_pokemon_json.json",
                                              "C:\\Cinder\\cinder_0.9.2_vc2015\\cinder_0.9.2_vc2015\\my-projects\\final-project-mtczech\\json_data_for_testing\\test_sets_json.json");
  SECTION("Check to see if a Pokemon is gone when it faints") {
    pokemon_species::Species* s = interface_test_data.GetHumanPlayer().GetCurrentlyInBattle();
    interface_test_data.GetHumanPlayer().GetCurrentlyInBattle()->current_hp_ = 0;
    interface_test_data.GetHumanPlayer().CheckIfPokemonFainted();
    REQUIRE(interface_test_data.GetHumanPlayer().GetCurrentlyInBattle() != s);
  }

  SECTION("Check to see a pokemon's hp cannot go above its max") {
    pokemon_species::Species* healing;
    pokemon_species::Species* defending;
    for (pokemon_species::Species* poke : interface_test_data.GetAllPokemonList()) {
      if (poke->species_name_ == "arcanine") {
        healing = poke;
      } else if (poke->species_name_ == "golem") {
        defending = poke;
      }
    }
    interface_test_data.AddEffects(*healing, *defending, healing->moves_.at(3));
    REQUIRE(healing->current_hp_ == healing->hp_);
    for (pokemon_species::Species* s : interface_test_data.GetAllPokemonList()) {
      delete s;
    }
  }

  SECTION("Check to see the game is over when one side has no pokemon remaining") {
    interface_test_data.GetHumanPlayer().GetReadyPokemon().clear();
    interface_test_data.GetHumanPlayer().GetCurrentlyInBattle()->current_hp_ = 0;
    interface_test_data.CheckIfGameOver();
    REQUIRE(interface_test_data.GetIsGameOver());
    for (pokemon_species::Species* s : interface_test_data.GetAllPokemonList()) {
      delete s;
    }
  }

  SECTION("Check switching pokemon out works properly") {
    pokemon_species::Species* s = interface_test_data.GetHumanPlayer().GetCurrentlyInBattle();
    interface_test_data.GetHumanPlayer().SwitchPokemon(0);
    REQUIRE(s != interface_test_data.GetHumanPlayer().GetCurrentlyInBattle());
  }

  SECTION("No errors if switch move used with 1 pokemon left") {
    interface_test_data.GetHumanPlayer().GetReadyPokemon().clear();
    pokemon_move::Move m;
    for (pokemon_move::Move move : interface_test_data.GetMoves()) {
      if (move.name_ == "volt-switch") {
        m = move;
      }
    }
    pokemon_species::Species* p = interface_test_data.GetHumanPlayer().GetCurrentlyInBattle();
    interface_test_data.ApplyMiscEffects(p, m);
    REQUIRE(interface_test_data.GetHumanPlayer().GetCurrentlyInBattle() == p);
    for (pokemon_species::Species* s : interface_test_data.GetAllPokemonList()) {
      delete s;
    }
  }

  SECTION("Check to see stat changes work properly when being added") {
    pokemon_species::Species* p = interface_test_data.GetHumanPlayer().GetCurrentlyInBattle();
    size_t p_attack = p->other_stats_.at("attack");
    p->stat_changes_.at("attack") = 1;
    interface_test_data.AdjustStats(*p);
    REQUIRE(p->other_stats_.at("attack") == Approx(size_t (p_attack * 1.5)).epsilon(1));
    interface_test_data.SetStatsBack(*p);
  }

  SECTION("Stat changes reset properly after every turn") {
    pokemon_species::Species* p = interface_test_data.GetHumanPlayer().GetCurrentlyInBattle();
    size_t p_attack = p->other_stats_.at("attack");
    p->stat_changes_.at("attack") = 1;
    interface_test_data.AdjustStats(*p);
    REQUIRE(p->other_stats_.at("attack") == Approx(size_t (p_attack * 1.5)).epsilon(1));
    interface_test_data.SetStatsBack(*p);
    REQUIRE(p->other_stats_.at("attack") == Approx(p_attack).epsilon(1));
  }

  SECTION("Test Stealth Rock actually does damage") {
    interface_test_data.GetComputerPlayer().SetRocks();
    interface_test_data.GetComputerPlayer().GetCurrentlyInBattle()->current_hp_ = 0;
    interface_test_data.GetComputerPlayer().CheckIfPokemonFainted();
    REQUIRE(interface_test_data.GetComputerPlayer().GetCurrentlyInBattle()->current_hp_ !=
                interface_test_data.GetComputerPlayer().GetCurrentlyInBattle()->hp_);
  }

  SECTION("Test Explosion faints the user") {
    pokemon_move::Move explosion;
    for (pokemon_move::Move m : interface_test_data.GetMoves()) {
      if (m.name_ == "explosion") {
        explosion = m;
        break;
      }
    }
    interface_test_data.ApplyMiscEffects(
        interface_test_data.GetHumanPlayer().GetCurrentlyInBattle(), explosion);
    REQUIRE(interface_test_data.GetHumanPlayer().GetCurrentlyInBattle()->current_hp_ == 0);
  }

  SECTION("Test a pokemon that dies from a move it uses leaves the battlefield") {
    pokemon_move::Move explosion;
    for (pokemon_move::Move m : interface_test_data.GetMoves()) {
      if (m.name_ == "explosion") {
        explosion = m;
        break;
      }
    }
    interface_test_data.ApplyMiscEffects(
        interface_test_data.GetHumanPlayer().GetCurrentlyInBattle(), explosion);
    pokemon_species::Species* p = interface_test_data.GetHumanPlayer().GetCurrentlyInBattle();
    REQUIRE(interface_test_data.GetHumanPlayer().GetCurrentlyInBattle()->current_hp_ == 0);
    interface_test_data.GetHumanPlayer().CheckIfPokemonFainted();
    REQUIRE(p != interface_test_data.GetHumanPlayer().GetCurrentlyInBattle());
  }
}
