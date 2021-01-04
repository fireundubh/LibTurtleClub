#pragma once

#include "PapyrusMisc.h"

auto PapyrusMisc::SearchListForForms(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::BGSListForm* a_list, std::vector<RE::TESForm*> a_forms) -> std::vector<bool> // NOLINT(performance-unnecessary-value-param)
{
	std::vector<bool> vec;

	if (a_list->forms.empty()) {
		a_vm->TraceStack("akFormList cannot be empty", a_stackID, Severity::kWarning);
		return vec;
	}

	if (a_forms.empty()) {
		a_vm->TraceStack("argForms cannot be None", a_stackID, Severity::kWarning);
		return vec;
	}

	for (auto* form : a_forms) {
		vec.push_back(form != nullptr && a_list->HasForm(form));
	}

	return vec;
}


auto PapyrusMisc::SearchListsForForm(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::BGSListForm* a_lists, RE::TESForm* a_form) -> std::vector<bool>
{
	std::vector<bool> vec;

	if (a_form == nullptr) {
		a_vm->TraceStack("akBaseObject cannot be None", a_stackID, Severity::kWarning);
		return vec;
	}

	if (a_lists == nullptr) {
		a_vm->TraceStack("akFormList cannot be None", a_stackID, Severity::kWarning);
		return vec;
	}

	if (a_lists->forms.empty()) {
		a_vm->TraceStack("akFormList cannot be empty", a_stackID, Severity::kWarning);
		return vec;
	}

	for (auto& column : a_lists->forms) {
		auto* row = column->As<RE::BGSListForm>();	// dubhDisguiseVampires

		if (row != nullptr) {
			vec.push_back(!row->forms.empty() && row->HasForm(a_form));
		}
	}

	return vec;
}


auto PapyrusMisc::InRangeGameTime(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const float a_min, const float a_max) -> bool
{
	auto* const calendar = RE::Calendar::GetSingleton();

	if (calendar == nullptr) {
		a_vm->TraceStack("Cannot initialize calendar singleton", a_stackID, Severity::kWarning);
		return false;
	}

	auto currentGameTime = calendar->GetCurrentGameTime();
	currentGameTime -= floorf(currentGameTime);
	currentGameTime *= 24.f;

	return currentGameTime >= a_min && currentGameTime < a_max;
}


auto PapyrusMisc::LookupRaceWeightIndex(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const std::int32_t a_factionIndex, RE::TESRace* a_playerRace, std::vector<RE::TESRace*> a_races) -> std::int32_t
{
	if (a_factionIndex == -1) {
		a_vm->TraceStack("aiFactionIndex cannot be negative", a_stackID, Severity::kWarning);
		return -1;
	}

	if (a_playerRace == nullptr) {
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


auto PapyrusMisc::RegisterFuncs(VM* a_vm) -> bool
{
	if (!a_vm) {
		logger::info("PapyrusMisc - cannot get VMState");
		return false;
	}

	a_vm->RegisterFunction("SearchListForForms", "TurtleClub", SearchListForForms);
	a_vm->RegisterFunction("SearchListsForForm", "TurtleClub", SearchListsForForm);
	a_vm->RegisterFunction("InRangeGameTime", "TurtleClub", InRangeGameTime);
	a_vm->RegisterFunction("LookupRaceWeightIndex", "TurtleClub", LookupRaceWeightIndex);

	return true;
}
