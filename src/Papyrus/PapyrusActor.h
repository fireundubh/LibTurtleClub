#pragma once

namespace PapyrusActor
{
	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	auto GetFactionStates(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor, RE::BGSListForm* a_factions) -> std::vector<bool>;
	auto GetWornEquipment(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::Actor* a_actor, bool a_leftWeapon, bool a_rightWeapon) -> std::vector<RE::TESForm*>;

	auto RegisterFuncs(VM* a_vm) -> bool;
}
