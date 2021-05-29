#pragma once
namespace dae {
	
	class QbertObserver
	{
	public:
		virtual ~QbertObserver() = default;
		virtual void Died() = 0;
		virtual void ChangedTile() = 0;
	};
}

