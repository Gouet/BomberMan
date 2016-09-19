//
// Video.cpp for indie studio in /home/tavern_d/rendu/semestre4/cpp_indie_studio/src
//
// Made by Matthieu Tavernier
// Login   <tavern_d@epitech.net>
//
// Started on  Thu Apr 28 11:55:48 2016 Matthieu Tavernier
// Last update Sun May 22 22:28:38 2016 Victor Gouet
//

#include "Video.hpp"
#include "../include/IrrlichtController.hpp"
#include "../include/EventGame.hpp"

const std::string     Video::default_path_video = "./intro/video/";
const std::string     Video::default_path_sound = "./intro/sound/";

Video::Video(const std::string path)
{
    DIR	*rep;

    rep = opendir(path.data());
    if (rep != NULL)
    {
        struct dirent	*ent;

        while ((ent = readdir(rep)) != NULL)
        {
            if (std::string(ent->d_name) != "." && std::string(ent->d_name) != "..")
                this->files.push_back(default_path_video + std::string(ent->d_name));
        }
        closedir(rep);
        std::sort(this->files.begin(), this->files.end());
    }
}

Video::~Video()
{
}

void	Video::Run()
{
    irr::IrrlichtDevice* device = IrrlichtController::getDevice();
    irrklang::ISoundEngine *engine = irrklang::createIrrKlangDevice();
    if (!engine)
    {
        return;
    }
    irr::video::IVideoDriver* driver = device->getVideoDriver();
    size_t  i = 0;
    clock_t	timerFrame;
    irr::gui::IGUIEnvironment *guiEnv;
    guiEnv = IrrlichtController::getGUIEnvironment();
    irr::gui::IGUIImage *img;
    img = guiEnv->addImage(irr::core::rect<irr::s32>(0,0, IrrlichtController::width, IrrlichtController::height));

    EventGame *eventGame = new EventGame();
    IrrlichtController::getDevice()->setEventReceiver(eventGame);

    while (device->run() && i < this->files.size())
    {
        if (eventGame->IsKeyDownOneTime(irr::KEY_RETURN))
            break;

        if (i == 24)
            engine->play2D((default_path_sound + "intro.wav");;
        timerFrame = clock();
        irr::video::ITexture *tex = driver->getTexture((this->files[i]).c_str());
        img->setImage(tex);
        img->setScaleImage(true);
        driver->beginScene(true, true, irr::video::SColor(0,0,0,0));
        IrrlichtController::getGUIEnvironment()->drawAll();
        driver->endScene();
        driver->removeTexture(tex);
        timerFrame = clock() - timerFrame;
        if (static_cast<float>(timerFrame) / CLOCKS_PER_SEC < 1.0 / 23.975)
            usleep(1000000.0 / 23.975 - static_cast<float>(timerFrame) / CLOCKS_PER_SEC * 1000000.0);
        ++i;
    }
    engine->stopAllSounds();
}
