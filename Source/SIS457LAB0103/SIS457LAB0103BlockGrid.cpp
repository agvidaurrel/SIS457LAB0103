// Copyright Epic Games, Inc. All Rights Reserved.

#include "SIS457LAB0103BlockGrid.h"
#include "SIS457LAB0103Block.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

ASIS457LAB0103BlockGrid::ASIS457LAB0103BlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(200.f,0.f,0.f));
	ScoreText->SetRelativeRotation(FRotator(90.f,0.f,0.f));
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(0)));
	ScoreText->SetupAttachment(DummyRoot);



	mibiografiaText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("mibiografiaText0"));
	mibiografiaText->SetRelativeLocation(FVector(200.f, 0.f, 0.f));
	mibiografiaText->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	mibiografiaText->SetText(FText::Format(LOCTEXT("mibiografiaFmt", "hola soy alvaro \ny soy de tupiza: {0}"), FText::AsNumber(0)));
	mibiografiaText->SetupAttachment(DummyRoot);
	// Set defaults
	Size = 3;
	BlockSpacing = 300.f;
}


void ASIS457LAB0103BlockGrid::BeginPlay()
{
	Super::BeginPlay();

	// Number of blocks
	const int32 NumBlocks = Size * Size;

	// Loop to spawn each block
	for(int32 BlockIndex=0; BlockIndex<NumBlocks; BlockIndex++)
	{
		const float XOffset = (BlockIndex/Size) * BlockSpacing; // Divide by dimension
		const float YOffset = (BlockIndex%Size) * BlockSpacing; // Modulo gives remainder

		// Make position vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

		// Spawn a block
		ASIS457LAB0103Block* NewBlock = GetWorld()->SpawnActor<ASIS457LAB0103Block>(BlockLocation, FRotator(0,0,0));

		// Tell the block about its owner
		if (NewBlock != nullptr)
		{
			NewBlock->OwningGrid = this;
		}
	}
}


void ASIS457LAB0103BlockGrid::AddScore()
{
	// Increment score
	Score++;

	// Update text
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(Score)));
}


void ASIS457LAB0103BlockGrid::Addmibiografia()
{
	// Increment score
	Score++;

	// Update text
	ScoreText->SetText(FText::Format(LOCTEXT("mibiografiaFmt", "mibiografia: {0}"), FText::AsNumber(Score)));
}

#undef LOCTEXT_NAMESPACE
