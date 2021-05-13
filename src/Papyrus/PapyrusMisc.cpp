#pragma once

#pragma warning(disable : 4100)

#include "PapyrusMisc.h"


namespace PapyrusMisc
{
	auto LookupRaceWeightIndex(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const std::int32_t a_factionIndex, RE::TESRace* a_playerRace, std::vector<RE::TESRace*> a_races) -> std::int32_t
	{
		if (a_factionIndex == -1) {
			a_vm->TraceStack("aiFactionIndex cannot be negative", a_stackID, Severity::kWarning);
			return -1;
		}

		if (!a_playerRace) {
			a_vm->TraceStack("akPlayerRace cannot be None", a_stackID, Severity::kWarning);
			return -1;
		}

		if (a_races.empty()) {
			a_vm->TraceStack("akRaces cannot be None", a_stackID, Severity::kWarning);
			return -1;
		}

		if (FACTION_RACES_MAP.count(a_factionIndex) == 0) {
			return -1;
		}

		auto raceIndices = FACTION_RACES_MAP[a_factionIndex];

		for (auto raceIndex : raceIndices) {
			auto* race = a_races[static_cast<std::uint32_t>(raceIndex)];
			if (race && a_playerRace == race)
				return raceIndex;
		}

		return -1;
	}


	auto RegisterFuncs(VM* a_vm) -> bool
	{
		if (!a_vm) {
			logger::info("PapyrusMisc - cannot get VMState");
			return false;
		}

		a_vm->RegisterFunction("LookupRaceWeightIndex", PROJECT_NAME, LookupRaceWeightIndex);

		return true;
	}
}