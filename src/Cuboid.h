
#pragma once





// tolua_begin
class cCuboid
{
public:
	// p1 is expected to have the smaller of the coords; Sort() swaps coords to match this
	Vector3i p1, p2;

	cCuboid(void) {}
	cCuboid(const Vector3i & a_p1, const Vector3i & a_p2) : p1(a_p1), p2(a_p2) {}
	cCuboid(int a_X1, int a_Y1, int a_Z1) : p1(a_X1, a_Y1, a_Z1), p2(a_X1, a_Y1, a_Z1) {}

	#ifdef TOLUA_EXPOSITION  // tolua isn't aware of implicitly generated copy constructors
		cCuboid(const cCuboid & a_Cuboid);
	#endif

	// DEPRECATED, use cCuboid(Vector3i, Vector3i) instead
	cCuboid(int a_X1, int a_Y1, int a_Z1, int a_X2, int a_Y2, int a_Z2) : p1(a_X1, a_Y1, a_Z1), p2(a_X2, a_Y2, a_Z2)
	{
		LOGWARNING("cCuboid(int, int, int, int, int, int) constructor is deprecated, use cCuboid(Vector3i, Vector3i) constructor instead.");
	}

	void Assign(int a_X1, int a_Y1, int a_Z1, int a_X2, int a_Y2, int a_Z2);
	void Assign(const cCuboid & a_SrcCuboid) { *this = a_SrcCuboid; }

	void Sort(void);

	int DifX(void) const { return p2.x - p1.x; }
	int DifY(void) const { return p2.y - p1.y; }
	int DifZ(void) const { return p2.z - p1.z; }

	/** Returns the volume of the cuboid, in blocks.
	Note that the volume considers both coords inclusive.
	Works on unsorted cuboids, too. */
	int GetVolume(void) const;

	/** Returns true if the cuboids have at least one voxel in common. Both coords are considered inclusive.
	Assumes both cuboids are sorted. */
	inline bool DoesIntersect(const cCuboid & a_Other) const
	{
		ASSERT(IsSorted());
		ASSERT(a_Other.IsSorted());

		// In order for cuboids to intersect, each of their coord intervals need to intersect
		return (
			DoIntervalsIntersect(p1.x, p2.x, a_Other.p1.x, a_Other.p2.x) &&
			DoIntervalsIntersect(p1.y, p2.y, a_Other.p1.y, a_Other.p2.y) &&
			DoIntervalsIntersect(p1.z, p2.z, a_Other.p1.z, a_Other.p2.z)
		);
	}

	bool IsInside(Vector3i v) const
	{
		return (
			(v.x >= p1.x) && (v.x <= p2.x) &&
			(v.y >= p1.y) && (v.y <= p2.y) &&
			(v.z >= p1.z) && (v.z <= p2.z)
		);
	}

	bool IsInside(int a_X, int a_Y, int a_Z) const
	{
		return (
			(a_X >= p1.x) && (a_X <= p2.x) &&
			(a_Y >= p1.y) && (a_Y <= p2.y) &&
			(a_Z >= p1.z) && (a_Z <= p2.z)
		);
	}

	bool IsInside(Vector3d v) const
	{
		return (
			(v.x >= p1.x) && (v.x <= p2.x) &&
			(v.y >= p1.y) && (v.y <= p2.y) &&
			(v.z >= p1.z) && (v.z <= p2.z)
		);
	}

	/** Returns true if this cuboid is completely inside the specifie cuboid (in all 6 coords).
	Assumes both cuboids are sorted. */
	bool IsCompletelyInside(const cCuboid & a_Outer) const;

	/** Moves the cuboid by the specified offsets in each direction */
	void Move(int a_OfsX, int a_OfsY, int a_OfsZ);

	/** Expands the cuboid by the specified amount in each direction.
	Works on unsorted cuboids as well.
	Note that this function doesn't check for underflows when using negative amounts. */
	void Expand(int a_SubMinX, int a_AddMaxX, int a_SubMinY, int a_AddMaxY, int a_SubMinZ, int a_AddMaxZ);

	/** Clamps both X coords to the specified range. Works on unsorted cuboids, too. */
	void ClampX(int a_MinX, int a_MaxX);

	/** Clamps both Y coords to the specified range. Works on unsorted cuboids, too. */
	void ClampY(int a_MinY, int a_MaxY);

	/** Clamps both Z coords to the specified range. Works on unsorted cuboids, too. */
	void ClampZ(int a_MinZ, int a_MaxZ);

	/** Returns true if the coords are properly sorted (lesser in p1, greater in p2) */
	bool IsSorted(void) const;

	/** If needed, expands the cuboid so that it contains the specified point. Assumes sorted. Doesn't contract. */
	void Engulf(Vector3i a_Point);

private:

	/** Returns true if the two specified intervals have a non-empty union */
	inline static bool DoIntervalsIntersect(int a_Min1, int a_Max1, int a_Min2, int a_Max2)
	{
		ASSERT(a_Min1 <= a_Max1);
		ASSERT(a_Min2 <= a_Max2);
		return ((a_Min1 <= a_Max2) && (a_Max1 >= a_Min2));
	}

} ;
// tolua_end




