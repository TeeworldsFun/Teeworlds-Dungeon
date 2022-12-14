/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include "layers.h"

#include <game/gamecore.h> // MapGen

CLayers::CLayers()
{
	m_GroupsNum = 0;
	m_GroupsStart = 0;
	m_LayersNum = 0;
	m_LayersStart = 0;
	m_pGameGroup = 0;
	m_pGameLayer = 0;
	m_pMap = 0;
}

void CLayers::Init(class IKernel *pKernel)
{
	m_pMap = pKernel->RequestInterface<IMap>();
	m_pMap->GetType(MAPITEMTYPE_GROUP, &m_GroupsStart, &m_GroupsNum);
	m_pMap->GetType(MAPITEMTYPE_LAYER, &m_LayersStart, &m_LayersNum);

	for(int g = 0; g < NumGroups(); g++)
	{
		CMapItemGroup *pGroup = GetGroup(g);
		for(int l = 0; l < pGroup->m_NumLayers; l++)
		{
			CMapItemLayer *pLayer = GetLayer(pGroup->m_StartLayer+l);

			if(pLayer->m_Type == LAYERTYPE_TILES)
			{
				CMapItemLayerTilemap *pTilemap = reinterpret_cast<CMapItemLayerTilemap *>(pLayer);

				// MapGen: Layers access info (Doesn't need group info because is supposed are in Game Layer Group)
				char layerName[64]={0};
				IntsToStr(pTilemap->m_aName, sizeof(pTilemap->m_aName)/sizeof(int), layerName);
				if (!m_pBackgrounLayer && str_comp_nocase(layerName, "background") == 0)
				{
					m_pBackgrounLayer = pTilemap;
					m_BackgrounLayerIndex = l;
				}
				else if (!m_pDoodadsLayer && str_comp_nocase(layerName, "doodads") == 0)
				{
					m_pDoodadsLayer = pTilemap;
					m_DoodadsLayerIndex = l;
				}
				else if (!m_pBase1Layer && str_comp_nocase(layerName, "base1") == 0)
				{
					m_pBase1Layer = pTilemap;
					m_Base1LayerIndex = l;
				}
				else if (!m_pBase2Layer && str_comp_nocase(layerName, "base2") == 0)
				{
					m_pBase2Layer = pTilemap;
					m_Base2LayerIndex = l;
					break; // Finish here... in not generated maps increase the CPU usage :/
				}
				else if (!m_pForegroundLayer && str_comp_nocase(layerName, "foreground") == 0)
				{
					m_pForegroundLayer = pTilemap;
					m_ForegroundLayerIndex = l;
				}

				if(pTilemap->m_Flags&TILESLAYERFLAG_GAME)
				{
					m_pGameLayer = pTilemap;
					m_pGameGroup = pGroup;

					// make sure the game group has standard settings
					m_pGameGroup->m_OffsetX = 0;
					m_pGameGroup->m_OffsetY = 0;
					m_pGameGroup->m_ParallaxX = 100;
					m_pGameGroup->m_ParallaxY = 100;

					if(m_pGameGroup->m_Version >= 2)
					{
						m_pGameGroup->m_UseClipping = 0;
						m_pGameGroup->m_ClipX = 0;
						m_pGameGroup->m_ClipY = 0;
						m_pGameGroup->m_ClipW = 0;
						m_pGameGroup->m_ClipH = 0;
					}

					// MapGen: Game layer access info
					m_GameGroupIndex = g;
					m_GameLayerIndex = l;
				}
			}
		}
	}
}

CMapItemGroup *CLayers::GetGroup(int Index) const
{
	return static_cast<CMapItemGroup *>(m_pMap->GetItem(m_GroupsStart+Index, 0, 0));
}

CMapItemLayer *CLayers::GetLayer(int Index) const
{
	return static_cast<CMapItemLayer *>(m_pMap->GetItem(m_LayersStart+Index, 0, 0));
}
