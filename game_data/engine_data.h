#pragma once

#ifndef FINAL_PROJECT_MTCZECH_ENGINE_DATA_H
#define FINAL_PROJECT_MTCZECH_ENGINE_DATA_H

#endif FINAL_PROJECT_MTCZECH_ENGINE_DATA_H

#include <nlohmann/json.hpp>
#include <unordered_map>
#include <map>
#include <cinder/app/App.h>

#include "../data_classes/move.h"
#include "../data_classes/pokemon_species.h"
#include "..\players\human_player.h"
#include "..\players\computer_player.h"

class EngineData {
 public:
  EngineData();

  EngineData(std::string move_json_path, std::string species_json_path, std::string set_json_path);

  void EngineData::to_json(nlohmann::json& j, const pokemon_move::Move& move);

  //Function for converting JSON to a move
  void EngineData::from_json(const nlohmann::json& j, pokemon_move::Move& move);

  std::vector<pokemon_move::Move> EngineData::GetMoves();

  std::vector<pokemon_species::Species*> EngineData::GetAllPokemonList();

  /**
   * Function for finding a move given its name
   * @param move_name The name of the move being searched for
   * @return The move being searched for
   */

  pokemon_move::Move EngineData::FindMove(const std::string move_name);

  HumanPlayer& EngineData::GetHumanPlayer();

  ComputerPlayer& EngineData::GetComputerPlayer();

  std::unordered_map<std::string, std::unordered_map<std::string, float>>
  EngineData::GetTypeMatrix();

  //Function for setting up the type matrix for determining strengths and weaknesses
  //Type matrix is hard coded in since the type matchups do not change

  void EngineData::SetUpTypeMatrix();

  size_t EngineData::FindLeadIndex(std::vector<pokemon_species::Species*> v);

  /**
   * Adjusts the stats before every turn based on stat changes or ailments to the pokemon
   * @param pokemon the pokemon having its stats adjusted
   */

  void AdjustStats(pokemon_species::Species& pokemon);

  /**
   * Does the opposite of AdjustStats so that AdjustStats is not applied more than once
   * It reverses all the changes made by AdjustStats
   */

  void SetStatsBack(pokemon_species::Species& pokemon);

  /**
   * Function that returns an array of Pokemon with loaded movesets given an array of numbers
   */

  std::vector<pokemon_species::Species*> EngineData::CreatePokemonTeam(std::vector<size_t> indices);

  std::string EngineData::GetMessage();

  /**
   * Function to check whether a given move executes properly or misses
   */

  bool EngineData::CheckIfMoveHits(pokemon_species::Species& attacking,
                                   const pokemon_move::Move move);

  /**
   * Function to calculate damage dealt by a given move
   */

  size_t EngineData::CalculateDamageDealt(pokemon_species::Species attacking,
            pokemon_move::Move attack, pokemon_species::Species defending);

  /**
   * Function for getting the STAB of a move
   * (A move gets a 1.5x power bonus if it is the same type as the pokemon using it)
   */

  float EngineData::GetStab(pokemon_species::Species attacking, pokemon_move::Move attack);

  /**
   * Function for getting the damage multiplier of a move
   * based on the types of the defending pokemon
   */

  float EngineData::GetTypeMultiplier(pokemon_species::Species defending,
                                      pokemon_move::Move attack);

  /**
   * Function for determining whether or not an additional effect happens
   */

  bool EngineData::CheckChance(size_t percent);

  /**
   * Function for adding additional effects to a pokemon move
   */

  void EngineData::AddEffects(pokemon_species::Species& attacking, pokemon_species::Species& defending,
                              pokemon_move::Move& move);

  /**
   * Function for checking if the game is over
   */

  void EngineData::CheckIfGameOver();

  /**
   * Function to check who goes first
   */

  bool EngineData::HumanGoesFirst(pokemon_move::Move human_move, pokemon_move::Move computer_move);

  /**
   * Function for finding the best move for the computer player to use
   * @return the index of the move being used in the pokemon's moveset
   */

  size_t EngineData::FindBestComputerMove();

  bool EngineData::GetIsGameOver();

  void EngineData::ApplyMiscEffects(pokemon_species::Species* attacking, pokemon_move::Move move);

  /**
   * Function for determining how much damage Stealth Rock deals and dealing said damage
   */

  void EngineData::DealStealthRockDamage(pokemon_species::Species& damage_recipient);

 private:

  //All of the moves in the game

  std::vector<pokemon_move::Move> moves;

  //All of the possible pokemon that a player can have

  std::vector<pokemon_species::Species*> all_pokemon_list;

  //The human player

  HumanPlayer human_player;

  //The computer player

  ComputerPlayer computer_player;

  //The type matrix for showing which hits are super effective

  std::unordered_map<std::string, std::unordered_map<std::string, float>> type_matrix_;

  //A message about a move that has been used, it is meant to be passed to the interface

  std::string message_;

  //Probability variable for whether or not a move actually hits

  size_t kProbability = 4;

  //Damage constant based on level, since all pokemon here are level 100 this is 42

  size_t kDamageConstant = 42;

  //Function to check if the game is over

  bool is_game_over_ = false;
};