#include "irrlicht.h"
#include "CVideoMaster.h"

using namespace irr;
using namespace video;
using namespace core;
using namespace scene;
using namespace io;
using namespace gui;

IrrlichtDevice  *device;
IVideoDriver    *driver;
ISceneManager   *smgr;
IGUIEnvironment *guienv;
CVideoMaster    *vidmaster;

class CEvents : public irr::IEventReceiver
{
  bool OnEvent (const irr::SEvent &e)
  {
    switch (e.EventType)
    {
      case EET_KEY_INPUT_EVENT :
      {
        switch (e.KeyInput.Key)
        {
          case KEY_BACK :
          {
            // Be careful with the parameters,
            // removing a texture currently in use will cause a crash
            vidmaster->removeVideoClip("YUV", true, true);
          } break;

          case KEY_ESCAPE :
          {
            device->closeDevice();
          }
          default:
            break;
        }
      } break;

      case EET_MOUSE_INPUT_EVENT :
      {
        switch (e.MouseInput.Event)
        {
          case EMIE_LMOUSE_PRESSED_DOWN :
          {
            // Add a new video clip to be used as a 2DImage
            vidmaster->addVideoClip("../../intro/Splash..ogg", "YUV", dimension2du(256,256), true);
          } break;

          case EMIE_RMOUSE_PRESSED_DOWN :
          {
            // Pause/Resume playback of YUV Video
            // Lots of different features can be accessed via the TheoClip pointer
            TheoraVideoClip* temp = vidmaster->getTheoClipByName("YUV");

            if (temp)
            {
              if (temp->isPaused()) temp->play();
              else                  temp->pause();
            }
          }
          default:
            break;
        }
      }
      default:
        break;
    }

    return false;
  }
};

int main()
{
  SIrrlichtCreationParameters deviceParams;

  deviceParams.DriverType = EDT_OPENGL;
  //deviceParams.DriverType = EDT_DIRECT3D9;
  deviceParams.WindowSize = dimension2du(800, 600);
  deviceParams.Bits       = 32;
  deviceParams.Fullscreen = false;
  deviceParams.Vsync      = false;
  deviceParams.AntiAlias  = 16;

  device = createDeviceEx(deviceParams);
  driver = device->getVideoDriver();
  smgr   = device->getSceneManager();
  guienv = device->getGUIEnvironment();

  CEvents eve;
  device->setEventReceiver(&eve);

  ICameraSceneNode* cam = smgr->addCameraSceneNodeFPS();
  cam->setPosition(vector3df(0, 0, 200.0f));

  // Create the video master with audio playback enabled using 1 decoder thread
  vidmaster = new CVideoMaster(device, true, 1);

  // Add a new video clip,
  // the returned texture can be used for pretty much everything
  ITexture* cubeDiffuse = vidmaster->addVideoClip("../../intro/Splash.ogv", "TV", ESM_NONE, true);

  IMeshSceneNode *TV = smgr->addCubeSceneNode(50);
  TV->setScale(vector3df(1.0f, 1.0f, 0.001f));
  // Set video texture as diffuse
  TV->setMaterialTexture(0, cubeDiffuse);
  TV->setMaterialFlag(EMF_LIGHTING, false);

  s32 lastFPS = -1;
  while(device->run())
  {
    // make sure to update each frame
    vidmaster->update();

    driver->beginScene(true, true, SColor(0, 0, 0, 0));
      smgr->drawAll();

      // get a texture by name and draw it
      ITexture* temp = vidmaster->getTextureByName("YUV");
      if (temp)
      {
        driver->draw2DImage(temp, vector2di(0, 0));
      }

    driver->endScene();

// --------------------------------------------------

    s32 fps = driver->getFPS();
    if (lastFPS != fps)
    {
      stringw str  = L"VideoMaster Demo | ";
              str += driver->getName();
              str += L" | ";
              str += fps;
              str += L" FPS";
      device->setWindowCaption(str.c_str());
      lastFPS = fps;
    }
  }

  delete vidmaster;

  device->drop();

  return 0;
}
