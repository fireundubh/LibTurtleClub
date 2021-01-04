#pragma once

namespace PapyrusActor
{
	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	constexpr std::array<std::int32_t, 8> SLOTS = { 31, 32, 33, 35, 36, 37, 39, 42 };

	auto ActorHasAnyKeyword(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor, RE::BGSListForm* a_keywords) -> bool;
	auto ActorIsInAnyFaction(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor, RE::BGSListForm* a_factions) -> bool;
	auto ActorIsInFaction(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor, RE::TESFaction* a_faction) -> bool;
	auto GetFactionStates(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor, RE::BGSListForm* a_factions) -> std::vector<bool>;
	auto GetWornEquipment(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor) -> std::vector<RE::TESForm*>;

	auto RegisterFuncs(VM* a_vm) -> bool;
}
