/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_LAYERS_H
#define GAME_LAYERS_H

#include <engine/map.h>
#include <game/mapitems.h>

class CLayers
{
	int m_GroupsNum;
	int m_GroupsStart;
	int m_LayersNum;
	int m_LayersStart;
	CMapItemGroup *m_pGameGroup;
	CMapItemLayerTilemap *m_pGameLayer;
	class IMap *m_pMap;

	// MapGen: Direct layer access
	int m_GameGroupIndex;
	int m_GameLayerIndex;
	int m_BackgrounLayerIndex;
	int m_DoodadsLayerIndex;
	int m_ForegroundLayerIndex;
	int m_Base1LayerIndex;
	int m_Base2LayerIndex;
	CMapItemLayerTilemap *m_pBackgrounLayer;
	CMapItemLayerTilemap *m_pDoodadsLayer;
	CMapItemLayerTilemap *m_pForegroundLayer;
	CMapItemLayerTilemap *m_pBase1Layer;
	CMapItemLayerTilemap *m_pBase2Layer;

	// for generating layers
	class CTile *m_pTiles;

public:
	CLayers();
	void Init(class IKernel *pKernel);
	int NumGroups() const { return m_GroupsNum; };
	class IMap *Map() const { return m_pMap; };
	CMapItemGroup *GameGroup() const { return m_pGameGroup; };
	CMapItemLayerTilemap *GameLayer() const { return m_pGameLayer; };
	CMapItemGroup *GetGroup(int Index) const;
	CMapItemLayer *GetLayer(int Index) const;

	// MapGen: Direct layer access
	int GetGameGroupIndex() const { return m_GameGroupIndex; }
	int GetGameLayerIndex() const { return m_GameLayerIndex; }
	CMapItemLayerTilemap *BackgroundLayer() const { return m_pBackgrounLayer; };
	int GetBackgroundLayerIndex() const { return m_BackgrounLayerIndex; }
	CMapItemLayerTilemap *DoodadsLayer() const { return m_pDoodadsLayer; };
	int GetDoodadsLayerIndex() const { return m_DoodadsLayerIndex; }
	CMapItemLayerTilemap *ForegroundLayer() const { return m_pForegroundLayer; };
	int GetForegroundLayerIndex() const { return m_ForegroundLayerIndex; }
	int GetBase1LayerIndex() const { return m_Base1LayerIndex; }
	int GetBase2LayerIndex() const { return m_Base2LayerIndex; }
};

#endif
