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



namespace pokemon_interface {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class PokemonEngineInterface : public ci::app::App {
 public:
  PokemonEngineInterface();

  void draw() override;
  void update() override;

  // provided that you can see the entire UI on your screen.
  const int kWindowSize = 1000;
  const int kMargin = 100;

 private:
  EngineData engine_data_;
};

}  // namespace pokemon_interface