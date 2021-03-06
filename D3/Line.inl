#pragma once

#include "Line.h"
#include "Coordinate/NormalizedVector.h"

namespace KEngine
{
	namespace Math
	{
		namespace D3
		{
			inline Line::Line() : m_points()
			{
				m_points[1] = Coordinate::Vector<3>(1.0f, 0.0f, 0.0f);
			}
			inline Line::Line(const Coordinate::Vector<3>& p_pointA,
				const Coordinate::Vector<3>& p_pointB) 
				: m_points{ p_pointA, p_pointB } {}

			constexpr Line::Line(const Data::Storage::Array<Coordinate::Vector<3>, 2>& p_pointArray)
				: m_points(p_pointArray) {}
			
			inline Line::Line(const Ray& p_ray)
				: m_points{ p_ray.GetOrigin(), p_ray.GetOrigin() + p_ray.GetDirection() } {}

			inline bool Line::operator==(const Line& p_line) const
			{
				const Data::Storage::Array<Coordinate::Vector<3>, 2>& p_points = p_line.GetPoints();
				return IsOnLine(p_points[0]) && IsOnLine(p_points[1]);
			}

			inline bool Line::operator!=(const Line& p_line) const
			{
				return !operator==(p_line);
			}

			inline bool Line::IsOnLine(const Coordinate::Vector<3>& p_point) const
			{
				auto directionA = Coordinate::NormalizedVector<3>(p_point - m_points[0]);
				auto directionB = Coordinate::NormalizedVector<3>(m_points[1] - m_points[0]);
				return p_point == m_points[0] || 
					p_point == m_points[1] || 
					directionA == directionB || 
					directionA == -directionB;
			}

			inline float Line::DistanceToLine(const Coordinate::Vector<3>& p_point) const
			{
				return DirectX::XMVectorGetX(DirectX::XMVector3LinePointDistance(m_points[0], m_points[1], p_point));
			}

			inline const Data::Storage::Array<Coordinate::Vector<3>, 2>& Line::GetPoints() const
			{
				return m_points;
			}
			inline Data::Storage::Array<Coordinate::Vector<3>, 2>& Line::GetPoints()
			{
				return m_points;
			}
		}
	}
}