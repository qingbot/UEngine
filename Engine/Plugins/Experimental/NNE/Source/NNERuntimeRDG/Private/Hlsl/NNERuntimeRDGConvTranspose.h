// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "NNERuntimeRDG.h"
#include "NNERuntimeRDGHlslOp.h"

namespace UE::NNERuntimeRDG::Private::Hlsl
{
	bool RegisterConvTransposeOperator(FOperatorRegistryHlsl& Registry);
} // UE::NNERuntimeRDG::Private::Hlsl
