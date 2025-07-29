#include "SeqAnimation.h"
#include "Vendor/tinyxml2.h"
#include<iostream>
#include "Camera/Camera.h"
#include "Graphics/TextureManager.h"

SeqAnimation :: SeqAnimation(bool repeat):Animation(repeat){}

void SeqAnimation::DrawFrame(float x, float y, float xScale, float yScale, SDL_RendererFlip flip)
{
    int frameX = m_CurrentFrame * m_CurrentSeq.Width;

    SDL_Rect srcRect = {
        frameX,                    // x: shift horizontally based on current frame
        0,                         // y: assuming 1 row
        m_CurrentSeq.Width,
        m_CurrentSeq.Height
    };

    Vector2D cam = Camera::GetInstance()->GetPosition();

    SDL_Rect destRect = {
        static_cast<int>(x - cam.X),
        static_cast<int>(y - cam.Y),
        static_cast<int>(m_CurrentSeq.Width * xScale),
        static_cast<int>(m_CurrentSeq.Height * yScale)
    };

    SDL_Texture* tex = TextureManager::GetInstance()->GetTexture(m_CurrentSeq.TextureID[0]);
    if (!tex) {
        std::cout << "Texture is null! ID: " << m_CurrentSeq.TextureID[0] << std::endl;
        return;
    }
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), tex, &srcRect, &destRect, 0, nullptr, flip);
}



void SeqAnimation::Update(float dt)
{
    if(m_Repeat || !m_IsEnded){
        m_IsEnded = false;
        m_CurrentFrame = (SDL_GetTicks()/m_CurrentSeq.Speed) % m_CurrentSeq.FrameCount;
    }

    if(!m_Repeat && m_CurrentFrame == (m_CurrentSeq.FrameCount-1))
    {
        m_IsEnded = true;
        m_CurrentFrame = (m_CurrentSeq.FrameCount-1);
    }
}   


void SeqAnimation::SetCurrentseq(std::string seqID)
{
    if(m_SeqMap.count(seqID) > 0)
    {
        m_CurrentSeq = m_SeqMap[seqID];
    }
    else
    {
        std::cout<< "The given Sequence Animation is not matching: " << seqID <<std::endl;
    }
}

void SeqAnimation::Parse(std::string source)
{
    tinyxml2::XMLDocument xml;
    xml.LoadFile(source.c_str());
    if(xml.Error())
    {
        std::cout<< "Failed to laod animation file: "<< source <<std::endl;
    }

    tinyxml2::XMLElement* root = xml.RootElement();
    for(tinyxml2::XMLElement* e = root->FirstChildElement(); e != nullptr; e=e->NextSiblingElement())
    {
        if(e->Value() == std::string("sequence"))
        {
            Sequence seq;
            std::string seqID = e->Attribute("id");
            e->QueryIntAttribute("speed", &seq.Speed);
            e->QueryIntAttribute("width", &seq.Width);
            e->QueryIntAttribute("height", &seq.Height);
            e->QueryIntAttribute("frameCount", &seq.FrameCount);
            for(tinyxml2::XMLElement* frame=e->FirstChildElement(); frame != nullptr; frame = frame->NextSiblingElement())
            {
                seq.TextureID.push_back(frame->Attribute("textureID"));
            }
            m_SeqMap[seqID] = seq;
        }
    }    
}