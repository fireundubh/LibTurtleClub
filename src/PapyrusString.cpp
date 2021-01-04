#pragma once

#pragma warning(disable : 4100)

#include "PapyrusString.h"

static auto ltrim(std::string& s) -> void
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](const int ch) {
		return !std::isspace(ch);
	}));
}

static auto rtrim(std::string& s) -> void
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](const int ch) {
		return !std::isspace(ch);
	}).base(),
		s.end());
}

static auto split(const RE::BSFixedString& src, const char delimiter) -> std::vector<RE::BSFixedString>
{
	std::vector<RE::BSFixedString> vec;

	const auto* cstr = src.c_str();

	std::stringstream ss(cstr);

	while (ss.good()) {
		std::string substr;

		std::getline(ss, substr, delimiter);

		ltrim(substr);
		rtrim(substr);

		vec.emplace_back(substr.c_str());
	}

	return vec;
}

static auto splitAsInt(const RE::BSFixedString& src, const char delimiter) -> std::vector<std::int32_t>
{
	std::vector<std::int32_t> vec;

	const auto* cstr = src.c_str();

	std::stringstream ss(cstr);

	while (ss.good()) {
		std::string substr;

		std::getline(ss, substr, delimiter);

		try {
			const auto n = std::stol(substr);
			vec.push_back(n);
		} catch (std::invalid_argument& e) {
			logger::critical(e.what());
			vec.push_back(-1);
		} catch (std::out_of_range& e) {
			logger::critical(e.what());
			vec.push_back(-1);
		}
	}

	return vec;
}

static auto splitAsFloat(const RE::BSFixedString& src, const char delimiter) -> std::vector<float>
{
	std::vector<float> vec;

	const auto* cstr = src.c_str();

	std::stringstream ss(cstr);

	while (ss.good()) {
		std::string substr;

		std::getline(ss, substr, delimiter);

		try {
			auto n = std::stof(substr);
			vec.push_back(n);
		} catch (std::invalid_argument& e) {
			logger::critical(e.what());
			vec.push_back(-1.f);
		} catch (std::out_of_range& e) {
			logger::critical(e.what());
			vec.push_back(-1.f);
		}
	}

	return vec;
}

auto PapyrusString::SplitString(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const RE::BSFixedString a_source, const RE::BSFixedString a_delimiter) -> std::vector<RE::BSFixedString> // NOLINT(performance-unnecessary-value-param)
{
	return split(a_source, a_delimiter[0]);
}

auto PapyrusString::StrToFloatArray(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const RE::BSFixedString a_source, const RE::BSFixedString a_delimiter) -> std::vector<float> // NOLINT(performance-unnecessary-value-param)
{
	return splitAsFloat(a_source, a_delimiter[0]);
}

auto PapyrusString::StrToIntArray(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const RE::BSFixedString a_source, const RE::BSFixedString a_delimiter) -> std::vector<std::int32_t> // NOLINT(performance-unnecessary-value-param)
{
	return splitAsInt(a_source, a_delimiter[0]);
}

auto PapyrusString::WrapString(VM* a_vm, StackID a_stackID, RE::StaticFunctionTag*, const RE::BSFixedString a_source, const std::int32_t a_max_length) -> RE::BSFixedString // NOLINT(performance-unnecessary-value-param)
{
	std::string s = a_source.c_str();

	const auto lineWrap = std::regex{ "(.{1," + std::to_string(a_max_length) + "})(?: +|$)" };

	s = std::regex_replace(s, lineWrap, "$1\n");
	s.resize(s.size() - 1);

	return s.c_str();
}

auto PapyrusString::RegisterFuncs(VM* a_vm) -> bool
{
	if (!a_vm) {
		logger::info("PapyrusString - cannot get VMState");
		return false;
	}

	a_vm->RegisterFunction("SplitString", "TurtleClub", SplitString);
	a_vm->RegisterFunction("StrToFloatArray", "TurtleClub", StrToFloatArray);
	a_vm->RegisterFunction("StrToIntArray", "TurtleClub", StrToIntArray);
	a_vm->RegisterFunction("WrapString", "TurtleClub", WrapString);

	return true;
}
