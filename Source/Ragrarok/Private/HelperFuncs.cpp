// Copyright by Suspended Team.


#include "HelperFuncs.h"

UObject* UHelperFuncs::GetDefaultObject(TSubclassOf<UObject> ObjectClass)
{
	return ObjectClass.GetDefaultObject();
}
