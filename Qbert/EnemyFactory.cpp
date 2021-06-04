#include "MiniginPCH.h"
#include "EnemyFactory.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "UggOrWrongWayComponent.h"

dae::GameObject* qbert::EnemyFactory::CreateEnemy(EnemyComponent::EnemyType type, QbertGame* qbertGame)
{
	dae::GameObject* enemy = new dae::GameObject();
	MovementComponent* movementComponent;
	dae::RenderComponent* renderComponent;

	UggOrWrongWayComponent* CoilyComponent;
	UggOrWrongWayComponent* uggComponent;
	UggOrWrongWayComponent* wrongwayComponent;
	UggOrWrongWayComponent* slickComponent;
	UggOrWrongWayComponent* samComponent;
	switch (type)
	{
	case EnemyComponent::EnemyType::COILY:
		movementComponent = new MovementComponent(enemy, qbertGame, { 0,3 });
		enemy->AddComponent(movementComponent);

		CoilyComponent = new UggOrWrongWayComponent(enemy, type, movementComponent, false);
		enemy->AddComponent(CoilyComponent);

		renderComponent = new dae::RenderComponent(enemy);
		enemy->AddComponent(renderComponent);
		renderComponent->SetTexture("../Data/Coily.png");
		renderComponent->SetWidth(34);
		renderComponent->SetHeight(32);
		renderComponent->SetPosition(45, 35);
		break;
	case EnemyComponent::EnemyType::UGG:
		movementComponent = new MovementComponent(enemy, qbertGame, { 6,6 });
		enemy->AddComponent(movementComponent);

		uggComponent = new UggOrWrongWayComponent(enemy, EnemyComponent::EnemyType::UGG, movementComponent, false);
		enemy->AddComponent(uggComponent);

		renderComponent = new dae::RenderComponent(enemy);
		enemy->AddComponent(renderComponent);
		renderComponent->SetTexture("../Data/Ugg.png");
		renderComponent->SetWidth(34);
		renderComponent->SetHeight(32);
		renderComponent->SetPosition(45, 35);
		break;
	case EnemyComponent::EnemyType::WRONGWAY:
		movementComponent = new MovementComponent(enemy, qbertGame, { 6,0 });
		enemy->AddComponent(movementComponent);

		wrongwayComponent = new UggOrWrongWayComponent(enemy, EnemyComponent::EnemyType::WRONGWAY, movementComponent, false);
		enemy->AddComponent(wrongwayComponent);

		renderComponent = new dae::RenderComponent(enemy);
		enemy->AddComponent(renderComponent);
		renderComponent->SetTexture("../Data/Wrong-Way.png");
		renderComponent->SetWidth(34);
		renderComponent->SetHeight(32);
		renderComponent->SetPosition(45, 35);
		break;

	case EnemyComponent::EnemyType::SLICK:
		movementComponent = new MovementComponent(enemy, qbertGame, { 6,6 });
		enemy->AddComponent(movementComponent);

		slickComponent = new UggOrWrongWayComponent(enemy, EnemyComponent::EnemyType::SLICK, movementComponent, false);
		enemy->AddComponent(slickComponent);

		renderComponent = new dae::RenderComponent(enemy);
		enemy->AddComponent(renderComponent);
		renderComponent->SetTexture("../Data/Slick.png");
		renderComponent->SetWidth(34);
		renderComponent->SetHeight(32);
		renderComponent->SetPosition(45, 35);
		break;
	case EnemyComponent::EnemyType::SAM:
		movementComponent = new MovementComponent(enemy, qbertGame, { 6,6 });
		enemy->AddComponent(movementComponent);

		samComponent = new UggOrWrongWayComponent(enemy, EnemyComponent::EnemyType::SAM, movementComponent, false);
		enemy->AddComponent(samComponent);

		renderComponent = new dae::RenderComponent(enemy);
		enemy->AddComponent(renderComponent);
		renderComponent->SetTexture("../Data/Sam.png");
		renderComponent->SetWidth(34);
		renderComponent->SetHeight(32);
		renderComponent->SetPosition(45, 35);
		break;
	}
	return enemy;
}