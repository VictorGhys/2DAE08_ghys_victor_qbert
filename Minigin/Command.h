#pragma once
#include <iostream>

#include "GameObject.h"
#include "QbertComponent.h"
#include "ServiceLocator.h"

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};

class JumpCommand : public Command
{
public:
	virtual void Execute() override { Jump(); };
private:
	void Jump() { std::cout << "Jump\n"; };
};

class FireCommand : public Command
{
public:
	virtual void Execute() override { Fire(); };
private:
	void Fire() { std::cout << "Fire\n"; };
};

class DuckCommand : public Command
{
public:
	virtual void Execute() override { Duck(); };
private:
	void Duck() { std::cout << "Duck\n"; };
};

class FartCommand : public Command
{
public:
	virtual void Execute() override { Fart(); };
private:
	void Fart() { std::cout << "Fart\n"; };
};

class KillQbertCommand : public Command
{
public:
	KillQbertCommand(dae::GameObject* qbert)
		:m_Qbert(qbert)
	{
	}
	virtual void Execute() override { KillQbert(); };
private:
	void KillQbert()
	{
		std::cout << "Kill\n";
		m_Qbert->GetComponentByType<dae::QbertComponent>()->Kill();
	};
	dae::GameObject* m_Qbert;
};

class AddPointsCommand : public Command
{
public:
	AddPointsCommand(dae::GameObject* qbert)
		:m_Qbert(qbert)
	{
	}
	virtual void Execute() override { AddPoints(); };
private:
	void AddPoints()
	{
		std::cout << "Add Points\n";
		m_Qbert->GetComponentByType<dae::QbertComponent>()->ChangeTile();
		//qbert->SetPoints(qbert->GetPoints() + 1);
	};
	dae::GameObject* m_Qbert;
};


class ToggleMuteCommand : public Command
{
public:
	virtual void Execute() override { ToggleMute(); };
private:
	void ToggleMute() { dae::ServiceLocator::GetSoundSystem().ToggleMute(); };
};
