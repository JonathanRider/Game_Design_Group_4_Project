#ifndef _AUDIO_SYSTEM_H_
#define _AUDIO_SYSTEM_H_

#include <SFML/Audio.hpp>
#include <vector>
#include <string>

#define MAX_SOUND_THREADS 5

class AudioSystem {
public:
  AudioSystem();
  ~AudioSystem();

  void loadResource();
  enum SoundName { BULLET_SHOOTING, SOUND_MAX};

  void update();

  void playSound(SoundName sound);

  void addMusicList(std::vector<std::string> &list);

  void reset(); //clean all the sound and music tracks
  void clearMusicList();
  void playMusic(std::string &music_file, bool repeat = true);
  void playMusic(int i, bool repeat = true);


private:
  std::vector<sf::SoundBuffer *> list_soundbuffer;
  std::vector<sf::Sound *> list_sound;
  std::vector<std::string> list_music;
  sf::Music music;
  bool b_stop;


};


#endif
