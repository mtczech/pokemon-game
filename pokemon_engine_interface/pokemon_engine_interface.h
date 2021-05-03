//
// Created by Matthew on 4/18/2021.
//

#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "../game_data/engine_data.h"
#ifndef FINAL_PROJECT_MTCZECH_POKEMON_ENGINE_INTERFACE_H
#define FINAL_PROJECT_MTCZECH_POKEMON_ENGINE_INTERFACE_H

#endif  // FINAL_PROJECT_MTCZECH_POKEMON_ENGINE_INTERFACE_H

#include <string>
#include <iostream>



namespace pokemon_interface {

/**
 *
 */
class PokemonEngineInterface : public ci::app::App {
 public:
  PokemonEngineInterface();

  void draw() override;
  void update() override;
  void keyDown(ci::app::KeyEvent event) override;

  // provided that you can see the entire UI on your screen.
  const int kWindowSize = 2000;
  const int kMargin = 500;

  /**
   * Helper function for drawing a Pokemon on the screen given a Pokemon and area
   */

  void PokemonEngineInterface::DrawPokemon(pokemon_species::Species creature, ci::Area area);

  void PokemonEngineInterface::DrawPokemonHealth(pokemon_species::Species creature, ci::vec2 position);

  void PokemonEngineInterface::WritePokemonNames(
      std::vector<pokemon_species::Species*> creatures, ci::vec2 position);

  void PokemonEngineInterface::ExecuteMove(size_t input, pokemon_species::Species* attacking,
                                           pokemon_species::Species* defending);

  void PokemonEngineInterface::EndGame();

  void PokemonEngineInterface::RunFullTurn(size_t user_move_index, size_t cpu_move_index);

 private:
  EngineData engine_data_;

  //Area taken up by the image of the user pokemon

  ci::Area kUserPokemonArea = ci::Area(ci::vec2(0, 250), ci::vec2(250, 500));

  //Area taken up by the image of the computer pokemon

  ci::Area kComputerPokemonArea = ci::Area(
      ci::vec2(350, 250), ci::vec2(600, 500));

  //A message displayed on the screen, because I don't think you can
  //display messages on the console with Cinder

  std::string message_ = "Your pokemon are on the left, the computer pokemon are on the right \n";
};

}  // namespace pokemon_interface