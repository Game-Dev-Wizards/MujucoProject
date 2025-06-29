// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MjComponent.h"

#include "MujocoGIsubsystem.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UMjComponent::UMjComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

FString UMjComponent::GetMujocoName() const
{
	return MujocoName;
}

int UMjComponent::GetMujocoID() const
{
	return  MujocoID;
}

mjtObj* UMjComponent::GetObjectType() const
{
	return ObjectType;
}

bool _sceneExcludesMe = false;

// Called when the game starts
void UMjComponent::BeginPlay()
{
	Super::BeginPlay();
	
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UMujocoGIsubsystem* refSubSystem = GameInstance->GetSubsystem<UMujocoGIsubsystem>();
	if (refSubSystem->GetCurrentMjScene() == nullptr) {
		
		UE_LOG(LogTemp, Error, TEXT("MuJoCo Scene not found"));

	}
	if (refSubSystem->GetCurrentMjScene()->Model != nullptr) {
		_sceneExcludesMe = true;
	}

	// ...
	
}


// Called every frame
void UMjComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

