#include "SeqAnimation.h"
#include "Vendor/tinyxml2.h"
#include<iostream>
#include "Graphics/TextureManager.h"

SeqAnimation :: SeqAnimation(bool repeat):Animation(repeat){}

void SeqAnimation::DrawFrame(float x, float y, float xScale, float yScale, SDL_RendererFlip flip)
{
    TextureManager::GetInstance()->Draw(m_CurrentSeq.TextureID[m_CurrentFrame], x, y, m_CurrentSeq.Width, m_CurrentSeq.Height, xScale, yScale, flip);
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