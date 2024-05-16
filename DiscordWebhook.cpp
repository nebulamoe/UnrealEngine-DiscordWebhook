#include "DiscordWebhook.h"

void UDiscordWebhook::SendDiscordMessage(const FString& Webhook, const FString& Message)
{
    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
    Request->OnProcessRequestComplete().BindStatic(&UDiscordWebhook::OnResponseReceived); // Use BindStatic for static functions
    Request->SetURL(Webhook);
    Request->SetVerb("POST");
    Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
    Request->SetHeader("Content-Type", TEXT("application/json"));

    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    JsonObject->SetStringField(TEXT("content"), Message);

    FString JsonString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
    FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

    Request->SetContentAsString(JsonString);
    Request->ProcessRequest();
}

void UDiscordWebhook::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    if (!bWasSuccessful || !EHttpResponseCodes::IsOk(Response->GetResponseCode()))
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to send message to Discord"));
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("Successfully sent message to Discord"));
}