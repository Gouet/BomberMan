//
// Texture.cpp for TEXTURE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Tue May 10 14:22:36 2016 Victor Gouet
// Last update Sun Jun  5 17:31:33 2016 Victor Gouet
//

#include <iostream>
#include "Texture.hpp"

const std::string BomberManTexture::path = BINDIR"media/commons/";
const std::string BomberManTexture::smallMap = BINDIR"media/smallMap/";
const std::string BomberManTexture::mediumMap = BINDIR"media/mediumMap/";
const std::string BomberManTexture::largeMap = BINDIR"media/largeMap/";
const std::string BomberManTexture::bombs = BINDIR"media/bombs/";
const std::string BomberManTexture::bonus = BINDIR"media/bonus/";
const std::string BomberManTexture::characters = BINDIR"media/characters/";
const std::string BomberManTexture::gui = BINDIR"media/gui/";
const std::string BomberManTexture::font = BINDIR"media/font/";

const std::map<std::string, struct model>  BomberManTexture::_models = {

		// Map SMALL
		{"carpet", {BomberManTexture::smallMap + "meshes/carpet.md3", BomberManTexture::smallMap + "textures/Carpet01_D.png"}},
		{"carpet5", {BomberManTexture::smallMap + "meshes/carpet5.md3", BomberManTexture::smallMap + "textures/Carpet03_D.png"}},
		{"chest3", {BomberManTexture::smallMap + "meshes/chest3.md3", BomberManTexture::smallMap + "textures/Chest03_D.BMP"}},
		{"chest4", {BomberManTexture::smallMap + "meshes/chest4.md3", BomberManTexture::smallMap + "textures/Chest04_D.BMP"}},
		{"curtain", {BomberManTexture::smallMap + "meshes/curtain.md3", BomberManTexture::smallMap + "textures/curtain_d.png"}},
		{"goods", {BomberManTexture::smallMap + "meshes/goods.md3", BomberManTexture::smallMap + "textures/goods_d.png"}},
		{"ground", {BomberManTexture::smallMap + "meshes/ground.md3", BomberManTexture::smallMap + "textures/ground_d1.png"}},
		{"light", {BomberManTexture::smallMap + "meshes/light.md3", BomberManTexture::smallMap + "textures/Light01_D.png"}},
		{"pillar", {BomberManTexture::smallMap + "meshes/pillar.md3", BomberManTexture::smallMap + "textures/pillar_d.png"}},
		{"statue", {BomberManTexture::smallMap + "meshes/statue.md3", BomberManTexture::smallMap + "textures/statue_d.png"}},
		{"table", {BomberManTexture::smallMap + "meshes/table.md3", BomberManTexture::smallMap + "textures/table_d.png"}},
		{"wall_left", {BomberManTexture::smallMap + "meshes/wall_left.md3", BomberManTexture::smallMap + "textures/wall_left.png"}},
		{"wall_right", {BomberManTexture::smallMap + "meshes/wall_right.md3", BomberManTexture::smallMap + "textures/wall_right.png"}},
		{"weapon", {BomberManTexture::smallMap + "meshes/weapon.md3", BomberManTexture::smallMap + "textures/weapon_d.png"}},

		// Map MEDIUM
		{"floor", {BomberManTexture::mediumMap + "meshes/floor.md3", BomberManTexture::mediumMap + "textures/floor.BMP"}},
		{"pillar_map2", {BomberManTexture::mediumMap + "meshes/pillar.md3", BomberManTexture::mediumMap + "textures/pillar.TGA"}},
		{"pillar_map2_2", {BomberManTexture::mediumMap + "meshes/pillar2.md3", BomberManTexture::mediumMap + "textures/pillar2.TGA"}},
		{"pillar_map2_3", {BomberManTexture::mediumMap + "meshes/pillar3.md3", BomberManTexture::mediumMap + "textures/pillar3.TGA"}},
		{"rock", {BomberManTexture::mediumMap + "meshes/rock.md3", BomberManTexture::mediumMap + "textures/rock.TGA"}},
		{"wall", {BomberManTexture::mediumMap + "meshes/wall.md3", BomberManTexture::mediumMap + "textures/wall.TGA"}},
		{"floor_trim", {BomberManTexture::mediumMap + "meshes/floor_trim.md3", BomberManTexture::mediumMap + "textures/floor_trim.BMP"}},
		{"fern", {BomberManTexture::mediumMap + "meshes/fern.md3", BomberManTexture::mediumMap + "textures/fern.TGA"}},
		{"tree", {BomberManTexture::mediumMap + "meshes/tree.md3", BomberManTexture::mediumMap + "textures/tree.TGA"}},
		{"statue_map2", {BomberManTexture::mediumMap + "meshes/statue.md3", BomberManTexture::mediumMap + "textures/statue.TGA"}},
		{"statue1", {BomberManTexture::mediumMap + "meshes/statue1.md3", BomberManTexture::mediumMap + "textures/statue1.TGA"}},
		{"pine", {BomberManTexture::mediumMap + "meshes/pine.md3", BomberManTexture::mediumMap + "textures/pine.TGA"}},

		// Characters
		{"ziggs", {BomberManTexture::characters + "ziggs.md3", BomberManTexture::characters + "ziggs.png"}},
		{"ziggsPool", {BomberManTexture::characters + "ziggs_pool.md3", BomberManTexture::characters + "ziggs_pool.png"}},
		{"ziggsSnow", {BomberManTexture::characters + "ziggs_snow.md3", BomberManTexture::characters + "ziggs_snow.png"}},
		{"ziggsGeneral", {BomberManTexture::characters + "ziggs_general.md3", BomberManTexture::characters + "ziggs_general.png"}},
		{"ziggsMad", {BomberManTexture::characters + "ziggs_mad.md3", BomberManTexture::characters + "ziggs_mad.png"}},

		// Bombes
		{"fireBomb", {BomberManTexture::bombs + "classicBomb.md2", BomberManTexture::bombs + "classicBomb.png"}},
		{"fragBomb", {BomberManTexture::bombs + "classicBomb.md2", BomberManTexture::bombs + "atomicBomb.png"}},
		{"miniBomb", {BomberManTexture::bombs + "classicBomb.md2", BomberManTexture::bombs + "atomicBomb.png"}},
		{"atomicBomb", {BomberManTexture::bombs + "classicBomb.md2", BomberManTexture::bombs + "trackerBomb.png"}},
		{"trackerBomb", {BomberManTexture::bombs + "classicBomb.md2", BomberManTexture::bombs + "fragBomb.png"}},
		{"mineBomb", {BomberManTexture::bombs + "classicBomb.md2", BomberManTexture::bombs + "fireBomb.png"}},

		// Gui
		{"menuScene", {"", BomberManTexture::gui + "MenuScene.png"}},
		{"menuSceneStart", {"", BomberManTexture::gui + "MenuSceneStart.png"}},
		{"playerSelection", {"", BomberManTexture::gui + "PlayerSelection.png"}},
		{"playerButton", {"", BomberManTexture::gui + "PlayerButton.png"}},
		{"playerButtonIa", {"", BomberManTexture::gui + "PlayerButtonIaEasy.png"}},
		{"IAEasy", {"", BomberManTexture::gui + "PlayerButtonIaEasy.png"}},
		{"IAMedium", {"", BomberManTexture::gui + "PlayerButtonIaMedium.png"}},
		{"IAHard", {"", BomberManTexture::gui + "PlayerButtonIaHard.png"}},
		{"playerButtonSelected", {"", BomberManTexture::gui + "PlayerButtonSelected.png"}},
		{"victory", {"", BomberManTexture::gui + "victory.png"}},
		{"KeyBindBg", {"", BomberManTexture::gui + "KeyBindBg.png"}},

		// Font
		{"font", {"", BomberManTexture::font + "arcade_font.png"}},

		// Other
		{"fire", {"", BomberManTexture::path + "fire.jpg"}},

		{"fireAtomic", {"", BomberManTexture::path + "fireAtomic.jpg"}},
		{"fireTracker", {"", BomberManTexture::path + "fireTracker.jpg"}},
		{"fireExplosion", {BomberManTexture::path + "cube.md2", ""}},

		// Bonus
		{"bonusBombPass", {BomberManTexture::bonus + "meshes/pass.md3", BomberManTexture::bonus + "textures/pass_d.png"}},
		{"bonusFireBomb", {BomberManTexture::bonus + "meshes/fire.md3", BomberManTexture::bonus + "textures/fire_d.png"}},//
		{"bonusFragBomb", {BomberManTexture::bonus + "meshes/multibomb.md3", BomberManTexture::bonus + "textures/multibomb_d.png"}},//
		{"bonusAtomicBomb", {BomberManTexture::bonus + "meshes/atomic.md3", BomberManTexture::bonus + "textures/atomic_d.png"}},
		{"bonusTrackerBomb", {BomberManTexture::bonus + "meshes/tracking.md3", BomberManTexture::bonus + "textures/tracking_d.png"}},//

		{"bonusPower", {BomberManTexture::bonus + "meshes/bomb.md3", BomberManTexture::bonus + "textures/bomb_d.png"}},//
		{"bonusSpeed", {BomberManTexture::bonus + "meshes/speed.md3", BomberManTexture::bonus + "textures/speed_d.png"}},//
		{"bonusBiggestMan", {BomberManTexture::bonus + "meshes/giant.md3", BomberManTexture::bonus + "textures/giant_d.png"}},//
		{"bonusSmallestMan", {BomberManTexture::bonus + "meshes/small.md3", BomberManTexture::bonus + "textures/small_d.png"}},//
		{"bonusInvincible", {BomberManTexture::bonus + "meshes/invincible.md3", BomberManTexture::bonus + "textures/invincible_d.png"}},//

		// Items
		{"itemThrow", {BomberManTexture::bonus + "meshes/throw.md3", BomberManTexture::bonus + "textures/throw_d.png"}},
		{"itemMineBomb", {BomberManTexture::bonus + "meshes/mine.md3", BomberManTexture::bonus + "textures/mine_d.png"}},

		// BomberMap
		{"ground", {"", BomberManTexture::path + "grass.png"}},
		{"cubeDestructible", {BomberManTexture::path + "barrel.md2", BomberManTexture::path + "barrel.png"}},
		{"edge", {BomberManTexture::smallMap + "meshes/edge.md2", BomberManTexture::smallMap + "textures/pillar.png"}},

		{"fontTest", {"", BINDIR"media/font/arcade_font.png"}},
};

void BomberManTexture::loadTexture()
{
	for (std::map<std::string, struct model>::const_iterator it = _models.begin(); it != _models.end(); ++it) {
		if ((*it).second.mesh != "") {
		  if (IrrlichtController::getSceneManager()->getMesh((*it).second.mesh.c_str()) == NULL)
		    throw std::runtime_error("Failed to load Model : " + (*it).second.mesh);
		}
		if ((*it).second.texture != "") {
		  if (IrrlichtController::getDriver()->getTexture((*it).second.texture.c_str()) == NULL)
		    throw std::runtime_error("Failed to load Model : " + (*it).second.mesh);
		}
	}
}

const struct model &BomberManTexture::getModel(const std::string &model)
{
	const std::map<std::string, struct model>::const_iterator   it = _models.find(model);

	if (it == _models.end())
	  throw std::runtime_error("Failed to load Model : " + model);
	return (it->second);
}
