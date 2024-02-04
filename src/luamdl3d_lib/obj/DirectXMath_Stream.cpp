#include "DirectXMath_Stream.h"

std::ostream& operator<<(std::ostream& out, const DirectX::XMFLOAT2& f2)
{
    out << std::fixed << std::setprecision(5);
    out << f2.x << " " << f2.y;
    return out;
}

std::ostream& operator<<(std::ostream& out, const DirectX::XMFLOAT3& f3)
{
    out << std::fixed << std::setprecision(5);
    out << f3.x << " " << f3.y << " " << f3.z;
    return out;
}

std::ostream& operator<<(std::ostream& out, const DirectX::XMFLOAT4& f4)
{
    out << std::fixed << std::setprecision(5);
    out << f4.x << " " << f4.y << " " << f4.z << " " << f4.w;
    return out;
}
