#include "BTTask_Fire.h"

#include "AIController.h"


UBTTask_Fire::UBTTask_Fire(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Fire";
	//bTickIntervals = true;
	INIT_TASK_NODE_NOTIFY_FLAGS();
}

EBTNodeResult::Type UBTTask_Fire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIController* Controller = OwnerComp.GetAIOwner();
	if(Controller)
	{
		Controller->Fire();
	}
	return EBTNodeResult::Succeeded;
}
