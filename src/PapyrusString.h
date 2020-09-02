#pragma once

#include "main.h"


namespace PapyrusString
{
	using VM = RE::BSScript::IVirtualMachine;
	using StackID = RE::VMStackID;
	using Severity = RE::BSScript::ErrorLogger::Severity;

	auto SplitString(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::BSFixedString a_source, RE::BSFixedString a_delimiter) -> std::vector<RE::BSFixedString>;
	auto StrToFloatArray(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const RE::BSFixedString a_source, const RE::BSFixedString a_delimiter) -> std::vector<float>;
	auto StrToIntArray(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const RE::BSFixedString a_source, const RE::BSFixedString a_delimiter) -> std::vector<std::int32_t>;
	auto WrapString(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, RE::BSFixedString a_source, std::int32_t a_max_length) -> RE::BSFixedString;

	auto RegisterFuncs(VM* a_vm) -> bool;
}
