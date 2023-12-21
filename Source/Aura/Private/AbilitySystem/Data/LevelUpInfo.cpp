// Hey yo


#include "AbilitySystem/Data/LevelUpInfo.h"

FAuraLevelUpInfo ULevelUpInfo::FindLevelForXP(int32 CurrentXP, int32 CumulativeXP) const
{
	CumulativeXP += CurrentXP;
	int32 ClosestLevelUpRequirement;

	for (const FAuraLevelUpInfo& LevelInfo : LevelUpInformation)
	{
		int32 LevelUpRequirementToValue = LevelInfo.LevelUpRequirement;

		if (LevelUpRequirementToValue <= CumulativeXP)
		{
			ClosestLevelUpRequirement = LevelUpRequirementToValue;
		}
		if (LevelUpRequirementToValue > CumulativeXP)
		{
			return LevelInfo;
		}
	}
	return FAuraLevelUpInfo();
}
