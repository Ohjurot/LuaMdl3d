#pragma once

#include <DirectXMath.h>

#include <ostream>
#include <iomanip>

std::ostream& operator<<(std::ostream& out, const DirectX::XMFLOAT2& f2);
std::ostream& operator<<(std::ostream& out, const DirectX::XMFLOAT3& f3);
std::ostream& operator<<(std::ostream& out, const DirectX::XMFLOAT4& f4);
