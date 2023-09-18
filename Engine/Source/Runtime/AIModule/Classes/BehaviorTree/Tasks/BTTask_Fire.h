#pragma once

#include "CoreMinimal.h"
#include "BTTask_BlackboardBase.h"
#include "UObject/ObjectMacros.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Fire.generated.h"

UCLASS()
class AIMODULE_API UBTTask_Fire : public UBTTask_BlackboardBase
{
	GENERATED_UCLASS_BODY()

	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

#if WITH_EDITOR

#endif

};
