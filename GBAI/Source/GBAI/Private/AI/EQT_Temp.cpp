//------------------------------------------------------------------------------------------------------------
#include "AI/EQT_Temp.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h" // Чтобы понимать, что мы тестируем Актора
#include "GameplayTagAssetInterface.h" // Стандартный интерфейс тегов
#include "GameFramework/Actor.h"
//------------------------------------------------------------------------------------------------------------




// UEQT_Temp
UEQT_Temp::UEQT_Temp()
{
	// Настройки по умолчанию
	Cost = EEnvTestCost::Low; // Тест дешевый, просто проверка
	ValidItemType = UEnvQueryItemType_Actor::StaticClass(); // Работаем только с Акторами
	SetWorkOnFloatValues(false); // Мы возвращаем Да/Нет (проходит/не проходит), а не число
}
//------------------------------------------------------------------------------------------------------------
void UEQT_Temp::RunTest(FEnvQueryInstance& QueryInstance) const
{
	// Проходимся по всем найденным объектам (нашим бургерам и яблокам)
	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		bool bHasTag = false;

		// 1. Получаем Актора из текущего элемента
		AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());

		if (ItemActor)
		{
			// 2. Проверяем, реализует ли Актор интерфейс тегов.
			// (Это работает и для C++, и для Blueprint, если там добавлен Interface)
			const IGameplayTagAssetInterface* TagInterface = Cast<IGameplayTagAssetInterface>(ItemActor);

			if (TagInterface)
			{
				// 3. Спрашиваем у интерфейса: "У тебя есть этот тег?"
				bHasTag = TagInterface->HasMatchingGameplayTag(TagToMatch);
			}
		}

		// 4. Записываем результат.
		// Если bHasTag == true, то Score будет 1.0 (прошел), иначе 0.0 (не прошел)
		It.SetScore(TestPurpose, FilterType, bHasTag, true);
	}
}
//------------------------------------------------------------------------------------------------------------
FText UEQT_Temp::GetDescriptionTitle() const
{
	return FText::FromString(TEXT("Has Gameplay Tag (C++)"));
}
//------------------------------------------------------------------------------------------------------------
FText UEQT_Temp::GetDescriptionDetails() const
{
	return FText::Format(FText::FromString(TEXT("{0}")), FText::FromName(TagToMatch.GetTagName()));
}
//------------------------------------------------------------------------------------------------------------
