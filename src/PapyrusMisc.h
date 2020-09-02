#pragma once

#include "main.h"


namespace PapyrusMisc
{
	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	inline std::map<const std::int32_t, const std::vector<std::int32_t>> FACTION_RACES_MAP = {
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

	auto SearchListForForms(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::BGSListForm* a_list, std::vector<RE::TESForm*> a_forms) -> std::vector<bool>;
	auto SearchListsForForm(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::BGSListForm* a_lists, RE::TESForm* a_form) -> std::vector<bool>;
	auto InRangeGameTime(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, float a_min, float a_max) -> bool;
	auto LookupRaceWeightIndex(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, std::int32_t a_factionIndex, RE::TESRace* a_playerRace, std::vector<RE::TESRace*> a_races) -> std::int32_t;

	auto RegisterFuncs(VM* a_vm) -> bool;
}
