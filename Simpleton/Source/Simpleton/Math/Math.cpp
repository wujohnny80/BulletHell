//====================================================================================================
// Filename:	Math.cpp
// Created by:	Johnny Wu
//====================================================================================================

#include "Math.h"

namespace Math
{

bool PointInRect(const Vector2& point, const Rect& rect)
{
	if (point.x > rect.Max().x || point.x < rect.x ||
		point.y > rect.Max().y || point.y < rect.y)
	{
		return false;
	}
	return true;
}

bool PointInCircle(const Vector2& point, const Circle& circle)
{
	const Vector2 centerToPoint = point - circle.center;
	const float distSqr = Dot(centerToPoint, centerToPoint);
	const float radiusSqr = circle.radius * circle.radius;
	return distSqr < radiusSqr;
}

bool Intersect(const Line& a, const Line& b)
{
	float ua = ((a.to.x - a.from.x) * (b.from.y - a.from.y)) - ((a.to.y - a.from.y) * (b.from.x - a.from.x));
	float ub = ((b.to.x - b.from.x) * (b.from.y - a.from.y)) - ((b.to.y - b.from.y) * (b.from.x - a.from.x));
	float denom = ((a.to.y - a.from.y) * (b.to.x - b.from.x)) - ((a.to.x - a.from.x) * (b.to.y - b.from.y));

	// First check for special cases
	if (denom == 0.0f)
	{
		if (ua == 0.0f && ub == 0.0f)
		{
			// The line segments are the same
			return true;
		}
		else
		{
			// The line segments are parallel
			return false;
		}
	}

	ua /= denom;
	ub /= denom;

	if (ua < 0.0f || ua > 1.0f || ub < 0.0f || ub > 1.0f)
	{
		return false;
	}

	return true;
}

bool Intersect(const Circle& c0, const Circle& c1)
{
	const float fRadii = c0.radius + c1.radius;
	const float fRadiiSquared = fRadii * fRadii;
	const float fDistanceSquared = DistanceSqr(c0.center, c1.center);
	return (fDistanceSquared < fRadiiSquared);
}

bool Intersect(const Rect& r0, const Rect& r1)
{

	// AABB
	if ((r0.x < r1.Max().x) &&
		(r0.Max().x > r1.x) &&
		(r0.y < r1.Max().y) &&
		(r0.Max().y > r1.y))
		return true;
	else
		return false;
}

bool Intersect(const Line& l, const Circle& c)
{
	return Intersect(c, l);
}

bool Intersect(const Circle& c, const Line& l)
{
	Vector2 startToCenter = c.center - l.from;
	Vector2 startToEnd = l.to - l.from;
	float len = startToEnd.Magnitude();
	Vector2 dir = startToEnd / len;

	// Find the closest point to the line segment
	float projection = Dot(startToCenter, dir);
	Vector2 closestPoint;
	if (projection > len)
	{
		closestPoint = l.to;
	}
	else if (projection < 0.0f)
	{
		closestPoint = l.from;
	}
	else
	{
		closestPoint = l.from + (dir * projection);
	}

	// Check if the closest point is within the circle
	Vector2 closestToCenter = c.center - closestPoint;
	if (closestToCenter.MagnitudeSqr() > c.radius * c.radius)
	{
		return false;
	}
	return true;
}

bool Intersect(const Circle& c, const Rect& r)
{
	return Intersect(r, c);
}

bool Intersect(const Rect& r, const Circle& c)
{
	Vector2 closestPoint;
	closestPoint.x = Clamp(c.center.x, r.x, r.Max().x);
	closestPoint.y = Clamp(c.center.y, r.y, r.Max().y);
	
	const float distance = Distance(closestPoint, c.center);
	if (distance > c.radius)
	{
		return false;
	}
	return true;
}

int RandomRange(int min, int max)
{
	if (min == max)
		return min;
	return rand() % (max - min + 1) + min;
}

int Pow(int b, int e)
{
	if (e == 0)
		return 1;
	if (e == 1)
		return b;

	if (e % 2 == 0)
		return Pow(b*b, e/2);
	else
		return b * Pow(b, e-1);
}

Vector2 GetCubicBezierPosition(float t, std::vector<Vector2>& p)
{
	Vector2 result;

	result = p[3] - p[0] - 3 * (p[2] - p[1]);
	result = result * t + 3 * (p[2] - 2 * p[1] + p[0]);
	result = result * t + 3 * (p[1] - p[0]);
	result = result * t + p[0];

	/*float t1 = 1-t;
	float t2 = t1 * t1;
	float t3 = t1 * t1 * t1;
	float tSq = t * t;
	float tCb = tSq * t;

	result.x =	   p[0].x * t3 + 
			   3 * p[1].x * t2 * t + 
			   3 * p[2].x * t1 * tSq +
				   p[3].x * tCb;

	result.y =	   p[0].y * t3 + 
			   3 * p[1].y * t2 * t + 
			   3 * p[2].y * t1 * tSq +
				   p[3].y * tCb;*/

	return result;
}

float GetBezierDistance(std::vector<Vector2>& p)
{
	const int kSteps = 10;
	float step = 1.0f / kSteps;
	Vector2 p0 = GetCubicBezierPosition(0, p);

	float dist = 0;
	for (int i = 0; i <= kSteps; ++i)
	{
		Vector2 p1 = GetCubicBezierPosition(i * step, p);
		dist += (p1 - p0).Magnitude();
		p0 = p1;
	}
	return dist;
}

}