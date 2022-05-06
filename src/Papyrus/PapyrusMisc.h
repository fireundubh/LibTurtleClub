#pragma once

namespace PapyrusMisc
{
	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	inline std::map<const std::int32_t, const std::vector<std::int32_t>> FACTION_RACES_MAP = { // NOLINT(cert-err58-cpp)
		{ /* Faction */ 0, { /* Races */ 8 } },
		{ 1, { 4, 12 } },
		{ 2, { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 } },
		{ 3, { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 } },
		{ 4, { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18 } },
		{ 5, { 8, 14 } },
		{ 6, { 4 } },
		{ 7, { 8, 14 } },
		{ 8, { 12, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 } },
		{ 9, { 6, 8, 12 } },
		{ 10, { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18 } },

		{ 11, { 0, 10 } },
		{ 12, { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 } },
		{ 13, { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 } },
		{ 14, { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 } },
		{ 15, { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 } },
		{ 16, { 12 } },

		{ 18, { 12 } },
		{ 19, { 12 } },
		{ 20, { 2, 12 } },

		{ 21, { 12 } },
		{ 22, { 4 } },
		{ 23, { 12 } },
		{ 24, { 8, 12, 14 } },
		{ 25, { 12 } },
		{ 26, { 6, 12 } },
		{ 27, { 12 } },
		{ 28, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 } },
		{ 29, { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18 } },
		{ 30, { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18 } },
	};

	inline std::vector<std::int32_t> VIGIL_OF_STENDARR_EXCLUSIONS = {
		1, 13, 14, 15, 16, 17, 28
	};

	inline std::vector<std::int32_t> WINDHELM_GUARD_EXCLUSIONS = {
		4, 18, 19, 20, 21, 22, 23, 24, 25, 27, 30
	};

	inline std::map<const std::int32_t, const std::vector<std::int32_t>> MUTUALLY_EXCLUSIVE_DISGUISES = {
		{ 1, { 12 } },
		{ 4, { 26 } },
		{ 8, { 16, 17, 30 } },
		{ 12, VIGIL_OF_STENDARR_EXCLUSIONS },
		{ 13, { 12 } },
		{ 14, { 12 } },
		{ 15, { 12 } },
		{ 16, { 12 } },
		{ 17, { 12 } },
		{ 18, { 26 } },
		{ 19, { 26 } },
		{ 20, { 26 } },
		{ 21, { 26 } },
		{ 22, { 26 } },
		{ 23, { 26 } },
		{ 24, { 26 } },
		{ 25, { 26 } },
		{ 26, WINDHELM_GUARD_EXCLUSIONS },
		{ 27, { 26 } },
		{ 28, { 12 } },
		{ 30, { 8, 26 } }
	};

	auto CanDisguiseActivate(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, std::int32_t a_factionIndex, std::vector<bool> a_factionStates) -> bool;

	auto LookupRaceWeightIndex(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, std::int32_t a_factionIndex, RE::TESRace* a_playerRace, std::vector<RE::TESRace*> a_races) -> std::int32_t;

	auto RegisterFuncs(VM* a_vm) -> bool;
}
