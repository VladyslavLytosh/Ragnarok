﻿// Copyright by Suspended Team.

#include "Data/CharacterDeathData.h"

FDeathData UCharacterDeathData::GetDeathDataByDamageType(const TSubclassOf<UDamageType>& DamageType)
{
	if (Data.Contains(DamageType))
	{
		return Data[DamageType];
	}

	return FDeathData();
}
