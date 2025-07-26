#include "TileLayer.h"
#include "Graphics\TextureManager.h"
#include <iostream>

TileLayer ::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets) : m_Tilesets(tilesets)
{
    m_RowCount = rowcount;
    m_ColCount = colcount;
    m_Tilemap = tilemap;
    

    if (m_Tilesets.empty())
    {
        std::cerr << "Error: No tilesets passed to TileLayer!" << std::endl;
        return;
    }

    for (unsigned int i = 0; i < m_Tilesets.size(); i++)
    {
        TextureManager::GetInstance()->LoadTexture(m_Tilesets[i].Name, "../assets/maps/" + m_Tilesets[i].Source);
    }
}

// void TileLayer::Render()
// {
//     for (unsigned int i = 0; i < m_RowCount; i++)
//     {
//         for (unsigned int j = 0; j < m_ColCount; j++)
//         {
//             int tileID = m_Tilemap[i][j];

//             if (tileID == 0)
//             {
//                 continue;
//             }
//             else
//             {
//                 int index = 0;
//                 if (m_Tilesets.size() > 1)
//                 {
//                     for (unsigned int k = 1; k < m_Tilesets.size(); k++)
//                     {
//                         if (tileID > m_Tilesets[k].FirstID && tileID < m_Tilesets[k].LastID)
//                         {
//                             tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].LastID;
//                             index = k;
//                             break;
//                         }
//                     }
//                 }

//                 Tileset ts = m_Tilesets[index];
//                 int tileRow = tileID / ts.ColCount;
//                 int tileCol = tileID - tileRow * ts.ColCount - 1;

//                 if (tileID % ts.ColCount == 0)
//                 {
//                     tileRow--;
//                     tileCol = ts.ColCount - 1;
//                 }
//                 TextureManager::GetInstance()->DrawTile(ts.Name, ts.Tilesize, j * ts.Tilesize, i * ts.Tilesize, tileRow, tileCol);
//             }
//         }
//     }
// }


// void TileLayer::Render()
// {
//     for (unsigned int i = 0; i < m_RowCount; i++)
//     {
//         for (unsigned int j = 0; j < m_ColCount; j++)
//         {
//             int tileID = m_Tilemap[i][j];

//             if (tileID == 0)
//                 continue;

//             int index = 0; // Default to first tileset

//             // Find correct tileset if there are multiple
//             for (unsigned int k = 0; k < m_Tilesets.size(); k++)
//             {
//                 if (tileID >= m_Tilesets[k].FirstID && tileID <= m_Tilesets[k].LastID)
//                 {
//                     index = k;
//                     break;
//                 }
//             }

//             // Safety check
//             if (index >= m_Tilesets.size())
//             {
//                 std::cerr << "Invalid tileset index for tileID " << tileID << std::endl;
//                 continue;
//             }

//             const Tileset& ts = m_Tilesets[index];

//             int localTileID = tileID - ts.FirstID;
//             int tileRow = localTileID / ts.ColCount;
//             int tileCol = localTileID % ts.ColCount;

//             TextureManager::GetInstance()->DrawTile(ts.Name, ts.Tilesize, j * ts.Tilesize, i * ts.Tilesize, tileRow, tileCol);
//         }
//     }
// }


void TileLayer::Render()
{
    for (unsigned int i = 0; i < m_RowCount; i++)
    {
        for (unsigned int j = 0; j < m_ColCount; j++)
        {
            int tileID = m_Tilemap[i][j];

            if (tileID == 0) continue;

            int index = 0;

            if (m_Tilesets.size() > 1)
            {
                for (unsigned int k = 1; k < m_Tilesets.size(); k++)
                {
                    if (tileID >= m_Tilesets[k].FirstID)
                    {
                        index = k;
                    }
                }
            }

            Tileset ts = m_Tilesets[index];
            tileID = tileID - ts.FirstID + 1;

            int tileRow = (tileID - 1) / ts.ColCount;
            int tileCol = (tileID - 1) % ts.ColCount;

            TextureManager::GetInstance()->DrawTile(ts.Name, ts.Tilesize, j * ts.Tilesize, i * ts.Tilesize, tileRow, tileCol);
        }
    }
}


void TileLayer::Update()
{
}