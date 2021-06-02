#pragma once
namespace qbert {
	class QbertObserver
	{
	public:
		virtual ~QbertObserver() = default;
		virtual void Died() = 0;
		virtual void ChangedTile() = 0;
	};
}
