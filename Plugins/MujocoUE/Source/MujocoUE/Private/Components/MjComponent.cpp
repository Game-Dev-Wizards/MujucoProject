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

void UMjComponent::OnSyncState(mjData* data)
{
}

bool _sceneExcludesMe = false;

// Called when the game starts
void UMjComponent::BeginPlay()
{
	Super::BeginPlay();

	OnEnable();
	/*UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UMujocoGIsubsystem* refSubSystem = GameInstance->GetSubsystem<UMujocoGIsubsystem>();
	if (refSubSystem->GetCurrentMjScene() == nullptr) {
		
		UE_LOG(LogTemp, Error, TEXT("MuJoCo Scene not found"));

	}
	if (refSubSystem->GetCurrentMjScene()->Model != nullptr) {
		_sceneExcludesMe = true;
	}*/

	// ...
	
}


void UMjComponent::OnEnable()
{
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UMujocoGIsubsystem* refSubSystem = GameInstance->GetSubsystem<UMujocoGIsubsystem>();
	
	if (refSubSystem->GetCurrentMjScene() == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("MuJoCo Scene not found"));

	}
	if (refSubSystem->GetCurrentMjScene()->Model != nullptr) {
		_sceneExcludesMe = true;
	}
}

void UMjComponent::Update()
{
	if (_sceneExcludesMe) {
		UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		UMujocoGIsubsystem* refSubSystem = GameInstance->GetSubsystem<UMujocoGIsubsystem>();
	
		refSubSystem->GetCurrentMjScene()->SceneRecreationAtLateUpdateRequested = true;
		_sceneExcludesMe = false;
	}
}

// Called every frame
void UMjComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMjComponent::BindToRuntime(mjModel* model, mjData* data)
{
}

tinyxml2::XMLElement* UMjComponent::GenerateMjcf(FString name, tinyxml2::XMLDocument* doc)
{
	MujocoName = name;

	tinyxml2::XMLElement* mjcf = OnGenerateMjcf(doc);
	if (!IsSuppressNameAttribute()) {
		mjcf->SetAttribute("name", TCHAR_TO_UTF8(*name));
	}

	return mjcf;
}

void UMjComponent::OnApplicationQuit()
{
	_exiting = true;
}

void UMjComponent::OnDisable()
{
	UGameInstance* GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UMujocoGIsubsystem* refSubSystem = GameInstance->GetSubsystem<UMujocoGIsubsystem>();
	if (!_exiting && refSubSystem->GetCurrentMjScene()) {
		refSubSystem->GetCurrentMjScene()->SceneRecreationAtLateUpdateRequested = true;
	}
}

void UMjComponent::ParseMjcf(tinyxml2::XMLElement* mjcf)
{
}

tinyxml2::XMLElement* UMjComponent::OnGenerateMjcf(tinyxml2::XMLDocument* doc)
{
	return nullptr;
}

void UMjComponent::OnBindToRuntime(mjModel* model, mjData* data)
{
}

