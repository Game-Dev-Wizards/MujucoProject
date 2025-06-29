// Fill out your copyright notice in the Description page of Project Settings.


#include "MujocoGIsubsystem.h"

#include "EngineUtils.h"

void UMujocoGIsubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UMujocoGIsubsystem::Deinitialize()
{
	Super::Deinitialize();
}

UMjScene* UMujocoGIsubsystem::GetCurrentMjScene() 
{
	if(MjSceneInstance)
	{
		return MjSceneInstance;
	}
	else
	{
		//spawn ac actor to hold UMJScene
		FVector SpawnLocation(0.f, 0.f, 300.f);
		FRotator SpawnRotation = FRotator::ZeroRotator;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* MyActor = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);

		// spawn actor component
		MjSceneInstance = NewObject<UMjScene>(MyActor);
		MjSceneInstance->RegisterComponent(); // Required!

		return MjSceneInstance;
	}
}

UMjGlobalSettings* UMujocoGIsubsystem::GetCurrentMjGlobalSettings()
{

	if(MjGlobalSettings)
	{
		return MjGlobalSettings;
	}
	else
	{
		UWorld* World = GEngine->GetWorldFromContextObjectChecked(this);

		TArray<UMjGlobalSettings*> AllUMjGlobalSettings;

		for (TActorIterator<AActor> It(World); It; ++It)
		{
			if (UMjGlobalSettings* Scene = It->FindComponentByClass<UMjGlobalSettings>())
			{
				AllUMjGlobalSettings.Add(Scene);
			}
		}

		if (AllUMjGlobalSettings.Num()>0)
		{
			if (AllUMjGlobalSettings.Num()>1)
			{
				UE_LOG(LogTemp, Log, TEXT("Only one MjGlobalSettings instance is allowed - please resolve manually inside editor by deleting extra UMjGlobalSettings"));

			}

			return AllUMjGlobalSettings[0];
		}






		
		//spawn ac actor to hold UMJScene
		FVector SpawnLocation(0.f, 0.f, 300.f);
		FRotator SpawnRotation = FRotator::ZeroRotator;

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* MyActor = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);

		// spawn actor component
		MjGlobalSettings = NewObject<UMjGlobalSettings>(MyActor);
		MjGlobalSettings->RegisterComponent(); // Required!

		return MjGlobalSettings;
	}
}
