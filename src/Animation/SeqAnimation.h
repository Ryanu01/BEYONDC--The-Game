#ifndef SEQANIMATION_H
#define SEQANIMATION_H

#include<map>
#include<string>
#include<vector>
#include<SDL2/SDL.h>
#include "Animation.h"


struct Sequence {
    int Speed;
    int FrameCount;
    int Width, Height;
    std::vector<std::string> TextureID;
};

class SeqAnimation : public Animation
{
private:
    Sequence m_CurrentSeq;
    std::string m_CurrentSeqID;
    std::map<std::string, Sequence> m_SeqMap;

public:
    SeqAnimation(bool repeat = true);
    std::string GetCurrentSeq() const;
    virtual void Update(float dt);
    void Parse(std::string source);
    void SetCurrentseq(std::string seqID);
    void SetRepeat(bool repeat){m_Repeat = repeat;}
    void DrawFrame(float x, float y, float xScale = 1, float yScale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);

    bool HasSequence(const std::string& id) {
    return m_SeqMap.find(id) != m_SeqMap.end();
}

};

#endif