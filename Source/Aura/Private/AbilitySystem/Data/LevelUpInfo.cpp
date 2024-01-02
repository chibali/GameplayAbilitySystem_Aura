// Hey yo


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 CurrentXP) const
{
	int32 Level = 1;
	bool bSearching = true;
	while(bSearching)
	{
		// LevelUpInformation[1] = Level 1 Information
		// LevelUpInformation[2] = Level 2 Information

		if (LevelUpInformation.Num() - 1<= Level) return Level;
		
		if (CurrentXP >= LevelUpInformation[Level].LevelUpRequirement)
		{
			++Level;
		}
		else
		{
			bSearching = false;
		}
	}
	return Level;
}
