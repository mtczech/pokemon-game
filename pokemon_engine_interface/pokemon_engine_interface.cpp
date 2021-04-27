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
}

void pokemon_interface::PokemonEngineInterface::update() {
  user_pokemon_ = engine_data_.GetHumanPlayer().GetCurrentlyInBattle();
  computer_pokemon_ = engine_data_.GetComputerPlayer().GetCurrentlyInBattle();
}

void pokemon_interface::PokemonEngineInterface::DrawPokemon(
    pokemon_species::Species creature, ci::Area area) {
  auto starting_image = ci::loadImage(ci::loadUrl(creature.front_sprite_));
  ci::gl::Texture2dRef starting_pokemon_image = ci::gl::Texture2d::create(starting_image);
  ci::gl::draw(starting_pokemon_image, area);
}

void pokemon_interface::PokemonEngineInterface::keyDown(ci::app::KeyEvent event) {

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