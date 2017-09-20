#pragma once

struct MathF
{
	typedef struct Vector2
	{
		double x;
		double y;

		Vector2(double _x = 0, double _y = 0)
			: x(_x), y(_y)
		{}

		Vector2 operator/(double dest) const
		{
			return Vector2(x / dest, y / dest);
		}
		Vector2 operator*(double dest) const
		{
			return Vector2(x * dest, y * dest);
		}
		Vector2 operator+(const Vector2 & other) const
		{
			return Vector2(x + other.x, y + other.y);
		}
		Vector2 operator-(const Vector2 & other) const
		{
			return Vector2(x - other.x, y - other.y);
		}

		double Length() const
		{
			return sqrt(x*x + y*y);
		}

	} VECTOR, *PVECTOR;

	/* �� ������ �Ÿ� */
	static double Distance(const VECTOR& Dst, const VECTOR& Src)
	{
		return (Dst - Src).Length();
	}
	/* �� ���͸� �߽����� �� ���� �浹 */
	static bool CircleCollision(const VECTOR& DstCenter, double DstRadius, const VECTOR& SrcCenter, double SrcRadius)
	{
		return Distance(DstCenter, SrcCenter) < DstRadius + SrcRadius;
	}
	/* ���� �̳��θ� �� ���� */
	static double Clamp(double Data, double Min = 0, double Max = 1)
	{
		if (Min > Max)
			swap(Min, Max);

		if (Min > Data)
			return Min;
		if (Max < Data)
			return Max;
		return Data;
	}
	/* ���� �̳��θ� ���� ���� */
	static VECTOR Clamp(VECTOR Data, VECTOR Min, VECTOR Max)
	{
		Data.x = Clamp(Data.x, Min.x, Max.x);
		Data.y = Clamp(Data.y, Min.y, Max.y);
		return Data;
	}
	/* ���� �������� �ݺ� */
	static double Repeat(double Data, double Min = 0, double Max = 1)
	{
		if (Min == Max)
			return Data;

		if (Min > Max)
			swap(Min, Max);
		double Dst = (Max - Min);
		int Single = (int)(Data / Dst);
		if (Single % 2 == 1)
			return (Data - (Single * Dst)) + Min;
		return Max - (Data - (Single * Dst));
	}
	/* �� ���� �������� */
	static double Lerp(double Data, double Begin, double End)
	{
		return (End - Begin) * Data + Begin;
	}
	/* �� ������ �������� */
	static VECTOR Lerp(double Data, VECTOR Begin, VECTOR End)
	{
		return (End - Begin) * Data - Begin;
	}
	/* ���� ������ �������� */
	static VECTOR Slerp(double Data, list<VECTOR> Line)
	{
		if (Line.size() == 1)
			return *Line.begin();

		list<VECTOR>::iterator Before, After;
		do
		{
			Before = Line.begin();
			After = ++Line.begin();
			while (After != Line.end())
			{
				Line.push_front(Lerp(Data, *Before, *After));
				++Before;
				++After;
			}
			Line.erase(Before);
		} while (Line.size() > 1);
		return *Line.begin();
	}
};