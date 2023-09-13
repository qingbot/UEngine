#pragma once
#include "MeshPassProcessor.h"

class WaterBallPass : FMeshPassProcessor
{

	void AddMeshBatch(const FMeshBatch& MeshBatch, uint64 BatchElementMask,
		const FPrimitiveSceneProxy* PrimitiveSceneProxy, int32 StaticMeshId) override;
};
