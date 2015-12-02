#include "audioSystem.h"
#include "global.h"
#include <cassert>

AudioSystem::AudioSystem():b_stop(true){
  loadResource();

  for(int i=0; i < MAX_SOUND_THREADS; i++ ){
    list_sound.push_back(new sf::Sound());
  }
}
AudioSystem::~AudioSystem(){
  for(int i= 0; i < list_soundbuffer.size(); i++){
    delete list_soundbuffer[i];
  }
  for(int i= 0; i < list_sound.size(); i++){
    delete list_sound[i];
  }
}

void AudioSystem::update() {
  if ( global()->gameEngine.gameState == constants::PLAYING ) {
    if (b_stop) {
      for (int i=0; i < list_sound.size(); i++) {
        if (list_sound[i]->getStatus() == sf::Sound::Paused) {
          list_sound[i]->play();
        }
      }
      if (music.getStatus() == sf::Music::Paused) {
        music.play();
      }
      else {
        playMusic(0, true);
      }
      b_stop = false;
    }
  }
  else {
    if(!b_stop) {
      for (int i=0; i < list_sound.size(); i++) {
        if (list_sound[i]->getStatus() == sf::Sound::Playing) {
          list_sound[i]->pause();
        }
      }
      if (music.getStatus() == sf::Music::Playing) {
        music.pause();
      }
      b_stop = true;
    }
  }
}

void AudioSystem::loadResource(){
  for(int i=0; i < SOUND_MAX; i++){
    list_soundbuffer.push_back(new sf::SoundBuffer());
  }
  list_soundbuffer[BULLET_SHOOTING_COMMON]->loadFromFile("resources/audio/sound/Gun_Shot-Marvin-1140816320.wav");
  list_soundbuffer[BULLET_SHOOTING_SMOKE]->loadFromFile("resources/audio/sound/grenadeSound.wav");
  list_soundbuffer[WEAPON_SWITCH]->loadFromFile("resources/audio/sound/weaponSwitch.wav");
  //other sounds ...
}

void AudioSystem::playSound(SoundName sound){
  if (sound >= 0 && sound < SOUND_MAX) {
    static int last_time_index = 0;
    for (int i=0; i < list_sound.size(); i++) {
      if (list_sound[i]->getStatus() == sf::Sound::Stopped) {
        list_sound[i]->setBuffer(*list_soundbuffer[sound]);
        list_sound[i]->play();
        last_time_index = i;
        return;
      }
    }
    last_time_index -= 1;
    if (last_time_index < 0)
      last_time_index = SOUND_MAX - 1;
    list_sound[last_time_index]->setBuffer(*list_soundbuffer[sound]);
    list_sound[last_time_index]->play();
  }
}
void AudioSystem::playMusic(std::string &music_file, bool repeat) {
  assert(music.openFromFile(music_file.c_str()));
  music.setLoop(repeat);
  music.play();
}
void AudioSystem::playMusic(int i, bool repeat) {
  if (i >=0 && i < list_music.size()) {
    playMusic(list_music[i], repeat);
  }
}
void AudioSystem::addMusicList(std::vector<std::string> &list){
  list_music.insert(list_music.end(), list.begin(), list.end());
}
void AudioSystem::clearMusicList(){
  list_music.clear();
  list_music.resize(0);
}
void AudioSystem::reset(){
  for (int i=0; i < list_sound.size(); i++) {
    list_sound[i]->stop();
  }
  music.stop();
}
