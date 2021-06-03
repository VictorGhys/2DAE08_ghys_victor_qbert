#pragma once
namespace qbert {
	class QbertObserver
	{
	public:
		virtual ~QbertObserver() = default;
		virtual void Died() = 0;
		virtual void ChangedTile() = 0;
		virtual void RemainingDisk() = 0;
		virtual void DefeatCoily() = 0;
		virtual void CatchSlickOrSlam() = 0;
	};
}
