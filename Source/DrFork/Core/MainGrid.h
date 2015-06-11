#pragma once
#include "GameBlock.h"
#include "LogicGrid.h"
#include "GameFramework/Actor.h"
#include "MainGrid.generated.h"

class AMainGrid;
static AMainGrid* AMainGridReference = nullptr;
const static int BlockSize = 200;

UCLASS()
class DRFORK_API AMainGrid : public AActor
{
	GENERATED_BODY()

	AGameBlock* CreateBlock(Point pos, FRotator rot);
	
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	UStaticMesh* Tablet;
	UStaticMesh* Virus;
	UMaterialInstance* RedMat;
	UMaterialInstance* BlueMat;
	UMaterialInstance* YeullouMat;

	GameState GameState;
	LogicGrid LogicGrid;

	float CollectedTime;
public:	
	AGameBlock* ControlledTablet;

	AMainGrid(const FObjectInitializer& ObjectInitializer);

	static AMainGrid* Get(){ return AMainGridReference; };

	void NewLevel();
	void CreateNewTablet();
	void DropTablet(float DeltaTime);
	bool CheckMoveBlock(AGameBlock* block, int diffX, int diffY);
	bool CeckMoveBlockChield(AGameBlock* block, int diffX, int diffY);
	bool CheckIndexes(AGameBlock* block, int diffX, int diffY);
	void SetBlockActorPosition(AGameBlock* block, int diffX, int diffY);
	void SetTabletActorPosition(AGameBlock* block, int diffX, int diffY);
	void RotateTabletActor(AGameBlock* block);

	UFUNCTION(BlueprintCallable, Category = "Game")
	void StartGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void PauseGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void RotateTablet();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void MoveTablet(int32 diffX, int32 diffY);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
};
