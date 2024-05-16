#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Http.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "DiscordWebhook.generated.h"

UCLASS()
class UDiscordWebhook : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Discord")
    static void SendDiscordMessage(const FString& Webhook, const FString& Message);

private:
    static void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};