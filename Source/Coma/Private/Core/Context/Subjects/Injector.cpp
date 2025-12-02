// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Context/Subjects/Injector.h"

#include "Components/ActorComponent.h"
#include "Core/Context/Context.h"
#include "Core/Context/Subjects/Reflector.h"
#include "Core/Utils/ComaStatics.h"
#include "Core/Types/Metadata.h"

void UInjector::Inject(const TArray<UActorComponent*>& Components) const {
    Context->GetReflector()->InjectInstances(Components);
}
