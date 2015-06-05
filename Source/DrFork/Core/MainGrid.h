#pragma once
#include "GameBlock.h"
#include "GameFramework/Actor.h"
#include "MainGrid.generated.h"

class AMainGrid;
static AMainGrid* AMainGridReference = nullptr;
const static int BlockSize = 200;

UCLASS()
class DRFORK_API AMainGrid : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	UStaticMesh* Tablet;
	UStaticMesh* Virus;
	UMaterialInstance* RedMat;
	UMaterialInstance* BlueMat;
	UMaterialInstance* YeullouMat;

public:	
	AGameBlock* ControlledBlock;

	AMainGrid(const FObjectInitializer& ObjectInitializer);

	static AMainGrid* Get(){ return AMainGridReference; };
	void StartGame();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
};
