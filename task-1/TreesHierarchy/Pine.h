#pragma once
#include "Conifer.h"
#include <iostream>

/// <summary>
///  Example implementation of Tree
/// </summary>
class Pine : public Conifer {
public:
	void grow() override;

private:
	class PineNeedle : public NeedleLeaf {
	public:
		PineNeedle() = delete;
		PineNeedle(const int length) : m_length(length) {}

		int& length() {
			return m_length;
		}

	private:
		int m_length;
	};
};
