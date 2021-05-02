//
// Created by Matthew on 4/17/2021.
//

#include "pokemon_engine_interface.h"
#include "cinder/gl/Texture.h"

pokemon_interface::PokemonEngineInterface::PokemonEngineInterface() {
  engine_data_ = EngineData("C:\\Cinder\\cinder_0.9.2_vc2015\\cinder_0.9.2_vc2015\\my-projects\\final-project-mtczech\\necessary_json_data\\json_for_all_moves.json",
                            "C:\\Cinder\\cinder_0.9.2_vc2015\\cinder_0.9.2_vc2015\\my-projects\\final-project-mtczech\\necessary_json_data\\json_for_all_pokemon.json",
                            "C:\\Cinder\\cinder_0.9.2_vc2015\\cinder_0.9.2_vc2015\\my-projects\\final-project-mtczech\\necessary_json_data\\pokemon_sets_json.json");
}

void pokemon_interface::PokemonEngineInterface::draw() {
  ci::Color("white");
  ci::gl::drawSolidRect(ci::Rectf (ci::vec2(0, 0), ci::vec2(650, 100)));
  ci::gl::drawString(message_, ci::vec2(0, 0), ci::Color("black"), ci::Font("Verdana", 20));
  DrawPokemon(user_pokemon_, kUserPokemonArea);
  DrawPokemon(computer_pokemon_, kComputerPokemonArea);
  DrawPokemonHealth(user_pokemon_, ci::vec2(0, 200));
  DrawPokemonHealth(computer_pokemon_, ci::vec2(325, 200));
  WritePokemonNames(user_ready_pokemon_, ci::vec2(0, 110));
  WritePokemonNames(computer_ready_pokemon_, ci::vec2(470, 110));
}

void pokemon_interface::PokemonEngineInterface::update() {
  user_pokemon_ = engine_data_.GetHumanPlayer().GetCurrentlyInBattle();
  computer_pokemon_ = engine_data_.GetComputerPlayer().GetCurrentlyInBattle();
  user_ready_pokemon_ = engine_data_.GetHumanPlayer().GetReadyPokemon();
  computer_ready_pokemon_ = engine_data_.GetComputerPlayer().GetReadyPokemon();
}

void pokemon_interface::PokemonEngineInterface::DrawPokemon(
    pokemon_species::Species creature, ci::Area area) {
  auto starting_image = ci::loadImage(ci::loadUrl(creature.front_sprite_));
  ci::gl::Texture2dRef starting_pokemon_image = ci::gl::Texture2d::create(starting_image);
  ci::gl::draw(starting_pokemon_image, area);
}

void pokemon_interface::PokemonEngineInterface::keyDown(ci::app::KeyEvent event) {
  switch (event.getChar()) {
    case '0':;
      //Put function to use move at index 0
  }
}

void pokemon_interface::PokemonEngineInterface::DrawPokemonHealth(
    pokemon_species::Species creature, ci::vec2 position) {
  ci::Color hp_color;
  if (float ((creature.current_hp_) / float (creature.hp_)) < 0.2) {
    hp_color = ci::Color("red");
  } else if (float ((creature.current_hp_) / float (creature.hp_)) < 0.5) {
    hp_color = ci::Color("yellow");
  } else {
    hp_color = ci::Color("green");
  }
  std::string output = std::to_string(creature.current_hp_) + "/" + std::to_string(creature.hp_);
  ci::gl::drawString(output, position, hp_color, ci::Font("Magneto", 80));
}

void pokemon_interface::PokemonEngineInterface::WritePokemonNames(
    std::vector<pokemon_species::Species> creatures, ci::vec2 position) {
  std::string message = "Pokemon remaining: \n";
  for (pokemon_species::Species creature : creatures) {
    message += creature.species_name_ + "\n";
  }
  ci::gl::drawString(message, position, ci::Color("white"), ci::Font("Verdana", 20));
}

void pokemon_interface::PokemonEngineInterface::ExecuteMove(
    size_t input, pokemon_species::Species& attacking, pokemon_species::Species& defending) {
  if (engine_data_.GetIsGameOver()) {
    return;
  }
  if (engine_data_.CheckIfMoveHits(attacking, attacking.moves_.at(input))) {
    engine_data_.AdjustStats(attacking);
    engine_data_.AdjustStats(defending);
    defending.current_hp_ = std::max(0, defending.current_hp_ -= engine_data_.CalculateDamageDealt(
        attacking, attacking.moves_.at(input), defending));
    system("pause");
    engine_data_.CheckIfGameOver();
    if (engine_data_.GetIsGameOver()) {
      return;
    }
    engine_data_.SetStatsBack(attacking);
    engine_data_.SetStatsBack(defending);
    engine_data_.AddEffects(attacking, defending, attacking.moves_.at(input));
    engine_data_.GetHumanPlayer().CheckIfPokemonFainted();
    engine_data_.GetComputerPlayer().CheckIfPokemonFainted();
  }
}