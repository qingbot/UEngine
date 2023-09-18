#include "BTTask_RotateToTarget.h"

#include "AIController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_RotateToTarget::UBTTask_RotateToTarget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "RotateToTarget";
	//bTickIntervals = true;
	INIT_TASK_NODE_NOTIFY_FLAGS();
}

EBTNodeResult::Type UBTTask_RotateToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	UObject* KeyValue = MyBlackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
	const AActor* TargetActor = Cast<AActor>(KeyValue);
	if(TargetActor)
	{
		const FVector Direction = TargetActor->GetActorLocation() - OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();
		
		OwnerComp.GetAIOwner()->GetPawn()->SetActorRotation( Direction.GetSafeNormal2D().Rotation());
	}
	return EBTNodeResult::Succeeded;
}

void UBTTask_RotateToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	
}

