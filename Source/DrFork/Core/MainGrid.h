#pragma once
#include "GameBlock.h"
#include "LogicGrid.h"
#include "Settings.h"
#include "GameFramework/Actor.h"
#include "Engine/DestructibleMesh.h"
#include "MainGrid.generated.h"

class AMainGrid;
static AMainGrid* AMainGridReference = nullptr;
const static int BlockSize = 200;
const static int MaxRubbishSize = 32;

UCLASS()
class DRFORK_API AMainGrid : public AActor
{
	GENERATED_BODY()

	AGameBlock* CreateBlock(Point pos, FRotator rot);
	
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	//UStaticMesh* Tablet;
	//UStaticMesh* Virus;
	UMaterialInstance* RedMat;
	UMaterialInstance* BlueMat;
	UMaterialInstance* YeullouMat;
	UDestructibleMesh* VirusDM;
	UDestructibleMesh* TabletDM;

	TArray<AGameBlock*> SceneRubbish;
	int RubbishIndex;

	GameState GameState;
	GameRoundState GameRoundState;

	LogicGrid LogicGrid;

	float CollectedTime;

	int LevelCompleted;

	Settings settings;
public:	
	AGameBlock* ControlledTablet;

	AMainGrid(const FObjectInitializer& ObjectInitializer);

	static AMainGrid* Get(){ return AMainGridReference; };

	void NewLevel();
	void CreateNewTablet();
	
	void MoveControlledTablet();
	void MoveUncontrolledTablet();
	bool CheckMoveBlock(AGameBlock* block, int diffX, int diffY);
	bool CeckMoveBlockChield(AGameBlock* block, int diffX, int diffY);
	bool CheckIndexes(AGameBlock* block, int diffX, int diffY);
	void SetBlockActorPosition(AGameBlock* block, int diffX, int diffY);
	void SetTabletActorPosition(AGameBlock* block, int diffX, int diffY);
	void RotateTabletActor(AGameBlock* block);
	

	void GameCycle(float DeltaTime);
	bool DestroyRound();
	bool CheckMoveRound();
	bool CheckFinishGame();

	void LevelComplete();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void StartGame(int SpeedMultyply, int VirusMultyply);

	UFUNCTION(BlueprintCallable, Category = "Game")
	void ResumeGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void PauseGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void GameOver();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void RotateTablet();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void MoveTablet(int32 diffX, int32 diffY);

	UFUNCTION(BlueprintCallable, Category = "Game")
	void MultiplyMoveTablet(int32 count);

	UFUNCTION(BlueprintCallable, Category = "Game")
	void ContinueGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void NewGame();


	UFUNCTION(BlueprintNativeEvent, Category = "GameSound")
		void OnRotate();
	virtual void OnRotate_Implementation(){};

	UFUNCTION(BlueprintNativeEvent, Category = "GameSound")
		void OnMove();
	virtual void OnMove_Implementation(){};

	UFUNCTION(BlueprintNativeEvent, Category = "GameSound")
		void OnDrop();
	virtual void OnDrop_Implementation(){};

	UFUNCTION(BlueprintNativeEvent, Category = "GameSound")
		void OnKill();
	virtual void OnKill_Implementation(){};

	UFUNCTION(BlueprintNativeEvent, Category = "GameSound")
		void OnKillTablet();
	virtual void OnKillTablet_Implementation(){};

	UFUNCTION(BlueprintNativeEvent, Category = "GameSound")
		void OnGameOver();
	virtual void OnGameOver_Implementation() {};

	UFUNCTION(BlueprintNativeEvent, Category = "GameSound")
		void OnLevelComplete();
	virtual void OnLevelComplete_Implementation() {};

	UFUNCTION(BlueprintNativeEvent, Category = "GameSound")
		void OnWinGame();
	virtual void OnWinGame_Implementation() {};

	UFUNCTION(BlueprintNativeEvent, Category = "GameSound")
		void StopMusic();
	virtual void StopMusic_Implementation() {};

	UFUNCTION(BlueprintNativeEvent, Category = "GameSound")
		void ReturnMusic();
	virtual void ReturnMusic_Implementation() {};

	UFUNCTION(BlueprintNativeEvent, Category = "GameSound")
		void MainMenuMusic();
	virtual void MainMenuMusic_Implementation() {};

	UFUNCTION(BlueprintNativeEvent, Category = "GameSound")
		void GameMusic();
	virtual void GameMusic_Implementation() {};

	UFUNCTION(BlueprintNativeEvent, Category = "UI")
		void PauseUI();
	virtual void PauseUI_Implementation() {};

	UFUNCTION(BlueprintNativeEvent, Category = "UI")
		void GameUI();
	virtual void GameUI_Implementation() {};

	UFUNCTION(BlueprintNativeEvent, Category = "UI")
		void GameOverUI();
	virtual void GameOverUI_Implementation() {};

	UFUNCTION(BlueprintNativeEvent, Category = "UI")
		void MainMenuUI();
	virtual void MainMenuUI_Implementation() {};

	UFUNCTION(BlueprintNativeEvent, Category = "UI")
		void LevelCompleteUI();
	virtual void LevelCompleteUI_Implementation() {};

	UFUNCTION(BlueprintNativeEvent, Category = "UI")
		void WinUI();
	virtual void WinUI_Implementation() {};

	virtual void BeginPlay() override;

	virtual void Tick( float DeltaSeconds ) override;
};
