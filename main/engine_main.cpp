//
// Created by Matthew on 4/18/2021.
//

#include "../pokemon_engine_interface/pokemon_engine_interface.h"
using pokemon_interface::PokemonEngineInterface;

void prepareSettings(PokemonEngineInterface::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(PokemonEngineInterface, ci::app::RendererGl, prepareSettings);
